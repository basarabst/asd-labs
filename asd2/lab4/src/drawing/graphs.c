#include <windows.h>
#include "../../headers/coords.h"
#include "../../headers/properties.h"

#define NUM_VERTICES 10

void drawEdges(HDC, int**, double**, double, int);

void drawGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, double K, int isDirected) {
  int **coords = getVerticesCoords(start);
  double **matrix = isDirected ? directedMatrix(K) : undirectedMatrix(K);
  int radius = RADIUS, dtx = 5;

  HPEN bluePen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
  HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

  SelectObject(hdc, blackPen);
  drawEdges(hdc, coords, matrix, K, isDirected);

  SelectObject(hdc, bluePen);
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

void drawCondensationGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, double K, int isDirected) {
  int **coords = getVerticesCoords(start);
  int radius = RADIUS, dtx = 5;
  double **condensationMatrix = getCondensationAdjacencyByK(K);
  double **matrix = formatMatrix(condensationMatrix);

  HPEN bluePen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
  HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

  SelectObject(hdc, blackPen);
  drawEdges(hdc, coords, matrix, K, isDirected);

  SelectObject(hdc, bluePen);
  int counter = 1;
  for (int i = 0; i < NUM_VERTICES; i++) {
    for (int j = 0; j < NUM_VERTICES; j++) {
      char num[2];
      itoa(counter, num, 10);
      if (condensationMatrix[i][j]) {
        int x = coords[0][i+1];
        int y = coords[1][i+1];
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
        TextOut(hdc, x - dtx, y - radius / 2, num, 2);
        i++;
        counter++;
      }
    }
  }
  freemCoords(coords);
  freemDouble(condensationMatrix);
  freemDouble(matrix);
}