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

#include "model/fst_common.h"
#include "model/fst_alphabet.h"
#include "model/fst_transition.h"
#include "model/fst_state.h"

typedef struct {
    fst_state_id         init_state;
    fst_state_id         max_state;

    int                  n_states;
    fst_state_t        **states;

    int                  n_final_states;
    fst_final_state_t  **final_states;

    int                  n_trans;
    int                  max_out_tran;
    fst_transition_t   **trans;

    fst_in_alphabet_t   *input_alphabet;
    fst_out_alphabet_t  *output_alphabet;
    fst_label_id         sent_start;
    fst_label_id         sent_end;
} fst_network_t;

#endif   /* ----- #ifndef fst_network_H  ----- */
