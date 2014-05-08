/*
 * =====================================================================================
 *       Filename:  x_queue_node.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/18/2014 20:53:37
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Porject:  Spark
 * =====================================================================================
 */

#include "utils/fst_common.h"

typedef struct x_queue_node {
    x_queue_node *prev;
    x_queue_node *next;

    void         *data;

    x_queue_node():prev(NULL), next(NULL), data(NULL) {}
} x_queue_node_t;

typedef struct x_queue {
    x_queue_node_t *push;
    x_queue_node_t *pop;
    int             length;
    
    x_queue():push(NULL), pop(NULL), length(0){}
} x_queue_t;

x_queue_t *x_queue_new();
int        x_queue_push(x_queue_t    *q, void* data);
int        x_queue_pop(x_queue_t     *q);
int        x_queue_reset(x_queue_t   *q);
int        x_queue_delete(x_queue_t  *q);
