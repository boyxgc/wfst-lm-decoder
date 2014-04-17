/*
 * =====================================================================================
 *       Filename:  fst_network.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:28:15
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#ifndef  fst_network_H
#define  fst_network_H

#include "utils/fst_common.h"
#include "model/fst_alphabet.h"
#include "model/fst_transition.h"
#include "model/fst_state.h"

#define FST_FILE_COLUMN_NORMAL       5
#define FST_FILE_COLUMN_FINAL_STATE  2

#define INIT_STATE                   1
typedef struct {
    fst_state_id         init_state;
    fst_state_id         max_state;

    int                  n_states;
    fst_state_t        **states;

    int                  n_final_states;
    fst_final_state_t  **final_states;

    int                  n_trans;
    int                  n_max_out_trans;
    fst_transition_t   **trans;

    fst_in_alphabet_t   *input_alphabet;
    fst_out_alphabet_t  *output_alphabet;
    fst_label_id         sent_start;
    fst_label_id         sent_end;
    fst_label_id         eps_marker;
} fst_network_t;

fst_network_t *fst_network_new();
int            fst_network_reset(fst_network_t  *net);
int            fst_network_load(fst_network_t *net, const char *fn, const char *isymfn, const char *osymfn);

#endif   /* ----- #ifndef fst_network_H  ----- */
