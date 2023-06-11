#ifndef PROPERTIES_H
#define PROPERTIES_H

#define NUM_VERTICES 10
#define RADIUS 30

typedef struct Edge {
  int src, dest, weight;
} edge;

double **directedMatrix(double);
double **undirectedMatrix(double);
double **getWeightMatrix(double);
int **getDrawingMatrix();
void freemDouble(double**);
void freemInt(int**);
void freemCoords(int**);

#endif