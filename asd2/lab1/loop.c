#include <stdio.h>

double cubeRootLoop(double x, unsigned int n) {
  double sum = 1 - x / 3;
  if (n == 1) sum = 1;
  double f = -x / 3;
  for (int i = 3; i <= n; i++) {
    f = -f * x * (3 * i - 7) / (3 * i - 3);
    sum += f;
  }
  return sum;
}

int main() {
  double x;
  unsigned int n;

  printf("x = ");
  scanf("%lf", &x);
  printf("n = ");
  scanf("%d", &n);

  printf("Result: %lf\n", cubeRootLoop(x, n));

  return 0;
}