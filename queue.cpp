#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct QNode* newNode(int k)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp;
}
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
void enQueue(struct Queue* q, int k)
{

    struct QNode* temp = newNode(k);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}
void deQueue(struct Queue* q)
{
    if (q->front == NULL)
        return;

    struct QNode* temp = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}
void done(struct Queue* q)
{
    
    if (q->front == NULL)
        return;

    struct QNode* temp;
    while (q -> front != NULL)
    {   
        temp = q -> front;
        q->front = q->front->next;
        free(temp);
    }

}
int count(struct Queue *q)
{
    int sum = 0;
    if (q -> front == NULL)
    {
        return 0;
    }
    struct QNode *temp = q -> front;
    while (temp != NULL)
    {
        if (temp -> key != 0)
            sum++;
        temp = temp -> next;
    }
    free(temp);
    return sum;
}
bool IsItEmpty(struct Queue *q)
{
    if (count(q) == 0)
        return true;
    else 
    return false;
}
void make_empty(struct Queue *q)
{
    struct QNode *temp = q -> front;
    while (temp != NULL)
    {
        temp -> key = 0;
        temp = temp -> next;
    }
    free(temp);
}
int count_with_zeros(struct Queue *q)
{
    int sum = 0;
    if (q -> front == NULL)
    {
        return 0;
    }
    struct QNode *temp = q -> front;
    while (temp != NULL)
    {
            sum++;
        temp = temp -> next;
    }
    free(temp);
    return sum;
}
void print(struct Queue *q)
{
    struct QNode *temp = q -> front;
    while (temp != NULL)
    {
        printf("%d ", temp -> key);
        temp = temp -> next;
    }
    printf("\n");
    free(temp);
}
void clone (struct Queue *q, struct Queue *a)
{
    struct QNode * temp = q -> front;
    a -> front = temp;
    a -> rear = temp;
    while (temp != NULL)
    {
        a->rear->next = temp;
        a->rear = temp;
    }
    a -> rear -> next = NULL;
}
