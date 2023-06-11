#include <stdio.h>
#include <stdlib.h>
#include "../headers/properties.h"

#define K1 0.68
#define K2 0.72

void outputMatrix(double **matrix) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%.0lf  ", matrix[i][j]);
    }
    printf("\n");
  }
}

void outputPaths2(double **powMatrix, double**adjMatrix) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if(powMatrix[i][j]) {

        for (int k = 0; k < n; k++) {
          if (adjMatrix[i][k] && adjMatrix[k][j]) {
            printf("%d->%d->%d;  ", i + 1, k + 1, j + 1);
          }
        }
        printf("\n");

      }
    }
  }
}

void outputPaths3(double **powMatrix, double**adjMatrix) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if(powMatrix[i][j]) {

        for (int k = 0; k < n; k++) {  
          for (int m = 0; m < n; m++) {
            if (adjMatrix[i][k] && adjMatrix[k][m] && adjMatrix[m][j]) {
              printf("%d->%d->%d->%d;  ", i + 1, k + 1, m + 1, j + 1);
            }
          }
        }
        printf("\n");

      }
    }
  }
}

void outputComponents(double **matrix) {
  int n = NUM_VERTICES;
  int counter = 1;
  for (int i = 0; i < n; i++) {
    int isNew = 1;
    for (int j = 0; j < n; j++) {
      if(matrix[i][j]) {
        if (isNew) printf("Component %d: {  ", counter);
        printf("%d  ", j + 1);
        isNew = 0;
      }
    }
    if (!isNew) {
      counter++;
      printf("}\n");
    }
  }
}

void outputDegrees(int *degrees) {
  printf("{  ");
  for (int i = 0; i < NUM_VERTICES; i++) {
    printf("%d  ", degrees[i]);
  }
  printf("}\n");
}

void outputVertices(int *vetrices) {
  printf("{  ");
  for (int i = 0; i < NUM_VERTICES && vetrices[i]; i++) {
    printf("%d  ", vetrices[i]);
  }
  printf("}\n");
}

void directedGraphInfo() {
  double **matrix = directedMatrix(K1);
  int *outdegrees = getOutdegrees(matrix);
  int *indegrees = getIndegrees(matrix);
  int *sumDegrees = getSumDegrees(outdegrees, indegrees);
  int *isolatedVertices = getIsolatedVertices(sumDegrees);
  int *pendantVertices = getPendantVertices(sumDegrees);

  printf("\n***Directed Graph Info***\n");

  printf("\nAdjacency matrix\n");
  outputMatrix(matrix);

  printf("\nDegrees of graph vertices (in order of vertices enumeration)\n");
  printf("Outdegrees: ");
  outputDegrees(outdegrees);
  printf("Indegrees: ");
  outputDegrees(indegrees);

  printf("\nGraph regularity: ");
  if (isRegular(sumDegrees)) printf("%d\n", sumDegrees[0]);
  else printf("irregular\n");

  printf("\nVertices (enumeration)\n");
  printf("Isolated: ");
  if (isolatedVertices[0]) outputVertices(isolatedVertices);
  else printf("none\n");
  printf("Pendant: ");
  if (pendantVertices[0]) outputVertices(pendantVertices);
  else printf("none\n");

  
  freemDouble(matrix);
  free(outdegrees);
  free(indegrees);
  free(sumDegrees);
  free(isolatedVertices);
  free(pendantVertices);
}

void undirectedGraphInfo() {
  double **matrix = undirectedMatrix(K1);
  int *degrees = getDegrees(matrix);
  int *isolatedVertices = getIsolatedVertices(degrees);
  int *pendantVertices = getPendantVertices(degrees);

  printf("\n***Undirected Graph Info***\n");

  printf("\nAdjacency matrix\n");
  outputMatrix(matrix);

  printf("\nDegrees of graph vertices (in order of vertices enumeration): ");
  outputDegrees(degrees);

  printf("\nGraph regularity: ");
  if (isRegular(degrees)) printf("%d\n", degrees[0]);
  else printf("irregular\n");

  printf("\nVertices (enumeration)\n");
  printf("Isolated: ");
  if (isolatedVertices[0]) outputVertices(isolatedVertices);
  else printf("none\n");
  printf("Pendant: ");
  if (pendantVertices[0]) outputVertices(pendantVertices);
  else printf("none\n");

  
  freemDouble(matrix);
  free(degrees);
  free(isolatedVertices);
  free(pendantVertices);
}

void modifiedGraphInfo() {
  double **matrix = directedMatrix(K2);
  double **matrixPow2 = multiplyMatrices(matrix, matrix);
  double **matrixPow3 = multiplyMatrices(matrixPow2, matrix);
  int *outdegrees = getOutdegrees(matrix);
  int *indegrees = getIndegrees(matrix);
  int *sumDegrees = getSumDegrees(outdegrees, indegrees);
  int *isolatedVertices = getIsolatedVertices(sumDegrees);
  int *pendantVertices = getPendantVertices(sumDegrees);
  double **reachabilityMatrix = getReachabilityMatrix(matrix);
  double **connectivityMatrix = getConnectivityMatrix(reachabilityMatrix);
  double **components = getComponents(connectivityMatrix);

  printf("\n***Modified Graph Info***\n");

  printf("\nAdjacency Matrix\n");
  outputMatrix(matrix);

  printf("\nDegrees of Graph Vertices (in order of vertices enumeration)\n");
  printf("Outdegrees: ");
  outputDegrees(outdegrees);
  printf("Indegrees: ");
  outputDegrees(indegrees);

  printf("\nGraph Regularity: ");
  if (isRegular(sumDegrees)) printf("%d\n", sumDegrees[0]);
  else printf("irregular\n");

  printf("\nVertices (enumeration)\n");
  printf("Isolated: ");
  if (isolatedVertices[0]) outputVertices(isolatedVertices);
  else printf("none\n");
  printf("Pendant: ");
  if (pendantVertices[0]) outputVertices(pendantVertices);
  else printf("none\n");

  printf("\nMatrix Power of 2\n");
  outputMatrix(matrixPow2);

  printf("\nPaths of Length 2\n");
  outputPaths2(matrixPow2, matrix);

  printf("\nMatrix Power of 3\n");
  outputMatrix(matrixPow3);

  printf("\nPaths of Length 3\n");
  outputPaths3(matrixPow3, matrix);

  printf("\nReachability Matrix\n");
  outputMatrix(reachabilityMatrix);

  printf("\nConnected Matrix\n");
  outputMatrix(connectivityMatrix);

  printf("\nStrongly Connected Components\n");
  outputComponents(components);

  printf("\n**Condensation Graph Adjacency Matrix**\n");
  getCondensationAdjacency(components);
  
  freemDouble(matrix);
  freemDouble(matrixPow2);
  freemDouble(matrixPow3);
  freemDouble(reachabilityMatrix);
  freemDouble(connectivityMatrix);
  freemDouble(components);
  free(outdegrees);
  free(indegrees);
  free(sumDegrees);
  free(isolatedVertices);
  free(pendantVertices);
}

int main() {
  directedGraphInfo();
  undirectedGraphInfo();
  modifiedGraphInfo();
}