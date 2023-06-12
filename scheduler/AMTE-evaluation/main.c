#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define N 80000
char data[N][12];

bool liner_search(const char *key, int size) {
  for (int i = 0; i < size; i++) {
    if (strcmp(key, data[i]) == 0) return true;
  }
  return false;
}

void test(int size) {
  int i = 0;
  while (i < size) {
    sprintf(data[i], "%d", rand());
    if (!liner_search(data[i], i)) i++;
  }
}

int main(void) {
  int rank, size;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  for (int i = 2500; i <= N; i *= 2) {
    clock_t s = clock();
    test(i);
    printf("%d, %.3f\n", i, (double)(clock() - s));
  }
  MPI_Finalize();
  return 0;
}
