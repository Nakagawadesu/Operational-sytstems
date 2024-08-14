#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Task
{
    int id;
    int priority;
    int arrival;
    int completness;
    int waiting;
} Task;

Task *createTask(int id, int priority, int arrival, int waiting, int completness)
{
    Task *task = (Task *)malloc(sizeof(Task));
    task->id = id;
    task->priority = priority;
    task->arrival = arrival;
    task->waiting = waiting;
    task->completness = completness;
    return task;
}
Task *InitTask(int n)
{
    Task *tasks = (Task *)malloc(n * sizeof(Task));
    return tasks;
}

void printTasks(Task *task, int n)
{
    printf("\033[34m Tasks \n");
    for (int i = 0; i < n; i++)
    {
        printf("Task %d: Priority: %d, Arrival: %d, Waiting: %d\n", task[i].id, task[i].priority, task[i].arrival, task[i].waiting);
    }
}

typedef struct Solution
{
    int id;
    int started;
    int ended;
    int arrival;

} Solution;

Solution *createSolution(int id, int started, int ended)
{
    Solution *solution = (Solution *)malloc(sizeof(Solution));
    solution->id = id;
    solution->started = started;
    solution->ended = ended;
    return solution;
}

#endif
