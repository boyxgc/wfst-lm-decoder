/*
 * =====================================================================================
 *       Filename:  utils.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:24:45
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#include "utils/utils.h"


bool isIn(char ch, const char *chs) {
	while(*chs) {
		if(ch == *chs) return true;
		chs++;
	}
	return false;
}

void split(std::string str, std::vector<std::string> &v, const char * delim) {
	v.clear();
	if(str.size() == 0) {
		return;
	}
	int pos_l = 0;
	int pos_r = 0;
	while(pos_l < str.size()){
		while(pos_l < str.size() && isIn(str[pos_l], delim)) {
			pos_l++;
			pos_r++;
		}
		while(pos_r < str.size() && !isIn(str[pos_r], delim)) {
			pos_r++;
		}
		std::string sub = str.substr(pos_l, pos_r - pos_l);
		pos_l = pos_r;
		if(sub.size() > 0){
			v.push_back(sub);
		}
		sub = "";
	}
}
