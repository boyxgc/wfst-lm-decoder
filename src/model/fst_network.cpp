/*
 * =====================================================================================
 *       Filename:  fst_network.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/16/2014 20:26:52
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "model/fst_network.h"
#include "utils/utils.h"

fst_network_t *fst_network_new() {
    fst_network_t * net = new fst_network_t();
    if(NULL == net) {
        spark_debug("new fst_network_t failed!\n");
        return NULL;
    }
    fst_network_reset(net);
    return net;
}

int fst_network_reset(fst_network_t * net) {
    int ret = -1;
    if(NULL == net) {
        spark_debug("reset NULL fst_network_t\n");
        return ret;
    }
    net->init_state       = 0;
    net->max_state        = 0;
    net->n_states         = 0;
    net->states           = NULL;
    net->n_final_states   = 0;
    net->final_states     = NULL;
    net->n_trans          = 0;
    net->n_max_out_trans  = 0;
    net->trans            = NULL;
    net->input_alphabet   = NULL;
    net->output_alphabet  = NULL;
    net->sent_start       = 0;
    net->sent_end         = 0;
    net->eps_marker       = 0;

    return ret;
}

int fst_network_load(fst_network_t * net, const char * fn, const char *isymfn, const char *osymfn) {
    int ret = -1;
    std::ifstream fin;
    fin.open(fn);
    if(!fin) {
        spark_debug("open %s failed\n", fn);
        return ret;
    }

    fst_network_reset(net);
    
    int init_state_n     = -1;
    int max_state_n      = -1;
    int n_final_states   = 0;
    int n_trans          = 0;
    int n_max_out_trans  = 0;
    
    //get init state from first line
    fin.seekg(0, std::ios::beg);
    if(!(fin >> init_state_n) || init_state_n < 0) {
        spark_debug("read init_state_n error\n");
        return ret;
    }

    // get the max num of state from last line
    char ch = ' ';
    int pos = -3;

    fin.seekg(pos, std::ios::end);
    fin.read(&ch,1);
    while(ch != '\n') {
        pos--;
        fin.seekg(pos, std::ios::end);
        fin.read(&ch,1);
    }
    fin >> max_state_n;
    if(max_state_n < 0) {
        spark_debug("max_state_n: %d\n", max_state_n);
        return ret;
    }

    //get number of transitions and final states;
    std::string  line               = "";
    int          n_line             = 0;
    std::string  last_state         = "-";
    int          maxsofar_out_trans = 0;
    const char  *delim              = " \t";
    std::vector<std::string> v;

    fin.seekg(0, std::ios::beg);
    while(getline(fin, line)) {
        if(line == ""){
            continue;
        }
        split(line, v, delim);
        
        n_line++;
        #if DEBUG >=1
        //printf("file %s, line: %d",fn, n_line);
        #endif

        if(v.size() == 0) {
            spark_debug("file %s, wrong line %d\n", fn, n_line);
        }
        if(v[0] == last_state){
            maxsofar_out_trans++;
        } else {
            if(maxsofar_out_trans > n_max_out_trans){
                n_max_out_trans    = maxsofar_out_trans;
            }
            maxsofar_out_trans = 1;
            last_state = v[0];
        }

        if(v.size() == FST_FILE_COLUMN_NORMAL){
            n_trans++;
        } else if(v.size() == FST_FILE_COLUMN_FINAL_STATE) {
            n_final_states++;
        } else {
            spark_debug("wrong data in file %s, line %d", fn, n_line);
        }
    }
    
    assert(n_trans+n_final_states == n_line);

    net->max_state       = max_state_n;
    net->init_state      = init_state_n;
    net->n_states        = max_state_n+1;
    net->states          = new fst_state_t*[net->n_states];
    net->n_final_states  = n_final_states;
    net->final_states    = new fst_final_state_t*[net->n_final_states];
    net->n_trans         = n_trans;
    net->n_max_out_trans = n_max_out_trans;
    net->trans           = new fst_transition_t*[net->n_trans];

    net->input_alphabet = fst_alphabet_new();
    if(fst_alphabet_load(net->input_alphabet, isymfn) == -1){
        spark_debug("load input_alphabet file %s failed", isymfn);
        return ret;
    }
    net->output_alphabet = fst_alphabet_new();
    if(fst_alphabet_load(net->output_alphabet, osymfn) == -1) {
        spark_debug("load output_alphabet file %s failed", osymfn)
        return ret;
    }
    net->sent_start = net->input_alphabet->sent_start;
    net->sent_end   = net->input_alphabet->sent_end;
    net->eps_marker = net->input_alphabet->eps_marker;

    memset(net->states, 0, net->n_states * sizeof(fst_state_t*));
    memset(net->final_states, 0, net->n_final_states * sizeof(fst_final_state_t *));
    memset(net->trans, 0, net->n_trans * sizeof(fst_transition_t *));

    //create states trans final_states
    int tran_n        = 0;
    int final_state_n = 0;
    last_state    = "-";
    n_line        = 0;
    line          = "";
    fin.close();
    fin.open(fn);
    //fin.seekg(0, std::ios::beg);
    while(getline(fin, line)) {
        if(line == ""){
            continue;
        }
        split(line, v, delim);
        n_line++;

        if(v.size() == FST_FILE_COLUMN_NORMAL) {// normal transition data
            int from_state = std::atoi(v[0].c_str());
            int to_state   = std::atoi(v[1].c_str());
            int in_label   = std::atoi(v[2].c_str());
            int out_label  = std::atoi(v[3].c_str());
            real weight     = std::atof(v[4].c_str());
            net->trans[tran_n] = fst_transition_new(to_state, weight, in_label, out_label);

            if(v[0] == last_state) {
                if(net->states[from_state]){
                    net->states[from_state]->n_trans++;
                } else {
                    spark_debug("file wrong order! state :%d NULL\n", from_state);
                    return ret;
                }
            } else {
                if(!net->states[from_state]){
                    net->states[from_state] = fst_state_new(tran_n, 1);
                } else {
                    spark_debug("file wrong order! state :%d NOT NULL\n", from_state);   
                    return ret;
                }
            }
            tran_n++;
        } else {                             // final state data
            int from_state = std::atoi(v[0].c_str());
            real weight     = std::atof(v[1].c_str());

            if(v[0] == last_state) {
                if(!net->final_states[final_state_n]){
                    net->final_states[final_state_n] = fst_final_state_new(from_state, weight);
                } else {
                    spark_debug("final state: %d NOT NULL\n", from_state);
                    return ret;
                }
            } else {
                spark_debug("final state %d alone, no shown before\n", from_state);
            }
            final_state_n++;
        }
        last_state = v[0];
    }

    if(fin) {
        fin.close();
    }
    ret = 0;
    return ret;
}
