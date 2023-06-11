#include <stdlib.h>

#define SEED 2202
#define NUM_VERTICES 10
#define K 0.74

double **randm() {  // рандомні значення від 0 до 2
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

double **mulmr(double **A) {  // множення на коефіцієнт та округлення
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double a = A[i][j] * K;
      A[i][j] = a > 1 ? 1 : 0;
    }
  }
  return A;
}

void freemDouble(double **A) {  // звільнення пам'яті від матриці типу double
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) free(A[i]);
  free(A);
}

void freemInt(int **A) {  // звільнення пам'яті від матриці типу int
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) free(A[i]);
  free(A);
}

void freemCoords(int **coords) {  // звільнення пам'яті від координат
  for (int i = 0; i < 2; i++) free(coords[i]);
  free(coords);
}

double **directedMatrix() { // генерація матриці орієнтованого графа
  double **T = randm();
  double **A = mulmr(T);
  return A;
}


double **undirectedMatrix() { // генерація матриці неорієнтованого графа
  int n = NUM_VERTICES;
  double **A = directedMatrix();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (A[i][j]) A[j][i] = 1;
    }
  }
  return A;
}
