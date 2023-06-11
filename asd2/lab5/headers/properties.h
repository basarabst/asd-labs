#ifndef PROPERTIES_H
#define PROPERTIES_H

#define NUM_VERTICES 10
#define RADIUS 30

typedef struct SearchMatrices {
  int **treeMatrix;
  int **relativityMatrix;
} matrices;

double **directedMatrix(double);
double **undirectedMatrix(double);
void freemDouble(double**);
void freemInt(int**);
void freemCoords(int**);
int getVertex(int, int**);
matrices bfs(double**);
matrices dfs(double**);

#endif