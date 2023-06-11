#include <stdio.h>

double cubeRootDescent(double x, unsigned int n, double f, unsigned int i, double sum) {
  if (i == 3) f = -x / 3;
  if (n > i - 2) {
    sum += f;
    f = -f * x * (3 * i - 7) / (3 * i - 3);
    sum = cubeRootDescent(x, n, f, i + 1, sum);
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

  printf("Result: %lf\n", cubeRootDescent(x, n, 0, 3, 1));

  return 0;
}