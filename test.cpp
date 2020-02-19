#include <iostream>
#include <time.h>
#include <stdlib.h>

int main() {
  srand(time(NULL));
  for (int i; i < 100; ++i) printf("%d\n", rand() % 100);
}
