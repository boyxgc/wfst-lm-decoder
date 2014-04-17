/*
 * =====================================================================================
 *       Filename:  fst_state.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:26:21
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#ifndef  fst_state_H
#define  fst_state_H

#include "utils/fst_common.h"

typedef struct {
    fst_transition_id tran_start;
    unsigned short    n_trans;
} fst_state_t;

typedef struct {
    fst_state_id state_id;
    real         weight;
} fst_final_state_t;

fst_state_t       *fst_state_new(int                        tran_start, int n_trans);
fst_final_state_t *fst_final_state_new(fst_state_id         st, real weight);
int                fst_state_reset(fst_state_t              *state);
int                fst_final_state_reset(fst_final_state_t  *final_state);
#endif   /* ----- #ifndef fst_state_H  ----- */

