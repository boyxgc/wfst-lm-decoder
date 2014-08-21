/*
 * =====================================================================================
 *       Filename:  test.cpp
 *    Description:  GG
 *        Version:  1.0
 *        Created:  04/14/2014 20:17:35
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "model/fst_alphabet.h"
#include "utils/fst_common.h"
#include "model/fst_network.h"

#include <vector>
#include <iostream>
using namespace std;

int main() {
    int ret;
/*    fst_alphabet_t *ab = NULL;
    ab = fst_alphabet_new();
    const char * fn= "test.syms";
    ret = fst_alphabet_load(ab, fn);
    if (ret == -1){
    	cout << "alphabet load error";
    	return 0;
    }
    cout << "n_labels:" << ab->n_labels << endl;
    cout << "eps_marker id:" << ab->eps_marker << endl;
*/
    fst_network_t *net = fst_network_new();
    //const char *netfn = "test.mod.txt";
    ret = fst_network_load(net, "test.mod.txt", "test.syms", "test.syms");
    if(ret == -1){
        cout << "network load error";
        return 0;
    }
    cout << "init_state_n:" << net->init_state << endl;
    cout << "n_trans:" << net->n_trans << endl;
    cout << "n_max_out_trans:" << net->n_max_out_trans << endl;
    cout << "n_states:" << net->n_states << endl;
    cout << "n_final_states:" << net->n_final_states << endl;
    cout << "final_state 3: id:" << net->final_states[3]->state_id << ", weight:" << net->final_states[3]->weight << endl;
    cout << "state 1:" << net->states[1]-> tran_start << "," << net->states[1]->n_trans << endl;
    cout << "state 4:" << net->states[4]-> tran_start << "," << net->states[4]->n_trans << endl;
    cout << "state 8:" << net->states[8]-> tran_start << "," << net->states[8]->n_trans << endl;
    cout << "trans 10:" << net->trans[10]->to_state << ", " << net->trans[10]->weight << "," << net->trans[10]->in_label_id << endl;

    string strs [] = {"foo", "foo", "bar", "test", "<eps>", "hello", "bar"};
    vector<string> v_str(strs, strs+7);
    vector<fst_label_id> v_id;
    fst_alphabet_sym2id(net->input_alphabet, v_str, v_id);
    for(int i = 0; i < v_str.size(); ++i) {
        cout << v_str[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < v_id.size(); ++i) {
        cout << v_id[i] << " ";
    }
    cout << endl;
    return 0;
}
