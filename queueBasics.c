/*
NOTE: edit the functions in the main to use the code
to your prefered liking
---
This is a basic array queue
*/

#include <stdio.h>
#define MAX 50

typedef struct queue
{
    int items[MAX];
    int front;
    int rear;
} queue;

void init(queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int isEmpty(queue *q)
{
    return q->front == -1;
}

int isFull(queue *q)
{
    return q->rear == MAX - 1;
}

void enQueue(queue *q, int val)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
    }
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->items[++q->rear] = val;
    }
}

int dequeue(queue *q)
{
    if (isEmpty(q))
    {
        printf("The queue is empty\n");
        return -1;
    }
    else
    {
        int val = q->items[q->front];
        if (q->front == q->rear)
        {
            q->front = q->rear = -1;
        }
        else
        {
            q->front++;
        }
        return val;
    }
}

void display(queue *q)
{
    if (isEmpty(q))
    {
        printf("Empty\n");
    }
    else
    {
        for (int i = q->front; i <= q->rear; i++)
        {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

int main()
{
    queue q;
    init(&q);

    if (isEmpty(&q))
    {
        printf("Queue is empty initially.\n");
    }

    enQueue(&q, 5);
    enQueue(&q, 10);
    enQueue(&q, 15);
    enQueue(&q, 20);

    printf("Queue after enqueuing 5, 10, 15, 20:\n");
    display(&q);

    int removed = dequeue(&q);
    printf("Dequeued element: %d\n", removed);

    printf("Queue after one dequeue:\n");
    display(&q);

    enQueue(&q, 25);
    enQueue(&q, 30);

    printf("Queue after enqueuing 25 and 30:\n");
    display(&q);

    printf("Dequeuing all elements:\n");
    while (!isEmpty(&q))
    {
        printf("Dequeued: %d\n", dequeue(&q));
    }

    printf("Queue after removing all elements:\n");
    display(&q);

    return 0;
}
