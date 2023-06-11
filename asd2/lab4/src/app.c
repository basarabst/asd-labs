#include <windows.h>

#define WIDTH 600
#define HEIGHT 600
#define START 100
#define K1 0.68
#define K2 0.72

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawGraph(HWND, HDC, PAINTSTRUCT, int, double, int);
void drawCondensationGraph(HWND, HDC, PAINTSTRUCT, int, double, int);

char ProgName[] = "Lab 4";

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
    "Lab 4. Graph characteristics and connectivity",
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

  RECT rect = {0, 0, WIDTH, HEIGHT};
  static BOOL shiftPressed = TRUE;
  static BOOL ctrlPressed = FALSE;
  static BOOL tabPressed = FALSE;
  static BOOL spacePressed = FALSE;

  switch (messg) {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      FillRect(hdc, &rect, WHITE_BRUSH);
      TextOut(hdc, START * 0.5, HEIGHT - START, "Shift - Directed Graph", 22);
      TextOut(hdc, START * 0.5, HEIGHT - START * 0.8, "Ctrl - Undirected Graph", 23);
      TextOut(hdc, WIDTH * 0.5, HEIGHT - START, "Tab - Modified Graph", 20);
      TextOut(hdc, WIDTH * 0.5, HEIGHT - START * 0.8, "Space - Condensation Graph", 26);
      if (shiftPressed) drawGraph(hWnd, hdc, ps, START, K1, 1);
      if (ctrlPressed) drawGraph(hWnd, hdc, ps, START, K1, 0);
      if (tabPressed) drawGraph(hWnd, hdc, ps, START, K2, 1);
      if (spacePressed) drawCondensationGraph(hWnd, hdc, ps, START, K2, 1);
      EndPaint(hWnd, &ps);
      break;

    case WM_KEYDOWN:
    if (wParam == VK_SHIFT) {
      shiftPressed = TRUE;
      ctrlPressed = FALSE;
      tabPressed = FALSE;
      spacePressed = FALSE;
    }
    if (wParam == VK_CONTROL) {
      shiftPressed = FALSE;
      ctrlPressed = TRUE;
      tabPressed = FALSE;
      spacePressed = FALSE;
    }
    if (wParam == VK_TAB) {
      shiftPressed = FALSE;
      ctrlPressed = FALSE;
      tabPressed = TRUE;
      spacePressed = FALSE;
    }
    if (wParam == VK_SPACE) {
      shiftPressed = FALSE;
      ctrlPressed = FALSE;
      tabPressed = FALSE;
      spacePressed = TRUE;
    }
    InvalidateRect(hWnd, NULL, TRUE);
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
}