#include "task.h"
#include "queue.h"

#include "linkedList.h"

Solution * SJF(Task * tasks, int nTasks ){
    Queue * queue = createQueue();
    Solution * solutions = (Solution *)malloc(nTasks * sizeof(Solution));
    LinkedList * list = createLinkedList();
      
    for (int i = 0; i < nTasks; i++){
        addNode(list, tasks[i]);
    }
    printf("\033[33m SJF- List \n");
    printList(list);

    while (list->head != NULL){
        Task shortestTask = getShortestTask(list);
        enqueue(queue, shortestTask);
        printList(list);
       
    }

    printf("\033[31m SJF- Queue \n");

    printQueue(queue);

    int currentTime = 0 ;
    Task  currentTask = queue->front->task;
    QueueCell * currentCell = queue->front;
    int currentTaskStarted = currentTime;
    dequeue(queue);

    while ( currentTask.id != NULL){
        
        if(currentTask.completness < currentTask.waiting){
            currentTask.completness++ ;
        }else{
            printf("Task %d is done\n", currentTask.id);
            solutions[currentTask.id] = *createSolution(currentTask.id, currentTaskStarted, currentTime);

            if(currentCell->next != NULL){
                currentCell = currentCell->next;
                currentTask = currentCell->task;
                currentTaskStarted = currentTime;
            }

            dequeue(queue);
            printf("current task is %d\n", currentTask.id);

        }
        printf("current time is %d\n", currentTime);
        currentTime++ ;
    }
    while(currentTask.completness < currentTask.waiting){
        currentTask.completness++;
        currentTime++;
    }
     printf("Task %d is done\n", currentTask.id);
     solutions[currentTask.id] = *createSolution(currentTask.id, currentTaskStarted, currentTime);
    return solutions;
    
}


Solution * FCFS(Task * task, int n ){
  Queue * queue = createQueue();
  Solution * solutions = (Solution *)malloc(n * sizeof(Solution));
  LinkedList * tasksList = createLinkedList();

  int currentTime = 0;
    int currentTaskStarted = 0;
    int finished = 0;
    printTasks(task, n);
    for (int i = 0; i < n; i++){
        printf("Adding task %d\n", task[i].id);
        addNode(tasksList, task[i]);
        
    }
    Task * currentTask = NULL;
    while (!finished){
        for (int i = 0; i < n; i++){
            if(tasksList->head != NULL){
                
            
            if(currentTime >= task[i].arrival){

                if(isInList(tasksList, task[i].id)){
                enqueue(queue, task[i]);
                removeNode(tasksList, task[i].id);
                }
             }
            }

        }   
        printf("\033[30m Current time is %d\n", currentTime);
        printf("Queue size is %d\n", queue->size);
        printf ("\033[33m FCFS - List \n");
        printList(tasksList);
        printf("\033[31m FCFS - Queue \n");
        printQueue(queue);
        if(currentTask == NULL){
            //("Current task is NULL\n");
           if(queue->front != NULL){
               printf("Starting task %d\n", queue->front->task.id);
                currentTask = createTask(queue->front->task.id, queue->front->task.priority, queue->front->task.arrival, queue->front->task.waiting);
               currentTaskStarted = currentTime;
               dequeue(queue);
           }else {
                if(tasksList->head = NULL)
                {
                    finished = 1;
                }
           }

        }else{
            //printf("Current task is not NULL is %d\n" , currentTask->id);
            if(currentTask->completness < currentTask->waiting){
                currentTask->completness++;
            }else{
                solutions[currentTask->id] = *createSolution(currentTask->id, currentTaskStarted, currentTime);
                if(tasksList->head == NULL  && queue->front == NULL){
                    finished = 1;
                }
                currentTask = NULL;
        }
        currentTime++;
    }  

}
return solutions;
}
