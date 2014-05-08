/*
 * =====================================================================================
 *       Filename:  fst_path.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/17/2014 22:45:27
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "fst_path.h"

fst_path_t *fst_path_new() {
    fst_path_t *path = new fst_path_t();
    if(NULL == path) {
        spark_debug("new fst_path_t failed\n");
        return NULL;
    }
    fst_path_reset(path);
    return path;
}

int fst_path_reset(fst_path_t * path) {
    int ret = -1;
    if(NULL == path) {
        spark_debug("reset NULL path\n");
        return ret;
    }
    path->prev      = NULL;
    path->score     = LOG_ZERO;
    path->lm_score  = LOG_ZERO;
    path->label     = 0;
    path->ref_count = 0;
    
    ret = 0;
    return ret;
}

int fst_path_delete(fst_path_t *path) {
    if(NULL == path) {
        return 0;
    }
    fst_path_delete(path->prev);
    delete path;
    return 0;
}
