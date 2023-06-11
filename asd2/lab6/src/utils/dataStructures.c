#include <stdlib.h>

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

vertex *newVertex(int num) {
  vertex *v = malloc(sizeof(vertex));
  v->num = num;
  v->weight = 0;
  v->dest = NULL;
  v->next = NULL;
  return v;
}

graph *KruskalMST(graph*);

graph *newEmptyGraph(int count) {
  graph *g = malloc(sizeof(graph));
  vertex *start = NULL;
  vertex *curr = NULL; 
  for (int i = 0; i < count; i++) {
    vertex *new = newVertex(i);
    if (start == NULL) {
      start = new;
      curr = new;
    } else {
      curr->next = new;
      curr = new;
    }
    g->startVertex = start;
  }
  return g;
}

void addEdge(graph *g, int src, int dest, int weight) {
  vertex *v = newVertex(dest);
  v->weight = weight;
  vertex *srcVertex = g->startVertex;
  while (srcVertex->num != src) {
    srcVertex = srcVertex->next;
  }
  vertex *destVertex = srcVertex;
  while (destVertex->dest != NULL) {
    destVertex = destVertex->dest;
  }
  destVertex->dest = v;
  
  v = newVertex(src);
  v->weight = weight;
  srcVertex = g->startVertex;
  while (srcVertex->num != dest) {
    srcVertex = srcVertex->next;
  }
  destVertex = srcVertex;
  while (destVertex->dest != NULL) {
    destVertex = destVertex->dest;
  }
  destVertex->dest = v;
}

void removeEdge(graph *g, int src, int dest) {
  vertex *srcVertex = g->startVertex;
  while (srcVertex->num != src) {
    srcVertex = srcVertex->next;
  }
  vertex *destVertex = srcVertex->dest;
  vertex *prev = srcVertex;
  while (destVertex->num != dest) {
    prev = destVertex;
    destVertex = destVertex->dest;
  }
  prev->dest = destVertex->dest;
  free(destVertex);

  srcVertex = g->startVertex;
  while (srcVertex->num != dest) {
    srcVertex = srcVertex->next;
  }
  destVertex = srcVertex->dest;
  prev = srcVertex;
  while (destVertex->num != src) {
    prev = destVertex;
    destVertex = destVertex->dest;
  }
  prev->dest = destVertex->dest;
  free(destVertex);
  
}

void freeGraph(graph *g) {
  vertex *curr = g->startVertex;
  vertex *next;
  while (curr != NULL) {
    vertex *destVertex = curr->dest;
    vertex *destNext;
    while (destVertex != NULL) {
      destNext = destVertex->dest;
      free(destVertex);
      destVertex = destNext;
    }
    next = curr->next;
    free(curr);
    curr = next;
  }
  free(g);
}

graph *newGraph(int count, double **adjMatrix, double **weightMatrix) {
  graph *g = newEmptyGraph(count);
  for (int src = 0; src < count; src++) {
    for (int dest = 0; dest <= src; dest++) {
      if (adjMatrix[src][dest]) {
        addEdge(g, src, dest, (int)weightMatrix[src][dest]);
      }
    }
  }
  return g;
}

int isVisited(visited *vis, int vertex) {
  visited *temp = vis;
  while (temp) {
    if (temp->vertex == vertex) return 1;
    temp = temp->next;
  }
  return 0;
}

visited *addVisited(visited *vis, int vertex) {
  visited *new = malloc(sizeof(visited));
  new->vertex = vertex;
  new->next = vis;
  return new;
}

void freeVisited(visited *vis) {
  while (vis) {
    visited *temp = vis;
    vis = vis->next;
    free(temp);
  }
}

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

void freeQueue(queue *q) {
  while (q->first) {
    dequeue(q);
  }
  free(q);
}
