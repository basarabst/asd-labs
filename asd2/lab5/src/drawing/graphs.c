#include <windows.h>
#include "../../headers/coords.h"
#include "../../headers/properties.h"

#define NUM_VERTICES 10

void drawEdges(HDC, int**, double**, int);
void drawEdge(HDC, int, int, int**, double**, int);
void drawVertex(HDC, int, int, int);

void drawGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, double K, int isDirected) {
  int **coords = getVerticesCoords(start);
  double **matrix = isDirected ? directedMatrix(K) : undirectedMatrix(K);
  int radius = RADIUS, dtx = 5;

  HPEN greenPen = CreatePen(PS_SOLID, 3, RGB(0, 128, 0));
  HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

  SelectObject(hdc, blackPen);
  drawEdges(hdc, coords, matrix, isDirected);

  SelectObject(hdc, greenPen);
  for (int j = 0; j < NUM_VERTICES; j++) {
    char num[2];
    itoa(j + 1, num, 10);
    int x = coords[0][j];
    int y = coords[1][j];
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    TextOut(hdc, x - dtx, y - radius / 2, num, 2);
  }

  freemCoords(coords);
}

int prev = -1;
void drawSearchComponent(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, double K, int *step, int isBFS) {
  int **coords = getVerticesCoords(start);
  double **adjMatrix = directedMatrix(K);
  matrices searchMatrices = isBFS ? bfs(adjMatrix) : dfs(adjMatrix);
  int **treeMatrix = searchMatrices.treeMatrix;
  int **relativityMatrix = searchMatrices.relativityMatrix;

  int curr = getVertex(*step, relativityMatrix);
  int from = getVertex(curr, treeMatrix);

  HPEN bluePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
  HPEN orangePen = CreatePen(PS_SOLID, 3, RGB(255, 140, 0));

  SelectObject(hdc, orangePen);
  if (*step != NUM_VERTICES && prev != -1) {
    drawEdge(hdc, from, curr, coords, adjMatrix, 1);
    drawVertex(hdc, from, coords[0][from], coords[1][from]);
  }

  if (prev != -1) {
    drawVertex(hdc, prev, coords[0][prev], coords[1][prev]);

  }
  
  SelectObject(hdc, bluePen);
  if (*step != NUM_VERTICES) {
    drawVertex(hdc, curr, coords[0][curr], coords[1][curr]);
  }

  prev = curr;

  freemCoords(coords);
  freemDouble(adjMatrix);
  freemInt(treeMatrix);
  freemInt(relativityMatrix);
}