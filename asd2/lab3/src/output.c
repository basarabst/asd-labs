#include <stdio.h>
#include "../headers/matrix.h"

void outputMatrix(double **matrix) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    printf("\n");
    for (int j = 0; j < n; j++) {
      printf("%.0lf  ", matrix[i][j]);
    }
  }
  printf("\n");
}

int main() {
  double **directed = directedMatrix();
  double **undirected = undirectedMatrix();

  printf("\nDirected Graph Matrix");
  outputMatrix(directed);
  freemDouble(directed);

  printf("\nUndirected Graph Matrix");
  outputMatrix(undirected);
  freemDouble(undirected);
}