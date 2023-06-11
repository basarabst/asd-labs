#include <stdlib.h>
#include "../../headers/dataStructures.h"
#include "stdio.h"

#define SEED 2202
#define NUM_VERTICES 10

typedef struct SearchMatrices {
  int **treeMatrix;
  int **relativityMatrix;
} matrices;

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

int getVertex(int step, int **matrix) {
  for (int i = 0; i < NUM_VERTICES; i++) {
    if (matrix[i][step]) return i;
  }
  return -1;
}

int getStartVertex(double **adjMatrix) {
  for (int i = 0; i < NUM_VERTICES; i++) {
    for (int j = 0; j < NUM_VERTICES; j++) {
      if (adjMatrix[i][j]) return i;
    }
  }
}

matrices bfs(double **adjMatrix) {
  int n = NUM_VERTICES;
  int counter = 0;
  int **treeMatrix = malloc(n * sizeof(size_t*));
  int **relativityMatrix = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    treeMatrix[i] = calloc(n, sizeof(int));
    relativityMatrix[i] = calloc(n, sizeof(int));
  }

  int startVertex = getStartVertex(adjMatrix);
  int *visited = calloc(n, sizeof(int));
  queue *q = initializeQueue();
  enqueue(q, startVertex);
  visited[startVertex] = 1;

  while (q->first) {
    int vertex = q->first->vertex;
    relativityMatrix[vertex][counter] = 1;
    for (int i = 0; i < n; i++) {
      if (!visited[i] && adjMatrix[vertex][i]) {
        visited[i] = 1;
        treeMatrix[vertex][i] = 1;
        enqueue(q, i);
      }
    }
    counter++;
    dequeue(q);
  }
  free(visited);
  free(q);

  matrices searchMatrices = {treeMatrix, relativityMatrix};

  return searchMatrices;
}

matrices dfs(double **adjMatrix) {
  int n = NUM_VERTICES;
  int counter = 0;
  int **treeMatrix = malloc(n * sizeof(size_t*));
  int **relativityMatrix = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    treeMatrix[i] = calloc(n, sizeof(int));
    relativityMatrix[i] = calloc(n, sizeof(int));
  }

  int startVertex = getStartVertex(adjMatrix);
  int *visited = calloc(n, sizeof(int));
  stack *s = initializeStack();
  push(s, startVertex);
  visited[startVertex] = 1;
  relativityMatrix[startVertex][counter] = 1;
  counter++;

  while (s->top) {
    int vertex = s->top->vertex;
    for (int i = 0; i < n; i++) {
      if (!visited[i] && adjMatrix[vertex][i]) {
        treeMatrix[vertex][i] = 1;
        relativityMatrix[i][counter] = 1;
        visited[i] = 1;
        push(s, i);
        counter++;
        break;
      } else if (i == n - 1) {
        pop(s);
      }
    }
  }
  free(visited);
  free(s);
  
  matrices searchMatrices = {treeMatrix, relativityMatrix};

  return searchMatrices;
}