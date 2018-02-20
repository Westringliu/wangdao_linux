#ifndef __WORK_QUE__
#define __WORK_QUE__
#include "head.h"

typedef struct tag_node{
    int new_fd;
    struct tag_node *pnext;
}node_t,*pnode_t;

typedef struct{
    pnode_t que_head,que_tail;
    int que_capacity;//容量
    int que_size;
    pthread_mutex_t mutex;
}que_t,*pque_t;
void que_set(pque_t,pnode_t);
void que_get(pque_t,pnode_t*);
#endif

