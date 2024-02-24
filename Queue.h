#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct
{
    void **Queue_array;
    signed int Queue_front;
    signed int Queue_rear;
    unsigned int Queue_max_size;
    unsigned int Queue_count;

}Queue_t;

typedef enum
{
    Queue_NOK = 0,
    Queue_OK,
    Queue_Empty,
    Queue_full,
    Queue_NULL_POINTER,

}Queue_status;

void *Queue_Create(unsigned int max_size , unsigned int *ret_status);
void *Queue_Destroy(Queue_t *My_Queue , unsigned int *ret_status);
Queue_status Enqueue(Queue_t *My_Queue , void *Element);
Queue_status Dequeue(Queue_t *My_Queue , unsigned int *Element);
Queue_status Queue_Front(Queue_t *My_Queue , unsigned int *Element);
Queue_status Queue_Rear(Queue_t *My_Queue , unsigned int *Element);
Queue_status Queue_Display(Queue_t *My_Queue);
#endif // _QUEUE_H
