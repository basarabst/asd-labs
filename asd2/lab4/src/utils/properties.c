#include <stdlib.h>
#include <stdio.h>

#define SEED 2202
#define NUM_VERTICES 10

// формування матриці з випадковими значеннями від 0 до 2
double **randm() {
  int n = NUM_VERTICES;
  srand(SEED);
  double **T;
  T = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    T[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      T[i][j] = (double)rand() / (double)RAND_MAX * 2;
    }
  }
  return T;
}

// множення на коефіцієнт та уніфікація матриці (0 або 1)
double **mulmr(double **A, double K) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double a = A[i][j] * K;
      A[i][j] = a > 1 ? 1 : 0;
    }
  }
  return A;
}

// звільнення пам'яті від матриці типу double
void freemDouble(double **A) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) free(A[i]);
  free(A);
}

// звільнення пам'яті від матриці типу int
void freemInt(int **A) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) free(A[i]);
  free(A);
}

// звільнення пам'яті від координат
void freemCoords(int **coords) {
  for (int i = 0; i < 2; i++) free(coords[i]);
  free(coords);
}

// композиція для генерації матриці орієнтованого графа
double **directedMatrix(double K) {
  double **T = randm();
  double **A = mulmr(T, K);
  return A;
}

// композиція для генерації матриці неорієнтованого графа
double **undirectedMatrix(double K) {
  int n = NUM_VERTICES;
  double **A = directedMatrix(K);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (A[i][j] == 1) A[j][i] = 1;
    }
  }
  return A;
}

// степені вершин
int *getDegrees(double **matrix) {
  int n = NUM_VERTICES;
  int *vector;
  vector = malloc(n * sizeof(int));
  int counter;
  for (int i = 0; i < n; i++) {
    counter = 0;
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] && i == j) counter += 2;
      else if (matrix[i][j]) counter++;
    }
    vector[i] = counter;
  }
  return vector;
}

// напівстепені виходу
int *getOutdegrees(double **matrix) {
  int n = NUM_VERTICES;
  int *vector;
  vector = malloc(n * sizeof(int));
  int counter;
  for (int i = 0; i < n; i++) {
    counter = 0;
    for (int j = 0; j < n; j++) {
      if (matrix[i][j]) counter++;
    }
    vector[i] = counter;
  }
  return vector;
}

// напівстепені входу
int *getIndegrees(double **matrix) {
  int n = NUM_VERTICES;
  int *vector;
  vector = malloc(n * sizeof(int));
  int counter;
  for (int j = 0; j < n; j++) {
    counter = 0;
    for (int i = 0; i < n; i++) {
      if (matrix[i][j]) counter++;
    }
    vector[j] = counter;
  }
  return vector;
}

// сума напівстепенів
int *getSumDegrees(int *outdegrees, int *indegrees) {
  int n = NUM_VERTICES;
  int *vector;
  vector = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    vector[i] = outdegrees[i] + indegrees[i];
  }
  return vector;
}

// регулярний граф чи ні
int isRegular(int *degrees) {
  int n = NUM_VERTICES;
  int prev = degrees[0];
  for (int i = 1; i < n; i++) {
    if (degrees[i] != prev) return 0;
    prev = degrees[i];
  }
  return 1;
}

// ізольовані вершини
int *getIsolatedVertices(int *degrees) {
  int n = NUM_VERTICES;
  int *vector = calloc(n, sizeof(int));
  int counter = 0;
  vector[counter] = 0;
  for (int i = 0; i < n; i++) {
    if (!degrees[i]) {
      vector[counter] = i + 1;
      counter++;
    }
  }
  return vector;
}

// висячі вершини
int *getPendantVertices(int *degrees) {
  int n = NUM_VERTICES;
  int *vector = calloc(n, sizeof(int));
  int counter = 0;
  vector[counter] = 0;
  for (int i = 0; i < n; i++) {
    if (degrees[i] == 1) {
      vector[counter] = i + 1;
      counter++;
    }
  }
  return vector;
}

// копіювання матриці
double **copyMatrix(double **matrix) {
  int n = NUM_VERTICES;
  double **copy = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    copy[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
     copy[i][j] = matrix[i][j];
    }
  }
  return copy;
}

// множення матриць
double **multiplyMatrices(double **first, double **second) {
  int n = NUM_VERTICES;
  double **matrix = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
      for (int k = 0; k < n; k++) {
        matrix[i][j] += first[i][k] * second[k][j];
      }
    }
  }
  return matrix;
}

