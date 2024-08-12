#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

typedef struct {
    int id;
    int started;
    int ended;
} GanttTask;

void readTasksFromFile(const char *filename, GanttTask tasks[], int *numTasks) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    *numTasks = 0;
    while (fscanf(file, "Task %d: Started: %d, Ended: %d\n", 
                  &tasks[*numTasks].id, 
                  &tasks[*numTasks].started, 
                  &tasks[*numTasks].ended) == 3) {
        (*numTasks)++;
    }

    fclose(file);
}

void printGanttChart(GanttTask tasks[], int numTasks) {
    int i, j;

    printf("+");
    for (i = 0; i < numTasks; i++) {
        int length = tasks[i].ended - tasks[i].started + 1;
        for (j = 0; j < length; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    printf("|");
    for (i = 0; i < numTasks; i++) {
        int length = tasks[i].ended - tasks[i].started + 1;
        printf("Task%d|", tasks[i].id);
    }
    printf("\n");

    printf("+");
    for (i = 0; i < numTasks; i++) {
        int length = tasks[i].ended - tasks[i].started + 1;
        for (j = 0; j < length; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    printf(" ");
    for (i = 0; i < numTasks; i++) {
        printf("%d    ", tasks[i].started);
    }
    printf("%d\n", tasks[numTasks-1].ended);
}

int main() {
    GanttTask tasks[MAX_TASKS];
    int numTasks = 0;       

    readTasksFromFile("SJF.txt", tasks, &numTasks);
    
    printGanttChart(tasks, numTasks);

    return 0;
}
