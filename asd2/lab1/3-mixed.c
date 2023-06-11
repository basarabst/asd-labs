#include <stdio.h>

double cubeRootMixed(double x, unsigned int n, double f, unsigned int i) {
  if (i == 3) f = -x / 3;
  if (n == 1) {
    f = 1;
  } else if (n > 2) {
    f = -f * x * (3 * i - 7) / (3 * i - 3);
    f += cubeRootMixed(x, n - 1, f, i + 1);
  } else {
    f = 1 - x / 3;
  }
  return f;
}

int main() {
  double x;
  unsigned int n;

  printf("x = ");
  scanf("%lf", &x);
  printf("n = ");
  scanf("%d", &n);

  printf("Result: %lf\n", cubeRootMixed(x, n, 1, 3));

  return 0;
}