// додавання матриць
double **addMatrices(double **first, double **second) {
  int n = NUM_VERTICES;
  double **matrix = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
     matrix[i][j] = first[i][j] + second[i][j];
    }
  }
  return matrix;
}

// булеве перетворення
void toBoolean(double **matrix) {
  int n = NUM_VERTICES;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j]) matrix[i][j] = 1;
    }
  }
}

// матриця досяжності
double **getReachabilityMatrix(double **matrix) {
  double **copy = copyMatrix(matrix);
  double **sum = copy;
  double **prev = copy;
  double **tempPrev, **tempSum;

  for (int i = 1; i < NUM_VERTICES - 1; i++) {
    tempPrev = multiplyMatrices(prev, matrix);
    tempSum = addMatrices(sum, tempPrev);
    freemDouble(sum);
    freemDouble(prev);
    prev = tempPrev;
    sum = tempSum;
  }

  for (int i = 0; i < NUM_VERTICES; i++) {
    sum[i][i] += 1;
  }

  freemDouble(prev);
  toBoolean(sum);

  return sum;
}

// транспонування матриці
double **transposeMatrix(double **matrix) {
  int n = NUM_VERTICES;
  double **transposedMatrix = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    transposedMatrix[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      transposedMatrix[i][j] = matrix[j][i];
    }
  }
  return transposedMatrix;
}

// поелементне множення матриць
double **multiplyMatricesByElement(double **first, double **second) {
  int n = NUM_VERTICES;
  double **matrix = malloc(n * sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      matrix[i][j] = first[i][j] * second[i][j];
    }
  }
  return matrix;
}

// матриця зв'язності
double **getConnectivityMatrix(double **reachabilityMatrix) {
  double **transposedMatrix = transposeMatrix(reachabilityMatrix);
  double **strongConnectivityMatrix = multiplyMatricesByElement(reachabilityMatrix, transposedMatrix);
  freemDouble(transposedMatrix);
  return strongConnectivityMatrix;
}

// пошук в глибину
void dfs(double **strongConnectivityMatrix, int vertex, double *component, int *visited) {
  visited[vertex] = 1;
  component[vertex] = 1;
  for (int i = 0; i < NUM_VERTICES; i++) {
    if (!visited[i] && strongConnectivityMatrix[vertex][i]) {
      dfs(strongConnectivityMatrix, i, component, visited);
    }
  }
}

// компоненти сильної зв'язності
double **getComponents(double **strongConnectivityMatrix) {
  int n = NUM_VERTICES;
  int *visited = calloc(n, sizeof(int));

  double **components = calloc(n, sizeof(size_t*));
  for (int i = 0; i < n; i++) {
    components[i] = calloc(n, sizeof(double));
  }

  for (int vertex = 0; vertex < n; vertex++) {
    if (!visited[vertex]) {
      dfs(strongConnectivityMatrix, vertex, components[vertex], visited);
    }
  }

  free(visited);
  return components;
}

// визначити кількість вершин (для графа конденсації)
int getNumVertices(double **matrix) {
  int n = NUM_VERTICES;
  int num = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j]) {
        num++;
        i++;
      }
    }
  }
  return num;
}

// перетворення матриці для малювання графа конденсації
double **formatMatrix(double **components) {
  double **matrix = calloc(NUM_VERTICES, sizeof(size_t*));
  for (int i = 0; i < NUM_VERTICES; i++) {
    matrix[i] = calloc(NUM_VERTICES, sizeof(double));
  }

  for(int i = 0; i < NUM_VERTICES; i++) {
    if (!components[0][i]) matrix[1][i+1] = 1;
  }

  return matrix;
}

// матриця суміжності для графа конденсіції
void getCondensationAdjacency(double **components) {
  int numVertices = getNumVertices(components);

  double **matrix = calloc(numVertices, sizeof(size_t*));
  for (int i = 0; i < numVertices; i++) {
    matrix[i] = calloc(numVertices, sizeof(double));
  }

  int columns = 1;
  for (int i = 0; i < NUM_VERTICES; i++) {
    if (!components[0][i]) {
      matrix[0][columns] = 1;
      columns++;
    }
  }

  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      printf("%.0lf  ", matrix[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < numVertices; i++) free(matrix[i]);
  free(matrix);
}

// композиція для отримання компонентів по коефіцієнту
double **getCondensationAdjacencyByK(double K) {
  double **matrix = directedMatrix(K);
  double **reachability = getReachabilityMatrix(matrix);
  double **connectivity = getConnectivityMatrix(reachability);
  double **components = getComponents(connectivity);

  freemDouble(matrix);
  freemDouble(reachability);
  freemDouble(connectivity);
  return components;
}