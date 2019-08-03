#ifndef LIST_H
#define List_H_
/*
 * Name: Kevin Green
 * Lab/task: Lab 2 Task 1
 * Date: 2/7/18
 */

typedef struct list {
    void *data;
    struct list *next;
} LIST;

void add(void *data);

void *delete();

LIST *get_start();

#endif