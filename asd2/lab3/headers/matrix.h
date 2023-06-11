#ifndef MATRIX_H
#define MATRIX_H

#define NUM_VERTICES 10
#define RADIUS 16

double **directedMatrix();
double **undirectedMatrix();
void freemDouble(double**);
void freemInt(int**);
void freemCoords(int**);

#endif