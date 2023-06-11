#include <windows.h>
#include <math.h>
#include "../../headers/properties.h"

void drawArrow(HDC, float, int, int);                                // стрілки
void drawLoops(HDC, double**, int**, int);                           // петлі
void drawMultipleArc(HDC, int, int, int, int);                       // кратні дуги
void drawUpAndDownArc (HDC, int, int, int, int, int, int, int, int); // верхні і нижні дуги
void drawLeftArc(HDC, int, int, int, int, int, int, int);            // ліві дуги
void drawRightArc(HDC, int, int, int, int, int, int, int);           // праві дуги
void drawStraightEdge(HDC, int, int, int, int, int);                 // прямі ребра

void drawEdges(HDC hdc, int **coords, double **matrix, double K, int isDirecred) {
  int n = NUM_VERTICES;
  int radius = RADIUS;
  int k = n;
  int distance = abs(coords[0][0] - coords[0][1]);
  drawLoops(hdc, matrix, coords, isDirecred);
  for (int i = 0; i < n; i++) {
    if (!isDirecred) k = i;
    for (int j = 0; j < k; j++) {
      if (matrix[i][j] && i != j) {
        int x1 = coords[0][i];
        int y1 = coords[1][i];
        int x2 = coords[0][j];
        int y2 = coords[1][j];
        int absx = abs(x1 - x2);
        int absy = abs(y1 - y2);

        if (matrix[j][i] && isDirecred) {
          drawMultipleArc(hdc, x1, y1, x2, y2);

        } else if (((y1 / 100) % 2) && y1 == y2 && absx > distance) {
          drawUpAndDownArc(hdc, i, j, x1, y1, x2, y2, distance, isDirecred);

        } else if (x1 == x2 && x1 < distance && absy > distance) {
          drawLeftArc(hdc, i, j, x1, y1, x2, y2, isDirecred);

        } else if (x1 == x2 && x1 > distance * 3 && absy > distance) {
          drawRightArc(hdc, i, j, x1, y1, x2, y2, isDirecred);
      
        } else {
          drawStraightEdge(hdc, x1, y1, x2, y2, isDirecred);
        }
      }
    }
  }

  freemDouble(matrix);
}


void drawArrow(HDC hdc, float fi, int px, int py) {
  fi = 3.1416 * (180.0 - fi) / 180.0;
  int lx, ly, rx, ry;
  lx = px + 15 * cos(fi + 0.3);
  rx = px + 15 * cos(fi - 0.3);
  ly = py + 15 * sin(fi + 0.3);
  ry = py + 15 * sin(fi - 0.30);
  MoveToEx(hdc, lx, ly, NULL);
  LineTo(hdc, px, py);
  LineTo(hdc, rx, ry);
}

void drawLoops(HDC hdc, double **matrix, int **coords, int isDirected) {
  int n = NUM_VERTICES;
  int radius = RADIUS;
  double indent = radius * 2.5;
   for (int i = 0; i < n; i++) {
    if (matrix[i][i]) {
      int x1 = coords[0][i];
      int y1 = coords[1][i];

      Ellipse(hdc, x1 - indent, y1 - indent, x1, y1);
      if (isDirected) drawArrow(hdc, -10, x1 - radius, y1);
    } 
  }
}

