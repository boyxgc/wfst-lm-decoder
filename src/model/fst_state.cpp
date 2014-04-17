/*
 * =====================================================================================
 *       Filename:  fst_state.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/17/2014 12:44:45
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "model/fst_state.h"
#include "utils/fst_common.h"
#include "utils/utils.h"

fst_state_t * fst_state_new(int tran_start, int n_trans) {
    fst_state_t * state = new fst_state_t();
    if(!state) {
        spark_debug("new fst_state_t failed\n");
        return NULL;
    }
    state->tran_start = tran_start;
    state->n_trans    = n_trans;
    return state;
}

int fst_state_reset(fst_state_t * state) {
    int ret = -1;
    if(state == NULL) {
        spark_debug("state NULL\n");
        return ret;
    }
    state->tran_start = 0;
    state->n_trans    = 0;
    ret = 0;
    return ret;
}

fst_final_state_t * fst_final_state_new(fst_state_id id, real weight) {
    fst_final_state_t *state = new fst_final_state_t();
    if(!state) {
        spark_debug("new fst_final_state_t failed\n");
        return NULL;
    }
    state->state_id = id;
    state->weight   = weight;
    return state;
}

int fst_final_state_reset( fst_final_state_t * state) {
    int ret = -1;
    if(NULL == state) {
        spark_debug("final state NULL\n");
        return ret;
    }
    state->state_id = 0;
    state->weight   = LOG_ZERO;
    ret = 0;
    return ret;
}
