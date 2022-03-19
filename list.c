#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
     List * l = (List*)malloc(sizeof(List));
     l->head = NULL;
     l->tail = NULL;
     l->current = NULL;
     return l;
}

void * firstList(List * list) {
    list->current = list->head;
    if (list->head != NULL)
      return list->head->data;
    return NULL;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->next != NULL)
      list->current = list->current->next;
    else return NULL;
    return list->current->data;
}

void * lastList(List * list) {
    list->current  = list->tail;
    if (list->tail != NULL)
      return list->tail->data;
    return NULL;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if(list->current->prev != NULL)
      list->current = list->current->prev;
    else return NULL;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * n = createNode(data);

    if (list->head == NULL){
        list->head = n;
        list->tail = n;
        list->current = n;
        return;
    }
    n->next = n;
    list->head->prev = n;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void *d = list->current->data;

    if (list->current == list->head){
        list->current->next->prev = NULL;
        list->current = list->current->next;
        list->head = list->current;
    }
    else{
        if (list->current == list->tail){
            list->current->prev->next = NULL;
            list->current = list->current->prev;
            list->tail = list->current;
        }
        else{
            list->current->next->prev = list->current->prev;
            list->current->prev->next = list->current->next;
            list->current = list->current->next;
        }
    }
    return d;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}