#include "task.h"
#include "queue.h"
#include "FCFS.h"
#include "SJF.h"
#include <stdio.h>

int main(){
    FILE *file = fopen("daTask.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int n = 0;
    char line[100];  

    while (fgets(line, sizeof(line), file)) {
        n++;
    }
    rewind(file);  

    Task *tasks = InitTask(n); 

    for(int i = 0; i < n; i++){
        int priority, arrival, waiting;
     
        fscanf(file, "Task %*d: Priority: %d, Arrival: %d, Waiting: %d\n", &priority, &arrival, &waiting);
        tasks[i] = *createTask(priority, arrival, waiting);
    }

    fclose(file);  

    printTasks(tasks, n);  

    free(tasks);

    return 0;
}
