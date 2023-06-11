#include <windows.h>
#include <math.h>
#include "../../headers/properties.h"

#define START 150

void drawArrow(HDC, float, int, int);                                // стрілки
void drawLoop(HDC, int, int**, int);                           // петлі
void drawUpAndDownArc (HDC, int, int, int, int, int, int, int, int); // верхні і нижні дуги
void drawLeftArc(HDC, int, int, int, int, int, int, int);            // ліві дуги
void drawRightArc(HDC, int, int, int, int, int, int, int);           // праві дуги
void drawStraightEdge(HDC, int, int, int, int, int);                 // прямі ребра
void drawEdge(HDC, int, int, int**, int);        // намалювати ребро (вибірка)

void drawEdge(HDC hdc, int from, int to, int **coords, int weight) {
  int distance = abs(coords[0][0] - coords[0][1]);
  int x1 = coords[0][from];
  int y1 = coords[1][from];
  int x2 = coords[0][to];
  int y2 = coords[1][to];
  int absx = abs(x1 - x2);
  int absy = abs(y1 - y2);

  if (y1 != START + distance && y1 == y2 && absx > distance) {
    drawUpAndDownArc(hdc, from, to, x1, y1, x2, y2, distance, weight);

  } else if (x1 == x2 && x1 < distance && absy > distance) {
    drawLeftArc(hdc, from, to, x1, y1, x2, y2, weight);

  } else if (x1 == x2 && x1 > distance * 3 && absy > distance) {
    drawRightArc(hdc, from, to, x1, y1, x2, y2, weight);
      
  } else {
    drawStraightEdge(hdc, x1, y1, x2, y2, weight);
  }
}

void drawVertex(HDC hdc, int vertex, int x, int y) {
  int radius = RADIUS, dtx = 5;
  char num[2];
  itoa(vertex + 1, num, 10);
  Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
  TextOut(hdc, x - dtx, y - radius / 2, num, 2);
}

void drawArrow(HDC hdc, float fi, int px, int py) {
  fi = 3.1416 * (180.0 - fi) / 180.0;
  int lx, ly, rx, ry;
  lx = px + 15 * cos(fi + 0.3);
  rx = px + 15 * cos(fi - 0.3);
  ly = py + 15 * sin(fi + 0.3);
  ry = py + 15 * sin(fi - 0.3);
  MoveToEx(hdc, lx, ly, NULL);
  LineTo(hdc, px, py);
  LineTo(hdc, rx, ry);
}

void drawLoop(HDC hdc, int vertex, int **coords, int weight) {
  int n = NUM_VERTICES;
  int radius = RADIUS;
  double indent = radius * 2.5;
  char num[1];
  itoa(weight, num, 10);
  int x1 = coords[0][vertex];
  int y1 = coords[1][vertex];
  Ellipse(hdc, x1 - indent, y1 - indent, x1, y1);
  TextOut(hdc, x1 - indent, y1 - indent, num, 1);
}

void drawUpAndDownArc(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int distance, int weight) {
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

  char num[3];
  itoa(weight, num, 10);
  TextOut(hdc, cx + ax, cy + ay, num, 3);
}

void drawLeftArc(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int weight) {
  int radius = RADIUS;
  double cx = (x1 + x2) * 0.5 - radius * 3;
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
  
  char num[3];
  itoa(weight, num, 10);
  TextOut(hdc, cx + ay, cy, num, 3);
}

void drawRightArc(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int weight) {
  int radius = RADIUS;
  double cx = (x1 + x2) * 0.5 + radius * 3;
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
  
  char num[3];
  itoa(weight, num, 10);
  TextOut(hdc, cx + ax, cy, num, 3);
}

void drawStraightEdge(HDC hdc, int x1, int y1, int x2, int y2, int weight) {
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
    
    char num[3];
    itoa(weight, num, 10);
    TextOut(hdc, (x1 + x2) * 0.5, (y1 + y2) * 0.5 - radius, num, 3);

  } else if (x1 == x2) {
    fi = y2 > y1 ? -90 : 90;
    ay = y2 > y1 ? -radius : radius;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    
    char num[3];
    itoa(weight, num, 10);
    TextOut(hdc, (x1 + x2) * 0.5 - radius, (y1 + y2) * 0.5, num, 3);

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
      
    char num[3];
    itoa(weight, num, 10);
    TextOut(hdc, (x1 + x2) * 0.5, (y1 + y2) * 0.5, num, 3);

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
    
    char num[3];
    itoa(weight, num, 10);
    TextOut(hdc, (x1 + x2) * 0.5, (y1 + y2) * 0.5, num, 3);
  }
}