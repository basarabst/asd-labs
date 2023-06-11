#include <stdlib.h>
#include "../../headers/properties.h"

int **getVerticesCoords(int start) {
  int n = NUM_VERTICES;

  int **coords;
  coords = malloc(n / 5 * sizeof(size_t*));
  for (int i = 0; i < 2; i++) {
    coords[i] = malloc(n * sizeof(int));
  }

  int temp = start;
  for (int j = 0; j < n / 2.5; j++) {
    coords[0][j] = temp;
    coords[1][j] = start;
    temp += 125;
  }

  for (int j = n / 2.5; j < n - 4; j++) {
    coords[0][j] = coords[0][j-1];
    coords[1][j] = coords[1][j-1] + 125;
  }

  for (int j = n - 4; j < n - 1; j++) {
    coords[0][j] = coords[0][j-1] - 125;
    coords[1][j] = coords[1][j-1];
  }

  for (int j = n - 1; j < n; j++) {
    coords[0][j] = coords[0][j-1];
    coords[1][j] = coords[1][j-1] - 125;
  }

  return coords;
}
