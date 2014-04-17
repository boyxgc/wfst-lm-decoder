/*
 * =====================================================================================
 *       Filename:  fst_transition.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/17/2014 12:55:31
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "model/fst_transition.h"
#include "utils/fst_common.h"
#include "utils/utils.h"

fst_transition_t * fst_transition_new(fst_state_id to_state, real weight, fst_label_id in, fst_label_id out) {
    fst_transition_t * tran = new fst_transition_t();
    if(!tran) {
        spark_debug("new fst_transition_t faliled \n");
        return NULL;
    }
    tran->to_state     = to_state;
    tran->weight       = weight;
    tran->in_label_id  = in;
    tran->out_label_id = out;

    return tran;
}
