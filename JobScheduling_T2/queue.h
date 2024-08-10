
#include "task.h"
typedef struct QueueCell {
    Task task;
    struct QueueCell * next;
} QueueCell;

typedef struct Queue{
    QueueCell * front;
    QueueCell * rear;
    int size;
    int capacity;
} Queue;

QueueCell * createQueueCell(Task task){
    QueueCell * cell = (QueueCell *)malloc(sizeof(QueueCell));
    cell->task = task;
    cell->next = NULL;
    return cell;
}
Queue * createQueue(int capacity){
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void enqueue(Queue * queue, Task task){
    
    if(queue->size == queue->capacity){
        printf("Queue is full\n");
        return;
    }

    QueueCell * cell = createQueueCell(task);
    if(queue->size == 0){
        queue->front = cell;
        queue->rear = cell;
    }else{
        queue->rear->next = cell;
        queue->rear = cell;
    }
    queue->size++;
    return;
}

void dequeue(Queue * queue){
    if(queue->size == 0){
        printf("Queue is empty\n");
        return;
    }
    QueueCell * temporaryCell = queue->front;
    queue->front = queue->front->next;
    free(temporaryCell);
    queue->size--;
    return ;
}

void printQueue(Queue * queue){
    QueueCell * current = queue->front;
    while(current != NULL){
        printf("Task: Priority: %d, Arrival: %d, Waiting: %d\n", current->task.priority, current->task.arrival, current->task.waiting);
        current = current->next;
    }
    return ;
}
