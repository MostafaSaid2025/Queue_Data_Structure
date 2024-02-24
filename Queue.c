#include <stdio.h>
#include "Queue.h"
/**
 * @brief Creates a new queue with the specified maximum size.
 * 
 * This function dynamically allocates memory for a new queue structure 
 * and initializes its attributes. The maximum size of the queue is 
 * specified by the parameter max_size. The status of the operation 
 * is returned through the parameter ret_status.
 * 
 * @param max_size The maximum size of the queue.
 * @param ret_status Pointer to an unsigned integer where the status 
 *                   of the operation will be stored.
 *                   Possible values are:
 *                   - Queue_OK: Operation succeeded.
 *                   - Queue_NOK: Operation failed.
 * 
 * @return Pointer to the newly created queue structure if successful, 
 *         otherwise NULL.
 */

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
/**
 * @brief Destroys the queue and releases allocated memory.
 * 
 * This function deallocates memory associated with the specified queue 
 * and sets the queue pointer to NULL. The status of the operation 
 * is returned through the parameter ret_status.
 * 
 * @param My_Queue Pointer to the queue structure.
 * @param ret_status Pointer to an unsigned integer where the status 
 *                   of the operation will be stored.
 *                   Possible values are:
 *                   - Queue_OK: Operation succeeded.
 *                   - Queue_NULL_POINTER: Invalid queue pointer.
 */

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
/**
 * @brief Inserts an element at the rear of the queue.
 * 
 * This function inserts the specified element at the rear of the queue.
 * If the queue is full, the operation fails, and the appropriate status 
 * code is returned.
 * 
 * @param My_Queue Pointer to the queue structure.
 * @param Element Pointer to the element to be inserted.
 * 
 * @return Queue_status indicating the status of the operation.
 */

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

/**
 * @brief Removes and returns the element at the front of the queue.
 * 
 * This function removes and returns the element at the front of the queue.
 * If the queue is empty, the operation fails, and the appropriate status 
 * code is returned.
 * 
 * @param My_Queue Pointer to the queue structure.
 * @param Element Pointer to an unsigned integer where the removed element 
 *                will be stored.
 * 
 * @return Queue_status indicating the status of the operation.
 */

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

/**
 * @brief Retrieves the element at the front of the queue.
 * 
 * This function retrieves the element at the front of the queue without 
 * removing it. If the queue is empty, the operation fails, and the 
 * appropriate status code is returned.
 * 
 * @param My_Queue Pointer to the queue structure.
 * @param Element Pointer to an unsigned integer where the front element 
 *                will be stored.
 * 
 * @return Queue_status indicating the status of the operation.
 */

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
/**
 * @brief Retrieves the element at the rear of the queue.
 * 
 * This function retrieves the element at the rear of the queue without 
 * removing it. If the queue is empty, the operation fails, and the 
 * appropriate status code is returned.
 * 
 * @param My_Queue Pointer to the queue structure.
 * @param Element Pointer to an unsigned integer where the rear element 
 *                will be stored.
 * 
 * @return Queue_status indicating the status of the operation.
 */

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

/**
 * @brief Displays the elements of the queue.
 * 
 * This function displays the elements of the queue. If the queue is empty, 
 * an appropriate message is printed.
 * 
 * @param My_Queue Pointer to the queue structure.
 * 
 * @return Queue_status indicating the status of the operation.
 */

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


