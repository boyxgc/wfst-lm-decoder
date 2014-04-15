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
#include <fstream>

int fst_alphabet_load(fst_alphabet_h *ab, char * symfn) {
    int ret = -1;
    std::ifstream fin;
    fin.open(symfn);
    if(!fin) {
        spark_debug("open %s failed", symfn);
        goto end;
    }
    fst_alphabet_reset(ab); 
    //get lines of file
    unsigned int count = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
    ab->n_labels = count+1;
    ab->labels   = new char *[count+1];
 
    int label_n;
    char label[MAX_LINE];
    while((fin >> label_n) && (fin >> label)) {
        ab->n_labels        = label_n;
        ab->labels[label_n] = new char[MAX_LINE];
        strcpy(ab->labels[label_n], label);
        if(strcmp(label, SENT_START) == 0) {
            ab->sent_start = label_n;
        } else if (strcmp(label, SENT_END) == 0) {
            ab->sent_end = label_n;
        } else if (strcmp(label, EPS_MARKER) == 0) {
            ab->eps_marker = label_n;
        }
    }
    ret = 0;
end:
    return ret;
}

int fst_alphabet_reset(fst_alphabet *ab) {
    int ret = 0;
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
    return ret;
}
