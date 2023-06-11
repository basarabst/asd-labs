#ifndef PROPERTIES_H
#define PROPERTIES_H

#define NUM_VERTICES 10
#define RADIUS 16

double **directedMatrix(double);
double **undirectedMatrix(double);
int *getDegrees(double**);
int *getOutdegrees(double**);
int *getIndegrees(double**);
void freemDouble(double**);
void freemInt(int**);
void freemCoords(int**);
int isRegular(int*);
int *getSumDegrees(int*, int*);
int *getIsolatedVertices(int*);
int *getPendantVertices(int*);
double **multiplyMatrices(double**, double**);
double **getReachabilityMatrix(double**);
double **getConnectivityMatrix(double**);
double **getComponents(double**);
void getCondensationAdjacency(double**);
double **getCondensationAdjacencyByK(double);
double **formatMatrix(double**);

#endif