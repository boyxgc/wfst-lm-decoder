/*
 * =====================================================================================
 *       Filename:  fst_decoder.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/17/2014 22:05:39
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#include "utils/fst_common.h"
#include "utils/utils.h"
#include "model/fst_network.h"
#include "model/fst_path.h"
#include "model/fst_token.h"

#ifndef  fst_decoder_H
#define  fst_decoder_H

typedef struct {
	fst_network_t *net;
	char * netfn;
	char * isymfn;
	char * osymfn;
} fst_decoder_cfg_t;

typedef struct {
	fst_decoder_cfg_t * cfg;

	std::vector<fst_label_id> input_sent;
	fst_token_t   *init_token;
	fst_token_t   *best_curr_token;
	fst_token_t   *best_final_token;
} fst_decoder_t;

fst_decoder_cfg_t *fst_decoder_cfg_new(const char * net, const char *isym, const char *osym);

fst_decoder_t *fst_decoder_new();
int fst_decoder_reset(fst_decoder_t   *decoder);
int fst_decoder_delete(fst_decoder_t  *decoder);

int fst_decoder_feed(fst_decoder_t *decoder, std::vector<std::string> &v_str);
int fst_decoder_propagate_token(fst_decoder_t *decoder, fst_token_t *token, std::vector<fst_label_id> input, int pos);

#endif   /* ----- #ifndef fst_decoder_H  ----- */
