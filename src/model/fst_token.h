/*
 * =====================================================================================
 *       Filename:  fst_token.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:27:58
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#ifndef  fst_token_H
#define  fst_token_H

#include "utils/fst_common.h"
#include "model/fst_state.h"
#include "model/fst_path.h"
#include "utils/x_queue.h"

typedef struct {
    real        score;
    real        lm_score;
    fst_state_t state_id;
    fst_path_t *path;
} fst_token_t;

fst_token_t *fst_token_new();
int          fst_token_reset(fst_token_t   *token);
int          fst_token_delete(fst_token_t  *token);

#define fst_token_cpy(DEST, SRC) memcpy(DEST, SRC, sizeof(fst_token_t))

typedef x_queue_t fst_token_pool_t;

// fst_token_pool_t *fst_token_pool_new();
// int               fst_token_pool_reset(fst_token_pool_t   *pool);
// int               fst_token_pool_delete(fst_token_pool_t  *pool);
// fst_token_t      *fst_token_pool_pop(fst_token_pool_t     *pool);

#endif   /* ----- #ifndef fst_token_H  ----- */
