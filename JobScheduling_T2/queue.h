
#include "task.h"
typedef struct QueueCell
{
    Task task;
    struct QueueCell *next;
} QueueCell;

typedef struct Queue
{
    QueueCell *front;
    QueueCell *rear;
    int size;
} Queue;

QueueCell *createQueueCell(Task task)
{
    QueueCell *cell = (QueueCell *)malloc(sizeof(QueueCell));
    Task *newTask = createTask(task.id, task.priority, task.arrival, task.waiting, task.completness);
    cell->task = *newTask;
    cell->next = NULL;
    return cell;
}
Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void enqueue(Queue *queue, Task task)
{

    QueueCell *cell = createQueueCell(task);
    if (queue->size == 0)
    {
        queue->front = cell;
        queue->rear = cell;
    }
    else
    {
        queue->rear->next = cell;
        queue->rear = cell;
    }
    queue->size++;
    return;
}

void dequeue(Queue *queue)
{
    if (queue->size == 0)
    {
        printf("Queue is empty\n");
        return;
    }
    QueueCell *temporaryCell = queue->front;
    queue->front = queue->front->next;
    free(temporaryCell);
    queue->size--;
    return;
}
int isInQueue(Queue *queue, int taskId)
{
    QueueCell *current = queue->front;
    while (current != NULL)
    {
        if (current->task.id == taskId)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
void printQueue(Queue *queue)
{
    QueueCell *current = queue->front;
    while (current != NULL)
    {
        printf("Task %d: Priority: %d, Arrival: %d, Waiting: %d\n", current->task.id, current->task.priority, current->task.arrival, current->task.waiting);
        current = current->next;
    }
    return;
}
void sortQueuePriority(Queue *queue)
{
    QueueCell *current = queue->front;
    QueueCell *next = current->next;
    while (current != NULL)
    {
        while (next != NULL)
        {
            if (current->task.priority > next->task.priority)
            {
                Task temp = current->task;
                current->task = next->task;
                next->task = temp;
            }
            next = next->next;
        }
        current = current->next;
    }
    return;
}

void sortQueueShortest(Queue *queue)
{
    QueueCell *current = queue->front;
    QueueCell *next = current->next;
    while (current != NULL)
    {
        while (next != NULL)
        {
            if (current->task.waiting > next->task.waiting)
            {
                Task temp = current->task;
                current->task = next->task;
                next->task = temp;
            }
            next = next->next;
        }
        current = current->next;
    }
    return;
}