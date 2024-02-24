#include <stdio.h>
#include "Queue.h"

void *Queue_Create(unsigned int max_size , unsigned int *ret_status)
{
    *ret_status = Queue_NOK;
    Queue_t *My_Queue = NULL;
    if (NULL == ret_status)
    {
        *ret_status = Queue_NOK;
    }
    else
    {
        My_Queue = (Queue_t *)malloc(sizeof(Queue_t));
        if (NULL == My_Queue)
        {
            *ret_status = Queue_NOK;
            My_Queue = NULL;
        }
        else
        {
            My_Queue->Queue_array = (void **)calloc(max_size , sizeof(void *));
            if (NULL == My_Queue->Queue_array)
            {
                *ret_status = Queue_NOK;
                My_Queue = NULL;
            }
            else
            {
                My_Queue->Queue_count = 0;
                My_Queue->Queue_front = -1;
                My_Queue->Queue_rear  = -1;
                My_Queue->Queue_max_size  = max_size;
                *ret_status = Queue_OK;
            }
        }
    }
    return My_Queue;

}
void *Queue_Destroy(Queue_t *My_Queue , unsigned int *ret_status)
{
    *ret_status = Queue_NOK;
    if (NULL == My_Queue || NULL == *ret_status)
    {
        *ret_status = Queue_NULL_POINTER;
    }
    else
    {
        free(My_Queue->Queue_array);
        free(My_Queue);
        My_Queue = NULL;
        *ret_status = Queue_OK;
    }
    return NULL;
}
Queue_status Enqueue(Queue_t *My_Queue , void *Element)
{
    Queue_status ret = Queue_NOK;
    if (NULL == My_Queue || NULL == Element)
    {
        ret = Queue_NULL_POINTER;
    }
    else
    {
        if (My_Queue->Queue_count == My_Queue->Queue_max_size)
        {
            ret = Queue_full;
        }
        else
        {
            (My_Queue->Queue_rear)++;
            My_Queue->Queue_array[My_Queue->Queue_rear] = Element;
            (My_Queue->Queue_count)++;
            if ((My_Queue->Queue_rear) == My_Queue->Queue_max_size)
            {
                (My_Queue->Queue_rear) = 0;
            }
            else {/* Nothing */}
            if (1 == (My_Queue->Queue_count))
            {
                (My_Queue->Queue_front) = 0;
            }
            else {/* Nothing */}
            ret = Queue_OK;
    }
    return ret;
    }
}

Queue_status Dequeue(Queue_t *My_Queue , unsigned int *Element)
{
    Queue_status ret = Queue_NOK;

    if (NULL == My_Queue || NULL == Element)
    {
        ret = Queue_NULL_POINTER;
    }
    else
    {
        if (0 == My_Queue->Queue_count)
        {
            ret = Queue_Empty;
        }
        else
        {
            *Element = My_Queue->Queue_array[My_Queue->Queue_front];
            (My_Queue->Queue_front)++;// here is the problem
            if ( (My_Queue->Queue_front) == (My_Queue->Queue_max_size))
            {
                (My_Queue->Queue_front) = 0;
            }
            else {/* Nothing */}
            if ( My_Queue->Queue_count == 1)
            {
                (My_Queue->Queue_count)--;
                My_Queue->Queue_front = -1;
                My_Queue->Queue_rear  = -1;
            }
            else
            {
                (My_Queue->Queue_count)--;
            }
        }
    }
    return ret;
}
Queue_status Queue_Front(Queue_t *My_Queue , unsigned int *Element)
{
    Queue_status ret = 0;
    if (NULL == My_Queue || NULL == Element)
    {
        ret = Queue_NULL_POINTER;
    }
    else
    {
        if (0 == My_Queue->Queue_count)
        {
            ret = Queue_Empty;
        }
        else
        {
            *Element = My_Queue->Queue_array[My_Queue->Queue_front];
            ret = Queue_OK;
        }
    }
    return ret;

}
Queue_status Queue_Rear(Queue_t *My_Queue , unsigned int *Element)
{
     Queue_status ret = 0;
    if (NULL == My_Queue || NULL == Element)
    {
        ret = Queue_NULL_POINTER;
    }
    else
    {
        if (0 == My_Queue->Queue_count)
        {
            ret = Queue_Empty;
        }
        else
        {
            *Element = My_Queue->Queue_array[My_Queue->Queue_rear];
            ret = Queue_OK;
        }
    }
    return ret;
}
Queue_status Queue_Display(Queue_t *My_Queue)
{
    Queue_status ret = Queue_NOK;
    unsigned int counter = My_Queue->Queue_front;
    if (NULL == My_Queue)
    {
        ret = Queue_NULL_POINTER;
    }
    else
    {
        if (0 == My_Queue->Queue_count)
        {
            printf("Queue is empty!!\n");
            ret = Queue_Empty;
        }
        else
        {
            printf("Queue elements are : ");
            while ((My_Queue->Queue_max_size)--)
            {
                printf("%i \t",My_Queue->Queue_array[counter]);
                counter++;
            }
            printf("\n");
            ret = Queue_OK;
        }
    }
    return ret;
}


