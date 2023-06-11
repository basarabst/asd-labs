#include <windows.h>
#include "../../headers/coords.h"
#include "../../headers/properties.h"
#include "../../headers/dataStructures.h"

#define NUM_VERTICES 10

graph *KruskalMST(graph *mainGraph);
edge getMinEdge(graph *g);

void drawLoops(HDC, graph*, int**, double**);
void drawEdges(HDC, graph*, int**, double**);
void drawEdge(HDC, int, int, int**, int);
void drawVertex(HDC, int, int, int);
void drawLoop(HDC, int, int**, int);

void drawGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, double K) {
  int **coords = getVerticesCoords(start);
  double **adjMatrix = undirectedMatrix(K);
  double **weightMatrix = getWeightMatrix(K);

  graph *mainGraph = newGraph(NUM_VERTICES, adjMatrix, weightMatrix);

  HPEN greenPen = CreatePen(PS_SOLID, 3, RGB(0, 128, 0));
  HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

  SelectObject(hdc, blackPen);
  drawLoops(hdc, mainGraph, coords, weightMatrix);
  drawEdges(hdc, mainGraph, coords, weightMatrix);

  SelectObject(hdc, greenPen);
  for (int j = 0; j < NUM_VERTICES; j++) {
    drawVertex(hdc, j, coords[0][j], coords[1][j]);
  }

  freemCoords(coords);
  freemDouble(adjMatrix);
  freemDouble(weightMatrix);
  freeGraph(mainGraph);
}

void drawPart(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, double K, int *step) {
  int **coords = getVerticesCoords(start);
  double **adjMatrix = undirectedMatrix(K);
  double **weightMatrix = getWeightMatrix(K);

  graph *mainGraph = newGraph(NUM_VERTICES, adjMatrix, weightMatrix);
  graph *spanningTree = KruskalMST(mainGraph);

  int counter = 0;
  edge minEdge;
  while (counter != *step) {
    minEdge = getMinEdge(spanningTree);
    removeEdge(spanningTree, minEdge.src, minEdge.dest);
    counter++;
  }

  HPEN orangePen = CreatePen(PS_SOLID, 3, RGB(255, 140, 0));

  SelectObject(hdc, orangePen);
  drawEdge(hdc, minEdge.src, minEdge.dest, coords, minEdge.weight);
  drawVertex(hdc, minEdge.src, coords[0][minEdge.src], coords[1][minEdge.src]);
  drawVertex(hdc, minEdge.dest, coords[0][minEdge.dest], coords[1][minEdge.dest]);
  
  freemCoords(coords);
  freemDouble(adjMatrix);
  freemDouble(weightMatrix);
  freeGraph(spanningTree);
}

void drawLoops(HDC hdc, graph *g, int **coords, double **weightMatrix) {
  vertex *curr = g->startVertex;
  while (curr != NULL) {
    vertex *destVertex = curr->dest;
    int from = curr->num;
    while (destVertex != NULL) {
      int to = destVertex->num;
      if (from == to) drawLoop(hdc, from, coords, destVertex->weight);
      destVertex = destVertex->dest;
    }
    curr = curr->next;
  }
}

void drawEdges(HDC hdc, graph *g, int **coords, double **weightMatrix) {
  int **drawingMatrix = getDrawingMatrix();
  vertex *curr = g->startVertex;
  while (curr != NULL) {
    vertex *destVertex = curr->dest;
    int from = curr->num;
    while (destVertex != NULL) {
      int to = destVertex->num;
      if (from != to && !drawingMatrix[from][to]) {
        drawEdge(hdc, from, to, coords, destVertex->weight);
        drawingMatrix[to][from] = 1;
      }
      destVertex = destVertex->dest;
    }
    curr = curr->next;
  }
  freemInt(drawingMatrix);
}
