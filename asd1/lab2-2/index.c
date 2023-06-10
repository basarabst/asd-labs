#include <stdio.h>

//matrix log
void logging(int matrix[9][7], int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%d  ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {

  int matrix[9][7] = {7, -1, 6, 8, -7, 9, 8,
                      6, -2, 6, 7, -3, 4, 7,
                      3, -2, 4, 6, -5, 5, 8,
                      5, -4, 1, 8, -6, 4, 5,
                      4, -2, 4, 5, -5, 3, 7,
                      0, -3, 3, 2, -7, 2, 4,
                      4, -4, 1, 5, -8, 1, 2,
                      0, -8, 3, 1, -4, 4, 4,
                      4, -5, 0, 1, -7, 0, 3};

  int row = sizeof(matrix) / sizeof(matrix[0]);
  int col = sizeof(matrix[0]) / sizeof(int);

  //before
  printf("Initial %d × %d matrix:\n", row, col);
  logging(matrix, row, col);

  //algorithm
  int i, j, k;
  int T;
  for (int i = 0; i < row; i++) {
    for (int j = 1; j < col; j++) {
      T = matrix[i][j];
      k = j;
      while(T > matrix[i][k-1] && k > 0) {
        matrix[i][k] = matrix[i][k-1];
        k -= 1;
      }
      matrix[i][k] = T;
    }
  }

  //after
  printf("\nSorted %d × %d matrix:\n", row, col);
  logging(matrix, row, col);

  return 0;
}