void drawMultipleArc(HDC hdc, int x1, int y1, int x2, int y2) {
  int radius = RADIUS;
  double cx, cy;
  double dx, dy;
  double fi, tanFi;
  int ax, ay;
  if (y1 == y2) {
    cx = (x1 + x2) * 0.5;
    cy = (y1 + y2) * 0.5;
    cy = x2 > x1 ? cy + radius : cy - radius;
    dx = fabs(cx - x2);
    dy = fabs(cy - y2);

    tanFi = dy / dx;
    fi = atan(tanFi) * 180 / 3.1416;
    ax = radius / sqrt(1 + tanFi * tanFi);
    ay = ax * tanFi;

    ax = x2 > x1 ? -ax : ax;
    ay = x2 > x1 ? ay : -ay;
    fi = x2 > x1 ? fi : 180 + fi;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, cx, cy);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, x2, y2);
    drawArrow(hdc, fi, x2 + ax, y2 + ay);

  } else if (x1 == x2) {
    cx = (x1 + x2) * 0.5;
    cx = y2 > y1 ? cx - radius : cx + radius;
    cy = (y1 + y2) * 0.5;
    dx = fabs(cx - x2);
    dy = fabs(cy - y2);

    tanFi = dx / dy;
    fi = atan(tanFi) * 180 / 3.1416;
    ay = radius / sqrt(1 + tanFi * tanFi);
    ax = ay * tanFi;

    ax = y2 > y1 ? -ax : ax;
    ay = y2 > y1 ? -ay : ay;
    fi = y2 > y1 ? -90 + fi : 90 + fi;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, cx, cy);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, x2, y2);
    drawArrow(hdc, fi, x2 + ax, y2 + ay);

  } else if (x2 > x1) {
    cx = (x1 + x2) * 0.5 - radius;
    cy = (y1 + y2) * 0.5 - radius;
    dx = fabs(cx - x2);
    dy = fabs(cy - y2);

    if (dx > dy) {
      tanFi = dx / dy;
      fi = 90 - atan(tanFi) * 180 / 3.1416;
      ay = radius / sqrt(1 + tanFi * tanFi);
      ax = ay * tanFi;
    } else {
      tanFi = dy / dx;
      fi = atan(tanFi) * 180 / 3.1416;
      ax = radius / sqrt(1 + tanFi * tanFi);
      ay = ax * tanFi;
    }

    fi = y2 > y1 ? -fi : fi;
    ay = y2 > y1 ? -ay : ay;
          
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, cx, cy);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, x2, y2);
    drawArrow(hdc, fi, x2 - ax, y2 + ay);

  } else {
    cx = (x1 + x2) * 0.5 + radius;
    cy = (y1 + y2) * 0.5 + radius;
    dx = abs(cx - x2);
    dy = abs(cy - y2);

    if (dx > dy) {
      tanFi = dx / dy;
      fi = 90 - atan(tanFi) * 180 / 3.1416;
      ay = radius / sqrt(1 + tanFi * tanFi);
      ax = ay * tanFi;
    } else {
      tanFi = dy / dx;
      fi = atan(tanFi) * 180 / 3.1416;
      ax = radius / sqrt(1 + tanFi * tanFi);
      ay = ax * tanFi;
    }

    fi = y1 > y2 ? -fi : fi;
    ay = y2 > y1 ? -ay : ay;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, cx, cy);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, x2, y2);
    drawArrow(hdc, fi + 180, x2 + ax, y2 + ay);
  }
}

void drawUpAndDownArc(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int distance, int isDirected) {
  int radius = RADIUS;
  int absx = abs(x1 - x2);
  double cx = (x1 + x2) * 0.5;
  double cy = (y1 + y2) * 0.5;
          
  int k = absx > distance * 2 ? radius * 3 : radius * 4;
  cy = y1 > distance ? cy + k : cy - k;
  double dx = abs(cx - x2);
  double dy = abs(cy - y2);

  double tanFi = dy / dx;
  double fi = atan(tanFi) * 180 / 3.1416;
  int ax = radius / sqrt(1 + tanFi * tanFi);
  int ay = ax * tanFi;

  if (y1 > cy) {
    ax = j > i ? -ax : ax;
    ay = -ay;
    fi = j > i ? -fi : fi - 180;
  } else {
    ax = j > i ? ax : -ax;
    fi = j > i ? -fi - 180 : fi;
  }

  MoveToEx(hdc, x1, y1, NULL);
  LineTo(hdc, cx, cy);
  MoveToEx(hdc, cx, cy, NULL);
  LineTo(hdc, x2, y2);
  if (isDirected) drawArrow(hdc, fi, x2 + ax, y2 + ay);
}

