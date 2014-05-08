/*
 * =====================================================================================
 *       Filename:  fst_alphabet.c
 *    Description:  
 *        Version:  1.0
 *        Created:  04/14/2014 18:58:59
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "model/fst_alphabet.h"
#include "utils/fst_common.h"
#include <fstream>

fst_alphabet_t * fst_alphabet_new() {
    fst_alphabet_t *ab = NULL;
    ab = new fst_alphabet_t();
    if(!ab) {
        spark_debug("new fst_alphabet_t failed");
        return NULL;
    }
    fst_alphabet_reset(ab);
    return ab;
}

int _map_symbol_id(fst_alphabet_t* ab) {
    int ret = -1;
    if(NULL == ab) {
        spark_debug("map_symbol_id NULL fst_alphabet \n");
        return ret;
    }
    if(ab->n_labels == 0) {
        spark_debug("0 alphabet->n_labels\n");
        return ret;
    }
    if(NULL == ab->labels) {
        spark_debug("NULL alpbabet->labels\n");
        return ret;
    }

    ab->symbol_id_map.clear();
    for(int i = 0; i < ab->n_labels; ++i) {
        if(ab->symbol_id_map.find(ab->labels[i]) != ab->symbol_id_map.end()) {
            spark_debug("label: %s already exists\n", (ab->labels[i]).c_str());
            return ret;
        } else {
            ab->symbol_id_map[ab->labels[i]] = i;
        }
    }
    ret = 0;
    return ret;
}

int fst_alphabet_load(fst_alphabet_t *ab, const char * symfn) {
    int ret = -1;
    std::ifstream fin;
    fin.open(symfn);
    if(!fin) {
        spark_debug("open %s failed", symfn);
        //goto end;
        return ret;
    }
    fst_alphabet_reset(ab); 
    //get lines of file
    int count = 0;
    count  = std::count(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>(), '\n');
    ab->n_labels = count+1;
    //ab->labels   = new char *[count+1];
    ab->labels   = new string[count+1];

    int label_n;
    std::string label;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while((fin >> label) && (fin >> label_n)) {
        //ab->labels[label_n] = new char[label.size()+1];
        //ab->labels[label_n][label.size()] = 0;
        //memcpy(ab->labels[label_n], label.c_str(), label.size());
        ab->labels[label_n] = label;
        #if DEBUG >= 1
        //printf("%s\t\t%d", ab->labels[label_n], label_n);
        #endif
        //strcpy(ab->labels[label_n], label);
        if(label == SENT_START) {
            ab->sent_start = label_n;
        } else if (label == SENT_END) {
            ab->sent_end = label_n;
        } else if (label == EPS_MARKER) {
            ab->eps_marker = label_n;
        } else if (label == UNK_MARKER) {
            ab->unk_marker = label_n;
        }
    }
    ret = _map_symbol_id(ab);// build map
//end:
    if(fin){
        fin.close();
    }
    return ret;
}

int fst_alphabet_reset(fst_alphabet_t *ab) {
    int ret = -1;
    if(ab == NULL){
        spark_debug("object NULL");
        return ret;
    }
    if(ab->n_labels > 0) {
        //for(int i = 0; i < ab->n_labels; ++i) {
        //    delete [] ab->labels[i];
        //}
        delete [] ab->labels;
    }
    ab->n_labels   = 0;
    ab->sent_start = -1;
    ab->sent_end   = -1;
    ab->eps_marker = -1;
    ret = 0;
    return ret;
}

int fst_alphabet_sym2id(fst_alphabet_t *ab, const std::vector<std::string> &v_str, std::vector<fst_label_id> &v_id) {
    int ret = -1;
    if(ab->symbol_id_map.empty() ) {
        spark_debug("empty symbol_id_map\n");
        return ret;
    }
    for(int i = 0; i < v_str.size(); ++i) {
        if(ab->symbol_id_map.find(v_str[i]) != ab->symbol_id_map.end() ) {
            v_id.push_back(ab->symbol_id_map[v_str[i]]);
        } else {
            v_id.push_back(ab->unk_marker);
        }
    }
    ret = 0;
    return ret;
}

