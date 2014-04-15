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

#define SENT_START "<s>"
#define SENT_END   "</s>"
#define EPS_MARKER "<eps>"

typedef struct {
	unsigned int   n_labels;
	char         **labels;
	fst_label_id   sent_start;
	fst_label_id   sent_end;
	fst_label_id   eps_marker;
}fst_alphabet_t, fst_in_alphabet_t, fst_out_alphabet_t;

fst_alphabet_t * fst_alphabet_new();
int fst_alphabet_load (fst_alphabet_t *ab, const char * symfn);
int fst_alphabet_reset(fst_alphabet_t *ab);
#endif   /* ----- #ifndef fst_alphabet_H  ----- */


