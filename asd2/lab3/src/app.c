#include <windows.h>

#define WIDTH 600
#define HEIGHT 600
#define START 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawGraph(HWND, HDC, PAINTSTRUCT, int, int);

char ProgName[] = "Lab 3";

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
    "Lab 3. Graphic representation of graphs",
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

  switch (messg) {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      FillRect(hdc, &rect, WHITE_BRUSH);
      TextOut(hdc, WIDTH * 0.5, HEIGHT - START, "press: Shift - directed, Ctrl - undirected", 42);
      if (shiftPressed) drawGraph(hWnd, hdc, ps, START, 1);
      if (ctrlPressed) drawGraph(hWnd, hdc, ps, START, 0);
      EndPaint(hWnd, &ps);
      break;

    case WM_KEYDOWN:
    if (wParam == VK_SHIFT) {
      shiftPressed = TRUE;
      ctrlPressed = FALSE;
    }
    if (wParam == VK_CONTROL) {
      shiftPressed = FALSE;
      ctrlPressed = TRUE;
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