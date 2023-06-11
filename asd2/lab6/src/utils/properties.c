#include <stdlib.h>
#include <math.h>
#include "../../headers/dataStructures.h"

#define SEED 2202
#define NUM_VERTICES 10

typedef struct Edge {
  int src, dest, weight;
} edge;

// формування матриці з випадковими значеннями від 0 до 2
double **randm() {
  int n = NUM_VERTICES;
  srand(SEED);
  double **T;
  T = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    T[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      T[i][j] = (double)rand() / (double)RAND_MAX * 2;
    }
  }
  return T;
}

// множення на коефіцієнт та уніфікація матриці (0 або 1)
double **mulmr(double **A, double K) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double a = A[i][j] * K;
      A[i][j] = a > 1 ? 1 : 0;
    }
  }
  return A;
}

// звільнення пам'яті від матриці типу double
void freemDouble(double **A) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) free(A[i]);
  free(A);
}

// звільнення пам'яті від матриці типу int
void freemInt(int **A) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) free(A[i]);
  free(A);
}

// звільнення пам'яті від координат
void freemCoords(int **coords) {
  for (int i = 0; i < 2; i++) free(coords[i]);
  free(coords);
}

// композиція для генерації матриці орієнтованого графа
double **directedMatrix(double K) {
  double **T = randm();
  double **A = mulmr(T, K);
  return A;
}

// композиція для генерації матриці неорієнтованого графа
double **undirectedMatrix(double K) {
  int n = NUM_VERTICES;
  double **A = directedMatrix(K);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (A[i][j] == 1) A[j][i] = 1;
    }
  }
  return A;
}

// створення службової матриці для малювання
int **getDrawingMatrix() {
  int n = NUM_VERTICES;
  int **matrix = malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i++) {
    matrix[i] = calloc(n, sizeof(int));
  }
  return matrix;
}

// поелементне множення
double **multByElement(double **first, double **second) {
  int n = NUM_VERTICES;
  double **matrix = malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      matrix[i][j] = first[i][j] * second[i][j];
    }
  }
  return matrix;
}

// множення на трикутну матрицю
double **multByTr(double **matrix) {
  for (int i = 0; i < NUM_VERTICES; i++) {
    for (int j = 0; j <= i; j++) {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

// додавання матриць
double **addMatrices(double **first, double **second) {
  int n = NUM_VERTICES;
  double **matrix = malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      matrix[i][j] = first[i][j] + second[i][j];
    }
  }
  return matrix;
}

// формування матриці Wt
double **getWtMatrix(double K) {
  int n = NUM_VERTICES;
  double **adjMatrix = undirectedMatrix(K);
  double **randmMatrix = randm();
  double **matrix = multByElement(randmMatrix, adjMatrix);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = round(matrix[i][j] * 100);
    }
  }

  freemDouble(adjMatrix);
  freemDouble(randmMatrix);
  return matrix;
}

// формування матриці В
double **getBMatrix(double **wtMatrix) {
  int n = NUM_VERTICES;
  double **matrix = malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i++) {
    matrix[i] = calloc(n, sizeof(double));
    for (int j = 0; j < n; j++) {
      if (wtMatrix[i][j]) matrix[i][j] = 1;
    }
  }
  return matrix;
}

// формування матриці С
double **getCMatrix(double **wtMatrix) {
  int n = NUM_VERTICES;
  double **BMatrix = getBMatrix(wtMatrix);
  double **matrix = malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i++) {
    matrix[i] = calloc(n, sizeof(double));
    for (int j = 0; j < n; j++) {
      if (BMatrix[i][j] != BMatrix[j][i]) matrix[i][j] = 1;
    }
  }
  freemDouble(BMatrix);
  return matrix;
}

// формування матриці D
double **getDMatrix(double **wtMatrix) {
  int n = NUM_VERTICES;
  double **BMatrix = getBMatrix(wtMatrix);
  double **matrix = malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i++) {
    matrix[i] = calloc(n, sizeof(double));
    for (int j = 0; j < n; j++) {
      if (BMatrix[i][j] && BMatrix[j][i]) matrix[i][j] = 1;
    }
  }
  freemDouble(BMatrix);
  return matrix;
}

// композиція для формування матриці ваг
double **getWeightMatrix(double K) {
  int n = NUM_VERTICES;
  double **wtMatrix = getWtMatrix(K);
  double **CMatrix = getCMatrix(wtMatrix);
  double **DMatrix = getDMatrix(wtMatrix);

  multByTr(DMatrix);
  double **sumMatrix = addMatrices(DMatrix, CMatrix);
  wtMatrix = multByElement(sumMatrix, wtMatrix);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (wtMatrix[i][j]) {
        wtMatrix[j][i] = wtMatrix[i][j];
      }
    }
  }

  freemDouble(CMatrix);
  freemDouble(DMatrix);
  freemDouble(sumMatrix);
  return wtMatrix;
}

// мінімальне ребро
edge getMinEdge(graph *g) {
  edge minEdge;
  int minWeight = __INT_MAX__;
  vertex *curr = g->startVertex;
  while (curr != NULL) {
    vertex *destVertex = curr->dest;
    int from = curr->num;
    while (destVertex != NULL) {
      int to = destVertex->num;
      if (destVertex->weight < minWeight && from != to) {
        minEdge.src = from;
        minEdge.dest = to;
        minEdge.weight = destVertex->weight;
        minWeight = destVertex->weight;
      }
      destVertex = destVertex->dest;
    }
    curr = curr->next;
  }
  return minEdge;
}

// знаходження потрібної вершини
vertex *getVertex(graph *g, int num) {
  vertex *some = g->startVertex;
  while (some->num != num) some = some->next;
  return some;
}

// перевірка, чи є ребро хордою на основі пошуку існуючого маршруту
int isChord(graph *spanningTree, int u, int v) {
  visited *vis = malloc(sizeof(visited));
  queue *q = initializeQueue();

  vis->vertex = u;
  vis->next = NULL;
  enqueue(q, u);

  while (q->first) {
    vertex *curr = getVertex(spanningTree, q->first->vertex)->dest;
    while (curr) {
      if (curr->num == v) {
        freeQueue(q);
        freeVisited(vis);
        return 1;
      } else if (!isVisited(vis, curr->num)) {
        vis = addVisited(vis, curr->num);
        enqueue(q, curr->num);
      }
      curr = curr->dest;
    }
    dequeue(q);
  }
  free(q);
  freeVisited(vis);
  return 0;
}

// алгоритм Краскала
graph *KruskalMST(graph *mainGraph) {
  int counter = 0;
  graph *spanningTree = newEmptyGraph(NUM_VERTICES);
  while (counter != NUM_VERTICES - 1) {
    edge minEdge = getMinEdge(mainGraph);
    removeEdge(mainGraph, minEdge.src, minEdge.dest);
    if(!isChord(spanningTree, minEdge.src, minEdge.dest)) {
      addEdge(spanningTree, minEdge.src, minEdge.dest, minEdge.weight);
      counter++;
    }
  }
  freeGraph(mainGraph);
  return spanningTree;
}
