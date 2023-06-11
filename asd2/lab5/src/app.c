#include <windows.h>

#define WIDTH 950
#define HEIGHT 800
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 30
#define NUM_VERTICES 10
#define START 150
#define K 0.84

int step;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawGraph(HWND, HDC, PAINTSTRUCT, int, double, int);
void drawSearchComponent(HWND, HDC, PAINTSTRUCT, int, double, int*, int);

char ProgName[] = "Lab 5";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
  WNDCLASS w;
  w.lpszClassName = ProgName;
  w.hInstance = hInstance;
  w.lpfnWndProc = WndProc;
  w.hCursor = LoadCursor(NULL, IDC_ARROW);
  w.hIcon = 0;
  w.lpszMenuName = 0;
  w.hbrBackground = WHITE_BRUSH;
  w.style = CS_HREDRAW | CS_VREDRAW;
  w.cbClsExtra = 0;
  w.cbWndExtra = 0;

  if (!RegisterClass(&w)) return 0;

  HWND hWnd;
  MSG lpMsg;

  hWnd = CreateWindow(
    ProgName,
    "Lab 5. Graph search",
    WS_OVERLAPPEDWINDOW,
    10,
    10,
    WIDTH,
    HEIGHT,
    (HWND)NULL,
    (HMENU)NULL,
    (HINSTANCE)hInstance,
    (HINSTANCE)NULL
  );
  
  CreateWindow("Button", "BFS", WS_VISIBLE | WS_CHILD, WIDTH * 0.4, HEIGHT * 0.4, BUTTON_WIDTH * 2, BUTTON_HEIGHT * 2, (HWND)hWnd, (HMENU)1, (HINSTANCE)hInstance, (HINSTANCE)NULL);
  CreateWindow("Button", "DFS", WS_VISIBLE | WS_CHILD, WIDTH * 0.4, HEIGHT * 0.5, BUTTON_WIDTH * 2, BUTTON_HEIGHT * 2, (HWND)hWnd, (HMENU)2, (HINSTANCE)hInstance, (HINSTANCE)NULL);

  ShowWindow(hWnd, nCmdShow);

  int flag;
  while((flag = GetMessage(&lpMsg, hWnd, 0, 0)) != 0) {
    if (flag == -1) return lpMsg.wParam;
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }

  DestroyWindow(hWnd);

  return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;
  HINSTANCE hInstance;
  RECT rect = {0, 0, WIDTH, HEIGHT};

  void createButton(char name[], int x, int y, HMENU num) {
    CreateWindow("BUTTON", name, WS_VISIBLE | WS_CHILD, x, y, BUTTON_WIDTH, BUTTON_HEIGHT, (HWND)hWnd, (HMENU)num, (HINSTANCE)hInstance, (HINSTANCE)NULL);
  }

  void removeButton(int num) {
    DestroyWindow(GetDlgItem(hWnd, num));
  }

  switch (messg) {
    case WM_COMMAND:
      switch (LOWORD(wParam)) {
        case 1:
          hdc = GetDC(hWnd);
          step = 0;
          removeButton(1);
          removeButton(2);
          createButton("Next", WIDTH * 0.4, HEIGHT - START, (HMENU)3);
          FillRect(hdc, &rect, WHITE_BRUSH);
          drawGraph(hWnd, hdc, ps, START, K, 1);
          TextOut(hdc, WIDTH * 0.1, HEIGHT - START * 0.6, "Green - New Vertex", 18);
          TextOut(hdc, WIDTH * 0.4, HEIGHT - START * 0.6, "Blue - Active Vertex", 21);
          TextOut(hdc, WIDTH * 0.6, HEIGHT - START * 0.6, "Orange - Checked Vertex and BFS-Tree Edge", 41);
          drawSearchComponent(hWnd, hdc, ps, START, K, &step, 1);
          step++;
        break;

        case 2:
          hdc = GetDC(hWnd);
          step = 0;
          removeButton(1);
          removeButton(2);
          createButton("Next", WIDTH * 0.4, HEIGHT - START, (HMENU)4);
          FillRect(hdc, &rect, WHITE_BRUSH);
          drawGraph(hWnd, hdc, ps, START, K, 1);
          TextOut(hdc, WIDTH * 0.1, HEIGHT - START * 0.6, "Green - New Vertex", 18);
          TextOut(hdc, WIDTH * 0.4, HEIGHT - START * 0.6, "Blue - Active Vertex", 21);
          TextOut(hdc, WIDTH * 0.6, HEIGHT - START * 0.6, "Orange - Checked Vertex and DFS-Tree Edge", 41);
          drawSearchComponent(hWnd, hdc, ps, START, K, &step, 0);
          step++;
        break;

        case 3:
          hdc = GetDC(hWnd);
          drawSearchComponent(hWnd, hdc, ps, START, K, &step, 1);
          if (step == NUM_VERTICES) removeButton(3);
          step++;
        break;

        case 4:
          hdc = GetDC(hWnd);
          drawSearchComponent(hWnd, hdc, ps, START, K, &step, 0);
          if (step == NUM_VERTICES) removeButton(4);
          step++;
        break;
      }
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
    break;

    default:
      return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
}