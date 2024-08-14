
#include "scheduling.h"
// #include "FCFS.h"
#include <stdio.h>

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

    printTasks(tasks, n);

    Solution *solutions = SJF(tasks, n);
    printf("\033[35m SJF - solution \n");
    for (int i = 0; i < n; i++)
    {
        printf("Task %d: Started: %d, Ended: %d\n", solutions[i].id, solutions[i].started, solutions[i].ended);
    }

    printf("\n");
    printf("\n");

    Solution *solutions2 = FCFS(tasks, n);
    printf("\033[35m FCFS - solution \n");
    for (int i = 0; i < n; i++)
    {

        printf("Task %d: Started: %d, Ended: %d\n", solutions2[i].id, solutions2[i].started, solutions2[i].ended);
    }

    Solution *solutions3 = priorityBased(tasks, n);
    printf("\033[35m PriorityBased - solution \n");
    for (int i = 0; i < n; i++)
    {
        printf("Task %d: Started: %d, Ended: %d\n", solutions3[i].id, solutions3[i].started, solutions3[i].ended);
    }

    Solution *solutions4 = RoundRobin(tasks, n, 1);
    printf("\033[35m RR - solution \n");
    for (int i = 0; i < n; i++)
    {
        printf("Task %d: Started: %d, Ended: %d\n", solutions4[i].id, solutions4[i].started, solutions4[i].ended);
    }

    free(tasks);

    FILE *file1 = fopen("SJF.txt", "w");
    if (file1 == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file1, "Task %d: Started: %d, Ended: %d\n", solutions[i].id, solutions[i].started, solutions[i].ended);
    }
    fclose(file1);
    free(solutions);

    FILE *file2 = fopen("FCFS.txt", "w");
    if (file2 == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file2, "Task %d: Started: %d, Ended: %d\n", solutions2[i].id, solutions2[i].started, solutions2[i].ended);
    }
    fclose(file2);
    free(solutions2);

    FILE *file3 = fopen("PriorityBased.txt", "w");
    if (file3 == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file3, "Task %d: Started: %d, Ended: %d\n", solutions3[i].id, solutions3[i].started, solutions3[i].ended);
    }
    fclose(file3);
    free(solutions3);

    FILE *file4 = fopen("RR.txt", "w");
    if (file4 == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file4, "Task %d: Started: %d, Ended: %d\n", solutions4[i].id, solutions4[i].started, solutions4[i].ended);
    }
    fclose(file4);

    return 0;
}
