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
    unsigned short    n_tran;
} fst_state_t;

typdef struct {
    fst_state_id state_id;
    real         weight;
} fst_final_state_t;

#endif   /* ----- #ifndef fst_state_H  ----- */

