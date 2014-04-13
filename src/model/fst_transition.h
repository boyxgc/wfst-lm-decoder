/*
 * =====================================================================================
 *       Filename:  fst_transition.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:26:49
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#ifndef  fst_transition_H
#define  fst_transition_H

#include "utils/fst_common.h"
#include "model/fst_state.h"

typedef struct {
    fst_state_id to_state;
    real         weight;
    fst_label_id in_label_id;
    fst_label_id out_label_id;
} fst_transition_t;

#endif   /* ----- #ifndef fst_transition_H  ----- */
