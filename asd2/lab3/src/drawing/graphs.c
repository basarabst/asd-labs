#include <windows.h>
#include "../../headers/matrix.h"

#define NUM_VERTICES 10

void drawEdges(HDC, int**, int);
int **getVerticesCoords(int);

void drawGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, int isDirected) {
  int **coords = getVerticesCoords(start);
  int radius = RADIUS, dtx = 5;

  HPEN bluePen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
  HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

  SelectObject(hdc, blackPen);
  drawEdges(hdc, coords, isDirected);

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
