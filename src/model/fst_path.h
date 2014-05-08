/*
 * =====================================================================================
 *       Filename:  fst_path.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:27:09
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#ifndef  fst_path_H
#define  fst_path_H

#include "utils/fst_common.h"
#include "model/fst_alphabet.h"
#include <vector>
#include <string>

typedef struct fst_path {
    struct fst_path *prev;
    real             score;
    real             lm_score;
    fst_label_id     label;
    unsigned int     ref_count;
} fst_path_t;

fst_path_t *fst_path_new();
int         fst_path_reset(fst_path_t   *path);
int         fst_path_delete(fst_path_t  *path);


#endif   /* ----- #ifndef fst_path_H  ----- */
