#include <windows.h>

#define WIDTH 950
#define HEIGHT 800
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 30
#define NUM_VERTICES 10
#define START 150
#define K 0.94

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawGraph(HWND, HDC, PAINTSTRUCT, int, double);
void drawPart(HWND, HDC, PAINTSTRUCT, int, double, int*);

char ProgName[] = "Lab 6";

int step = 0;

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
    "Lab 6. Minimum spanning tree",
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
  
  CreateWindow("BUTTON", "Next", WS_VISIBLE | WS_CHILD,  WIDTH * 0.7, HEIGHT - START, BUTTON_WIDTH, BUTTON_HEIGHT, (HWND)hWnd, (HMENU)1, (HINSTANCE)hInstance, (HINSTANCE)NULL);

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

  switch (messg) {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      drawGraph(hWnd, hdc, ps, START, K);
      step++;
      EndPaint(hWnd, &ps);
    break;

    case WM_COMMAND:
      if (LOWORD(wParam) == 1) {
        hdc = GetDC(hWnd);
        drawPart(hWnd, hdc, ps, START, K, &step);
        if (step == NUM_VERTICES - 1) DestroyWindow(GetDlgItem(hWnd, 1));
        step++;
      }
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
    break;

    default:
      return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
}