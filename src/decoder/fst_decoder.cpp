/*
 * =====================================================================================
 *       Filename:  fst_decoder.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/17/2014 22:06:51
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */

#include "decoder/fst_decoder.h"

const fst_token_t NULL_TOKEN = {LOG_ZERO, LOG_ZERO, 0, NULL};

fst_decoder_cfg_t *fst_decoder_cfg_new(const char * net, const char *isym, const char *osym){
	fst_decoder_cfg_t *cfg = new fst_decoder_cfg_t();
	if(NULL == cfg){
		spark_debug("new cfg failed\n");
		return NULL;
	}
	cfg->net = fst_network_new();
	fst_network_load(cfg->net, net, isym, osym);
	strcpy(cfg->netfn, net);
	strcpy(cfg->isymfn, isym);
	strcpy(cfg->osymfn, osym);
	return cfg;
}

fst_decoder_t *fst_decoder_new(const char * net, const char *isym, const char *osym) {
	fst_decoder_t *decoder = new fst_decoder_t();
	if(NULL == decoder) {
		spark_debug("new decoder failed\n");
		return NULL;
	}
	decoder->cfg = fst_decoder_cfg_new(net, isym, osym);
	fst_token_cpy(decoder->init_token, &NULL_TOKEN);
	fst_token_cpy(decoder->best_curr_token, &NULL_TOKEN);
	fst_token_cpy(decoder->best_final_token, &NULL_TOKEN);

	decoder->init_token->state_id = decoder->cfg->net->init_state;
	return decoder;
}

int fst_decoder_feed(fst_decoder_t *decoder, std::vector<std::string> &v_str) {
	int ret = -1;
	if(decoder == NULL) {
		spark_debug("feed NULL decoder\n");
		return ret;
	}
	fst_alphabet_sym2id(decoder->cfg->net->input_alphabet, v_str, decoder->input_sent);
	ret = fst_decoder_propagate_token(decoder, decoder->init_token, 0);
	if(ret == -1) {
		spark_debug("propagate token failed\n");
		return ret;
	}
	ret = 0;
	return ret;
}

int fst_decoder_propagate_token(fst_decoder_t *decoder, fst_token_t *token, int pos){
	int ret = -1;
	fst_network_t *net = decoder->cfg->net;
	fst_state_t *state = net->states[token->state_id];
}
