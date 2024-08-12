
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "task.h"

typedef struct Node {
    Task task;
    struct Node * next;
} Node;

typedef struct LinkedList{
    Node * head;
    Node * tail;
    int size;
} LinkedList;

Node * createNode(Task task){
    Node * node = (Node *)malloc(sizeof(Node));
    node->task = task;
    node->next = NULL;
    return node;
}

LinkedList * createLinkedList(){
    LinkedList * list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}




void addNode(LinkedList * list, Task task){
    Node * node = createNode(task);
    if(list->size == 0){
        list->head = node;
        list->tail = node;
    }else{
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
    return;
}



void removeNode(LinkedList * list, int taskId){
    if(list->size == 0){
        printf("List is empty\n");
        return;
    }
    printf("Removing task %d\n", taskId);
    Node * current = list->head;
    Node * previous = NULL;
    while(current != NULL){
        if(current->task.id == taskId){
            if(previous == NULL){
                list->head = current->next;
            }else{
                previous->next = current->next;
            }
            free(current);
            list->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Task not found\n");
    return;
}


void printList(LinkedList * list){
    Node * current = list->head;
    while(current != NULL){
        printf("Task %d: Priority: %d, Arrival: %d, Waiting: %d\n", current->task.id, current->task.priority, current->task.arrival, current->task.waiting);
        current = current->next;
    }
    return;
}

int isInList(LinkedList * list, int taskId){
    Node * current = list->head;
    while(current != NULL){
        if(current->task.id == taskId){
            return 1;
        }
        current = current->next;
    }
    return 0;
}
Task  getShortestTask(LinkedList * list){
    Node * current = list->head;
    Task shortestTask = current->task;
    if(current->next == NULL){
        removeNode(list, current->task.id);

        return shortestTask;
    }
    else{

    while(current != NULL){
        if(current->task.waiting < shortestTask.waiting){
            shortestTask = current->task;
        }
        current = current->next;
    }
    removeNode(list, shortestTask.id);
    return shortestTask;
    }

}


#endif