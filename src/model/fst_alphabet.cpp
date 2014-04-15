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
    ab->labels   = new char *[count+1];

    #ifdef DEBUG
    //cout << ab->n_labels << endl;
    #endif
 
    int label_n;
    std::string label;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    while((fin >> label) && (fin >> label_n)) {
        //ab->n_labels        = label_n;
        ab->labels[label_n] = new char[label.size()+1];
        ab->labels[label_n][label.size()] = 0;
        memcpy(ab->labels[label_n], label.c_str(), label.size());
        #if DEBUG >= 1
        //printf("%s\t\t%d", ab->labels[label_n], label_n);
        if (label == "y-ou2+er1"){
            printf("y-ou2+er1 id: %d\n", label_n);
        }
        #endif
        //strcpy(ab->labels[label_n], label);
        if(label == SENT_START) {
            ab->sent_start = label_n;
        } else if (label == SENT_END) {
            ab->sent_end = label_n;
        } else if (label == EPS_MARKER) {
            ab->eps_marker = label_n;
        }
    }
    ret = 0;
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
        for(int i = 0; i < ab->n_labels; ++i) {
            delete [] ab->labels[i];
        }
        delete [] ab->labels;
    }
    ab->n_labels   = 0;
    ab->sent_start = -1;
    ab->sent_end   = -1;
    ab->eps_marker = -1;
    ret = 0;
    return ret;
}
