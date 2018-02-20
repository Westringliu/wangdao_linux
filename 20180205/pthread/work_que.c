#include "work_que.h"

void que_set(pque_t pq,pnode_t pnew)
{
    pthread_mutex_lock(&pq->mutex);
    if(NULL==pq->que_head)
    {
        pq->que_head=pnew;
        pq->que_tail=pnew;
    }else{
        pq->que_tail->pnext=pnew;
        pq->que_tail=pnew;
    }
    pq->que_size++;
    pthread_mutex_unlock(&pq->mutex);
}

void que_get(pque_t pq,pnode_t *p)
{
    *p=pq->que_head;
    pq->que_head=pq->que_head->pnext;
    if(NULL==pq->que_head)
    {
        pq->que_tail=NULL;
    }
    pq->que_size--;
}

