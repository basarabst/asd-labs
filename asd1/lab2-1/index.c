#include <stdio.h>

int main() {

  double matrix[9][7] = {7.0, -0.3, 6.3, 8.0, -0.6, 9.0, 8.0,
                         6.6, -2.0, 6.1, 7.5, -1.0, 4.0, 8.0,
                         5.0, -2.0, 4.0, 7.5, -3.0, 4.0, 8.0,
                         5.0, -2.0, 4.0, 6.0, -6.0, 4.0, 5.3,
                         4.3, -2.0, 4.0, 5.0, -6.0, 3.0, 5.3,
                         4.3, -3.1, 3.0, 5.0, -7.3, 2.0, 4.0,
                         4.0, -4.2, 3.0, 5.0, -8.0, 1.9, 4.0,
                         4.0, -4.2, 3.0, 1.0, -8.0, 1.9, 4.0,
                         4.0, -5.0, 0.0, 1.0, -8.0, 0.5, 3.0};

  int row = sizeof(matrix) / sizeof(matrix[0]);
  int col = sizeof(matrix[0]) / sizeof(double);
  double X;

  // matrix log
  printf("Selected %d × %d matrix:\n", row, col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%.1lf  ", matrix[i][j]);
    }
    printf("\n");
  }

  // algorithm
  printf("Enter the X:\n");
  scanf("%lf", &X);

  for (int j = 0; j < col; j++) {
    int top = 0;
    int down = row-1;
    while (top < down) {
      int i = 0.5*(top+down);
      if (X < matrix[i][j]) {
        top = i+1;
      } else {
        down = i;
      }
    }
    if (X == matrix[down][j]) {
      printf("X is found in column %d at row %d\n", j, down);
    } else {
      printf("X is not found in column %d\n", j);
    }
  }
  getchar();
  return 0;
}