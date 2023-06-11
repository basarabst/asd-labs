#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Element {
  int vertex;
  struct Element *next;
} element;

typedef struct Queue {
  element *first;
  element *last;
} queue;

typedef struct Stack {
  element *top;
} stack;

queue *initializeQueue();
void enqueue(queue*, int);
void dequeue(queue*);
stack *initializeStack();
void push(stack*, int);
void pop(stack*);

#endif