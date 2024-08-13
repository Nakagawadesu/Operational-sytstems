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


    
    int finished = 0;

    int currentTime = 0 ;
    Task * currentTask = NULL;
    int currentTaskStarted = 0;

    while (!finished){

        for (int i = 0; i < nTasks; i++){
            if(list->head != NULL){
                if(currentTime >= tasks[i].arrival){
                    if(isInList(list, tasks[i].id)){
                        enqueue(queue, tasks[i]);
                        removeNode(list, tasks[i].id);
                    }
                }
            }
        }

        Task   shortestJob = getShortestTask(list);
        if(queue->front != NULL && shortestJob.id != NULL){
            moveToFront(queue, shortestJob.id);
        }

        printf("\033[30m Current time is %d\n", currentTime);
        printf("Queue size is %d\n", queue->size);
        printf("\033[33m SJF - List \n");
        printList(list);
        printf("\033[31m SJF - Queue \n");
        printQueue(queue);

        if(currentTask == NULL){
            if(queue->front != NULL){
                printf("Starting task %d\n", queue->front->task.id);
                currentTask = createTask(queue->front->task.id, queue->front->task.priority, queue->front->task.arrival, queue->front->task.waiting);
                currentTaskStarted = currentTime;
                dequeue(queue);
            }else{
                if(list->size == 0 && queue->size == 0){
                    finished = 1;
                }
            }
        }else{
            if(currentTask->completness < currentTask->waiting){
                currentTask->completness++;
            }else{
                solutions[currentTask->id] = *createSolution(currentTask->id, currentTaskStarted, currentTime);
                if(list->head == NULL && queue->front == NULL){
                    finished = 1;
                }
                currentTask = NULL;
            }
        }
        currentTime++;
       
    }
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

Solution * priorityBased  ( Task * tasks, int n){
    Queue * queue = createQueue();
    Solution * solutions = (Solution *)malloc(n * sizeof(Solution));
    LinkedList * list = createLinkedList();
    for (int i = 0; i < n; i++){
        addNode(list, tasks[i]);
    }
    printf("\033[33m Priority Based - List \n");
    printList(list);

    int finished = 0;
    int currentTime = 0;
    Task * currentTask = NULL;
    int currentTaskStarted = 0;
    while (!finished){
        for (int i = 0; i < n; i++){
            if(list->head != NULL){
                if(currentTime >= tasks[i].arrival){
                    if(isInList(list, tasks[i].id)){
                        enqueue(queue, tasks[i]);
                        removeNode(list, tasks[i].id);
                    }
                }
            }
        }
        
        Task highestpriority = getHighestPriorityTask(list);
        if(queue->front != NULL && highestpriority.id != NULL  ){
             moveToFront(queue, highestpriority.id); 
             
        }

        printf("\033[30m Current time is %d\n", currentTime);
        printf("Queue size is %d\n", queue->size);
        printf("\033[33m Priority Based - List \n");
        printList(list);
        printf("\033[31m Priority Based - Queue \n");
        printQueue(queue);
        if(currentTask == NULL){
            if(queue->front != NULL){
                printf("Starting task %d\n", queue->front->task.id);
                currentTask = createTask(queue->front->task.id, queue->front->task.priority, queue->front->task.arrival, queue->front->task.waiting);
                currentTaskStarted = currentTime;
                dequeue(queue);
            }else{
                if(list->head == NULL && queue->front == NULL){
                    finished = 1;
                }
            }
        }else{
            if(currentTask->completness < currentTask->waiting){
                currentTask->completness++;
            }else{
                solutions[currentTask->id] = *createSolution(currentTask->id, currentTaskStarted, currentTime);
                if(list->head == NULL && queue->front == NULL){
                    finished = 1;
                }
                currentTask = NULL;
            }
        }
        currentTime++;
    }
    return solutions;
    
}
