#include <stdio.h>

#include "s21_morphological_analysis.h"
#include "s21_sort_station.h"

int main(int argc, char** argv) {
  double answer = evaluate(argv[argc - 1]);
  printf("%lf\n", answer);
}