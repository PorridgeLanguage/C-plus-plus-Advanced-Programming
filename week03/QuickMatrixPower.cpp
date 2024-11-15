#include <iostream>
#include <vector>

const long long MOD_NUM = 1e9 + 7;
typedef std::vector<std::vector<long long>> Matrix;

Matrix multiply(const Matrix& A, const Matrix& B, int n) {
  Matrix C(n, std::vector<long long>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        C[i][j] = (C[i][j] + A[i][k] * B[k][j] % MOD_NUM) % MOD_NUM;
      }
    }
  }
  return C;
}

Matrix quick_matrix_power(Matrix A, int p, int n) {
  Matrix result(n, std::vector<long long>(n, 0));
  for (int i = 0; i < n; i++) {
    result[i][i] = 1;
  }
  while (p) {
    if (p & 1) {
      result = multiply(result, A, n);
    }
    A = multiply(A, A, n);
    p >>= 1;
  }
  return result;
}

int main() {
  int n, p;
  std::cin >> n >> p;

  Matrix matrix(n, std::vector<long long>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> matrix[i][j];
    }
  }
  Matrix result = quick_matrix_power(matrix, p, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1; j++) {
      std::cout << result[i][j] << " ";
    }
    std::cout << result[i][n - 1] << "\n";
  }
  return 0;
}