#include <stdio.h>
#include <stdlib.h>
#include "../headers/properties.h"

#define K 0.94

void outputDoubleMatrix(double **matrix) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%.0lf  ", matrix[i][j]);
    }
    printf("\n");
  }
}

void outputIntMatrix(int **matrix) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d  ", matrix[i][j]);
    }
    printf("\n");
  }
}

void outputProperties() {
  double **matrix = undirectedMatrix(K);
  double **weightMatrix = getWeightMatrix(K);

  printf("\nGraph Adjacency Matrix\n");
  outputDoubleMatrix(matrix);
  printf("\nWeight Matrix\n");
  outputDoubleMatrix(weightMatrix);

  freemDouble(matrix);
  freemDouble(weightMatrix);
}


int main() {
  outputProperties();
}