void drawLeftArc(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int isDirected) {
  int radius = RADIUS;
  double cx = (x1 + x2) * 0.5 - radius * 2;
  double cy = (y1 + y2) * 0.5;
  double dx = abs(cx - x2);
  double dy = abs(cy - y2);

  double tanFi = dx / dy;
  double fi = atan(tanFi) * 180 / 3.1416;
  int ay = radius / sqrt(1 + tanFi * tanFi);
  int ax = ay * tanFi;

  ay = j > i ? -ay : ay;
  fi = j > i ? fi - 90 : 90 - fi;

  MoveToEx(hdc, x1, y1, NULL);
  LineTo(hdc, cx, cy);
  MoveToEx(hdc, cx, cy, NULL);
  LineTo(hdc, x2, y2);
  if (isDirected) drawArrow(hdc, fi, x2 - ax, y2 + ay);
}

void drawRightArc(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int isDirected) {
  int radius = RADIUS;
  double cx = (x1 + x2) * 0.5 + radius * 2;
  double cy = (y1 + y2) * 0.5;
  double dx = abs(cx - x2);
  double dy = abs(cy - y2);

  double tanFi = dy / dx;
  double fi = 90 - atan(tanFi) * 180 / 3.1416;
  int ax = radius / sqrt(1 + tanFi * tanFi);
  int ay = ax * tanFi;

  ay = j > i ? -ay : ay;
  fi = j > i ? -fi - 90 : fi + 90;

  MoveToEx(hdc, x1, y1, NULL);
  LineTo(hdc, cx, cy);
  MoveToEx(hdc, cx, cy, NULL);
  LineTo(hdc, x2, y2);
  if (isDirected) drawArrow(hdc, fi, x2 + ax, y2 + ay);
}

void drawStraightEdge(HDC hdc, int x1, int y1, int x2, int y2, int isDirected) {
  int radius = RADIUS;
  int absx = abs(x1 - x2);
  int absy = abs(y1 - y2);
  double cx, cy;
  double fi, tanFi;
  int ax, ay;

  if (y1 == y2) {
    fi = x2 > x1 ? 0 : 180;
    ax = x2 > x1 ? -radius : radius;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    if (isDirected) drawArrow(hdc, fi, x2 + ax, y2);

  } else if (x1 == x2) {
    fi = y2 > y1 ? -90 : 90;
    ay = y2 > y1 ? -radius : radius;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    if (isDirected) drawArrow(hdc, fi, x2, y2 + ay);

  } else if (x2 > x1) {

    if (absx > absy) {
      tanFi = absx / absy;
      fi = 90 - atan(tanFi) * 180 / 3.1416;
      ay = radius / sqrt(1 + tanFi * tanFi);
      ax = ay * tanFi;
    } else {
      tanFi = absy / absx;
      fi = atan(tanFi) * 180 / 3.1416;
      ax = radius / sqrt(1 + tanFi * tanFi);
      ay = ax * tanFi;
    }

      fi = y2 > y1 ? -fi : fi;
      ay = y2 > y1 ? -ay : ay;

      MoveToEx(hdc, x1, y1, NULL);
      LineTo(hdc, x2, y2);
      if (isDirected) drawArrow(hdc, fi, x2 - ax, y2 + ay);

  } else if (x1 > x2) {

    if (absx > absy) {
      tanFi = absx / absy;
      fi = 90 - atan(tanFi) * 180 / 3.1416;
      ay = radius / sqrt(1 + tanFi * tanFi);
      ax = ay * tanFi;
    } else {
      tanFi = absy / absx;
      fi = atan(tanFi) * 180 / 3.1416;
      ax = radius / sqrt(1 + tanFi * tanFi);
      ay = ax * tanFi;
    }

    fi = y1 > y2 ? -fi : fi;
    ay = y2 > y1 ? -ay : ay;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    if (isDirected) drawArrow(hdc, fi + 180, x2 + ax, y2 + ay);
  }
}