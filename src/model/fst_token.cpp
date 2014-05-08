/*
 * =====================================================================================
 *       Filename:  fst_token.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/17/2014 22:38:36
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "model/fst_token.h"

fst_token_t *fst_token_new() {
    fst_token_t * token = new fst_token_t();
    if(!token) {
        spark_debug("new fst_token_t failed\n");
        return NULL;
    }
    fst_token_reset(token);
    return token;
}

int fst_token_reset(fst_token_t *token) {
    int ret = -1;
    if(NULL == token) {
        spark_debug("reset NULL token\n");
        return ret;
    }
    token->score    = LOG_ZERO;
    token->state    = 0;
    token->lm_score = LOG_ZERO;
    token->path     = NULL;
    ret = 0;
    return ret;
}

int fst_token_delete(fst_token_t *token) {
    int ret = -1;
    if(NULL == token) {
        spark_debug("delete NULL token");
        return ret;
    }
    delete token;
    ret = 0;
    return ret;
}

fst_token_pool_t *fst_token_pool_new() {
    fst_token_pool_t *pool = x_queue_new();
    if(!pool) {
        spark_debug("new fst_token_pool failed\n");
        return NULL;
    }
    return pool;
}

int fst_token_pool_reset(fst_token_pool_t *pool) {
    int ret = -1;
    if(!pool) {
        spark_debug("reset NULL fst_token_pool\n");
        return ret;
    }
    ret = x_queue_reset(pool);
    return ret;
}

int fst_token_pool_delete(fst_token_pool_t *pool) {
    int ret = -1;
    if(!pool) {
        spark_debug("delete NULL fst_token_pool\n");
        return ret;
    }
    ret = x_queue_delete(pool);
    return ret;
}

fst_token_t * fst_token_pool_pop(fst_token_pool_t *pool) {
    fst_token_t *token = fst_token_new();
    if(-1 == x_queue_push(pool, (void*)token)) {
        spark_debug("push token failed\n");
        return NULL;
    }
    return token;
}
