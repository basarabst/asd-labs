#include <stdlib.h>

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

queue *initializeQueue() {
  queue *queue = malloc(sizeof(queue));
  queue->first = NULL;
  queue->last = NULL;
  return queue;
}

void enqueue(queue *q, int vertex) {
  element *new = malloc(sizeof(element));
  new->vertex = vertex;
  new->next = NULL;
  element *last = q->last;

  if (!last) {
    q->first = new;
    q->last = new;
  } else {
    q->last->next = new;
    q->last = new;
  }
}

void dequeue(queue *q) {
  element *temp = q->first;
  if (q->first == q->last) {
    q->first = NULL;
    q->last = NULL;
  } else {
    q->first = q->first->next;
  }
  free(temp);
}

stack *initializeStack() {
  stack *s = malloc(sizeof(stack));
  s->top = NULL;
  return s;
}

void push(stack *s, int vertex) {
  element *new = malloc(sizeof(element));
  new->vertex = vertex;
  new->next = s->top;
  s->top = new;
}

void pop(stack *s) {
  element *temp = s->top;
  s->top = s->top->next;
  free(temp);
}