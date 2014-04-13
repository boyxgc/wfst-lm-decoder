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

typedef struct {
    real        score;
    real        lm_score;
    fst_path_t *path;
} fst_token_t;

#define fst_token_cpy(DEST, SRC) memcpy(DEST, SRC, sizeof(fst_token_t))

#endif   /* ----- #ifndef fst_token_H  ----- */
