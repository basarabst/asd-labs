#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Vertex {
  int num;
  int weight;
  struct Vertex *dest;
  struct Vertex *next;
} vertex;

typedef struct Graph {
  vertex *startVertex;
} graph;


typedef struct Visited {
  int vertex;
  struct Visited *next;
} visited;

typedef struct Element {
  int vertex;
  struct Element *next;
} element;

typedef struct Queue {
  element *first;
  element *last;
} queue;



vertex *newVertex(int);
graph *newEmptyGraph(int);
void addEdge(graph*, int, int, int);
void removeEdge(graph*, int, int);
void freeGraph(graph*);
graph *newGraph(int, double**, double**);

queue *initializeQueue();
void enqueue(queue*, int);
void dequeue(queue*);
void freeQueue(queue*);

int isVisited(visited*, int);
visited *addVisited(visited*, int);
void freeVisited(visited *vis);

#endif