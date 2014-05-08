/*
 * =====================================================================================
 *       Filename:  fst_alphabet.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:25:54
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#ifndef fst_alphabet_H
#define fst_alphabet_H

#include "utils/fst_common.h"
#include <unordered_map>

#define SENT_START "<s>"
#define SENT_END   "</s>"
#define EPS_MARKER "<eps>"
#define UNK_MARKER "<unk>"

typedef struct {
	unsigned int   n_labels;
	//union{
	//char         **labels;
	string        *labels;
	//}
	fst_label_id   sent_start;
	fst_label_id   sent_end;
	fst_label_id   eps_marker;
    fst_label_id   unk_marker;

    std::unordered_map<string, fst_label_id> symbol_id_map;
}fst_alphabet_t, fst_in_alphabet_t, fst_out_alphabet_t;

fst_alphabet_t * fst_alphabet_new();
int fst_alphabet_load (fst_alphabet_t *ab, const char * symfn);
int fst_alphabet_reset(fst_alphabet_t *ab);
int fst_alphabet_sym2id(fst_alphabet_t *ab, const std::vector<std::string> &v_str, std::vector<fst_label_id> &v_id);
#endif   /* ----- #ifndef fst_alphabet_H  ----- */


