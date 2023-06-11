#include <stdio.h>

double SUM = 1;

double cubeRootBack(double x, unsigned int n) {
  double i = 0;
  int flag = 1;
  if (!(n % 2)) flag = -1;
  if (n == 2){
    i = x / 3;
  } else if (n > 2) {
    i = cubeRootBack(x, n - 1) * x * (3 * n - 7) / (3 * n - 3);
  }
  SUM += flag * i;
  return i;
}

int main() {
  double x;
  unsigned int n;

  printf("x = ");
  scanf("%lf", &x);
  printf("n = ");
  scanf("%d", &n);

  cubeRootBack(x, n);
  printf("Result: %lf\n", SUM);

  return 0;
}