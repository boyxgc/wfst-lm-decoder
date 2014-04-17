/*
 * =====================================================================================
 *       Filename:  fst_common.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/13/2014 13:24:45
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#ifndef  fst_common_H
#define  fst_common_H
#include <stdio.h>
#include <cstring>
#include <string>

typedef unsigned int fst_state_id;
typedef unsigned int fst_label_id;
typedef unsigned int fst_transition_id;
typedef float        real;
typedef std::string  string;

#define LOG_ZERO     -1.0e10
#define MAX_LINE     255

#ifndef DEBUG
#define DEBUG 2
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#undef spark_debug
#define spark_debug(...) printf("%s:%s:%d:", __FILE__, __FUNCTION__, __LINE__); printf(__VA_ARGS__);

#endif   /* ----- #ifndef fst_common_H  ----- */
