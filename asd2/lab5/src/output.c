#include <stdio.h>
#include <stdlib.h>
#include "../headers/properties.h"

#define K 0.84

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

void outputAdj() {
  double **matrix = directedMatrix(K);
  printf("\nGraph Adjacency Matrix\n");
  outputDoubleMatrix(matrix);
  freemDouble(matrix);
}

void outputBFS() {
  double **matrix = directedMatrix(K);
  matrices searchMatrices = bfs(matrix);

  printf("\n<--Breadth-First Search-->\n");

  printf("\nSearch Tree Matrix\n");
  outputIntMatrix(searchMatrices.treeMatrix);

  printf("\nRelativity Matrix\n");
  outputIntMatrix(searchMatrices.relativityMatrix);

  freemDouble(matrix);
  freemInt(searchMatrices.treeMatrix);
  freemInt(searchMatrices.relativityMatrix);
}

void outputDFS() {
  double **matrix = directedMatrix(K);
  matrices searchMatrices = dfs(matrix);

  printf("\n<--Depth-First Search-->\n");

  printf("\nSearch Tree Matrix\n");
  outputIntMatrix(searchMatrices.treeMatrix);

  printf("\nRelativity Matrix\n");
  outputIntMatrix(searchMatrices.relativityMatrix);

  freemDouble(matrix);
  freemInt(searchMatrices.treeMatrix);
  freemInt(searchMatrices.relativityMatrix);
}

int main() {
  outputAdj();
  outputBFS();
  outputDFS();
}