/*
 * =====================================================================================
 *       Filename:  x_queue.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/19/2014 11:55:07
 *       Compiler:  gcc
 *
 *         Author:  Devin Guocheng Xie (gc), guochenx@usc.edu
 *        Project:  Spark
 * =====================================================================================
 */
#include "x_queue.h"

x_queue_t * x_queue_new() {
    x_queue_t *queue = new x_queue_t();
    if(!queue) {
        spark_debug("new x_queue_t failed\n");
        return NULL;
    }
    queue->push = new x_queue_node();
    queue->pop  = new x_queue_node();
    queue->push->prev = queue->pop;
    queue->pop->next  = queue->push;
    return queue;
}

int x_queue_push(x_queue_t* q, void* data) {
    int ret = -1;
    x_queue_node_t *n = new x_queue_node_t();
    if(NULL == n) {
        spark_debug("push NULL node\n");
        return ret;
    }
    if(NULL == q) {
        spark_debug("push NULL queue\n");
        return ret;
    }
    n->data = data;

    n->next             = q->push;
    q->push->prev->next = n;
    n->prev             = q->push->prev;
    q->push->prev       = n;
    q->length++;
    ret = 0;
    return ret;
}

int x_queue_pop(x_queue_t *q) {
    int ret = -1;
    if(NULL == q) {
        spark_debug("pop NULL queue\n");
        return ret;
    }
    if(q->length == 0) {
        spark_debug("pop empty queue\n");
        return ret;
    }
    x_queue_node_t *tmp = q->pop->next;
    q->pop->next = tmp->next;
    tmp->next->prev = q->pop;
    // if(tmp->data) {
    //     delete tmp->data;
    // }
    delete tmp;
    q->length--;
    ret = 0;
    return ret;
}

int x_queue_reset(x_queue_t *q) {
    int ret = -1;
    if(q == NULL) {
        spark_debug("reset NULL x_queue\n");
        return ret;
    }
    while(q->length) {
        x_queue_pop(q);
    }
    assert(q->length == 0);
    ret = 0;
    return ret;
}

int x_queue_delete(x_queue_t *q) {
    int ret = -1;
    if(NULL == q) {
        spark_debug("delete NULL x_queue\n");
        return ret;
    }
    x_queue_reset(q);
    delete q->push;
    delete q->pop;
    delete q;
    ret = 0;
    return ret;
}
