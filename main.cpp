#include <cstdint>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>

#define SIZE 2

// A*B = C
int A[SIZE][SIZE];
int B[SIZE][SIZE];
int C[SIZE][SIZE];

void *multiply(void *thread_id) {

  auto i = reinterpret_cast<std::uintptr_t>(thread_id);

  for (int outer = 0; outer < SIZE; ++outer) {

    int sum = 0;
    for (int col = 0; col < SIZE; ++col) {
      sum += A[i][col] * B[col][outer];
    }
    ::C[i][outer] += sum;
  }
}

int main(void) {

  ::A[0][0] = 2;
  ::A[0][1] = 2;
  ::A[1][0] = 3;
  ::A[1][1] = 4;

  ::B[0][0] = 4;
  ::B[0][1] = 5;
  ::B[1][0] = 6;
  ::B[1][1] = 7;

  pthread_t threads[SIZE];

  int rc;

  for (long thread_id = 0; thread_id < SIZE; ++thread_id) {
    rc = pthread_create(&threads[thread_id], NULL, multiply, (void *)thread_id);
  }

  for (int row = 0; row < SIZE; ++row) {

    for (int col = 0; col < SIZE; ++col) {
      printf("%d ", C[row][col]);
    }
    printf("\n");
  }
  return 0;
}
