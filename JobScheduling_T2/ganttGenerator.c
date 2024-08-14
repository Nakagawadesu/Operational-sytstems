#include <stdio.h>
#include <stdlib.h>
#include "task.h"
typedef struct
{
    int id;
    int started;
    int ended;
} GanttTask;

GanttTask *createGanttTask(int id, int started, int ended)
{
    GanttTask *task = (GanttTask *)malloc(sizeof(GanttTask));
    task->id = id;
    task->started = started;
    task->ended = ended;
    return task;
}
GanttTask *InitGanttTask(int n)
{
    GanttTask *tasks = (GanttTask *)malloc(n * sizeof(GanttTask));
    return tasks;
}

GanttTask *readGanttTasks(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return NULL;
    }

    GanttTask *tasks = InitGanttTask(5);
    for (int i = 0; i < 5; i++)
    {
        fscanf(file, "Task %d: Started: %d, Ended: %d\n", &tasks[i].id, &tasks[i].started, &tasks[i].ended);
    }
    fclose(file);

    return tasks;
}
int findMaxEndTime(GanttTask tasks[5])
{
    int maxEndTime = 0;
    for (int i = 0; i < 5; i++)
    {
        if (tasks[i].ended > maxEndTime)
        {
            maxEndTime = tasks[i].ended;
        }
    }
    return maxEndTime;
}

void ganttPrinter(
    GanttTask tasks[5],
    int maxEndTime)
{
    for (int i = 0; i < 5; i++)
    {
        printf("Task %d: ", tasks[i].id);
        for (int j = 0; j <= maxEndTime; j++)
        {
            if (j >= tasks[i].started && j < tasks[i].ended)
            {
                printf("█");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Time  : ");
    for (int j = 0; j <= maxEndTime; j++)
    {
        printf("%d", j % 10);
    }
    printf("\n");
}
float calculateAvarageWaitingTime(Task *tasks, GanttTask *ganttTasks, int n, int maxEndTime)
{
    int waitingTime = 0;
    for (int i = 0; i < n; i++)
    {
        int taskWaitingTime = 0;
        for (int j = 0; j < 5; j++)
        {
            if (ganttTasks[j].id == tasks[i].id)
            {
                taskWaitingTime = ganttTasks[j].started - tasks[i].arrival;

                printf("Task : %d , arrival : %d , started : %d\n", tasks[j].id, tasks[i].arrival, ganttTasks[j].started);
            }
        }
        waitingTime += taskWaitingTime;
    }
    return (float)waitingTime / n;
}

int main()
{

    FILE *file = fopen("daTask.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int n = 0;
    char line[100];

    while (fgets(line, sizeof(line), file))
    {
        n++;
    }
    rewind(file);

    Task *tasks = InitTask(n);

    for (int i = 0; i < n; i++)
    {
        int priority, arrival, waiting;

        fscanf(file, "Task %*d: Priority: %d, Arrival: %d, Waiting: %d\n", &priority, &arrival, &waiting);
        tasks[i] = *createTask(i, priority, arrival, waiting, 0);
    }

    fclose(file);

    GanttTask *Gtasks = readGanttTasks("FCFS.txt");
    int maxEndTime = findMaxEndTime(Gtasks);
    float avgWaitingTime = calculateAvarageWaitingTime(tasks, Gtasks, n, maxEndTime);

    GanttTask *Gtasks2 = readGanttTasks("SJF.txt");
    int maxEndTime2 = findMaxEndTime(Gtasks2);
    float avgWaitingTime2 = calculateAvarageWaitingTime(tasks, Gtasks, n, maxEndTime);

    GanttTask *Gtasks3 = readGanttTasks("PriorityBased.txt");
    int maxEndTime3 = findMaxEndTime(Gtasks3);
    float avgWaitingTime3 = calculateAvarageWaitingTime(tasks, Gtasks3, n, maxEndTime);

    GanttTask *Gtasks4 = readGanttTasks("RR.txt");
    int maxEndTime4 = findMaxEndTime(Gtasks4);
    float avgWaitingTime4 = calculateAvarageWaitingTime(tasks, Gtasks4, n, maxEndTime);

    printf("\033[32m FCFS Gantt Chart\n");
    ganttPrinter(Gtasks, maxEndTime);
    printf("Medium waiting time: %.2f\n", avgWaitingTime);
    printf("\n");

    printf("\033[33m SJF Gantt Chart\n");
    ganttPrinter(Gtasks2, maxEndTime2);
    printf("Medium waiting time: %.2f\n", avgWaitingTime2);

    printf("\n");
    printf("\033[34m Priority Gantt Chart\n");
    ganttPrinter(Gtasks3, maxEndTime3);
    printf("Medium waiting time: %.2f\n", avgWaitingTime3);

    printf("\n");
    printf("\033[36m Round Robin Gantt Chart\n");
    ganttPrinter(Gtasks4, maxEndTime4);
    printf("Medium waiting time: %.2f\\n", avgWaitingTime4);

    return 0;
}
