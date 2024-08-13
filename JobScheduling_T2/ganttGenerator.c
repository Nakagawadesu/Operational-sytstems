#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int started;
    int ended;
} GanttTask;

GanttTask * createGanttTask(int id, int started, int ended) {
    GanttTask * task = (GanttTask *)malloc(sizeof(GanttTask));
    task->id = id;
    task->started = started;
    task->ended = ended;
    return task;
}
GanttTask * InitGanttTask(int n) {
    GanttTask * tasks = (GanttTask *)malloc(n * sizeof(GanttTask));
    return tasks;
}

GanttTask * readGanttTasks(char * filename) {
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }


    GanttTask * tasks = InitGanttTask(5);
    for (int i = 0; i < 5; i++) {
        fscanf(file, "Task %d: Started: %d, Ended: %d\n", &tasks[i].id, &tasks[i].started, &tasks[i].ended);
    }
    fclose(file);

    return tasks;
}
int findMaxEndTime(GanttTask tasks[5]) {
    int maxEndTime = 0;
    for (int i = 0; i < 5; i++) {
        if (tasks[i].ended > maxEndTime) {
            maxEndTime = tasks[i].ended;
        }
    }
    return maxEndTime;
}

void ganttPrinter(
    GanttTask tasks[5],
    int maxEndTime
){
for (int i = 0; i < 5; i++) {
        printf("Task %d: ", tasks[i].id);
        for (int j = 0; j <= maxEndTime; j++) {
            if (j >= tasks[i].started && j < tasks[i].ended) {
                printf("█");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Time  : ");
    for (int j = 0; j <= maxEndTime; j++) {
        printf("%d", j % 10);
    }
    printf("\n");
}

int main() {
   
    GanttTask  * tasks   = readGanttTasks("FCFS.txt");
    int maxEndTime = findMaxEndTime(tasks);
    GanttTask * tasks2 = readGanttTasks("SJF.txt");
    int maxEndTime2 = findMaxEndTime(tasks2);


    printf("\033[32m FCFS Gantt Chart\n");
    ganttPrinter(tasks, maxEndTime);
    printf("\n");
    printf("\033[33m SJF Gantt Chart\n");
    ganttPrinter(tasks2, maxEndTime2);
    



    

    return 0;
}
