#include "s21_morphological_analysis.h"
#include "s21_sort_station.h"

#include <stdio.h>

int main() {
    char expression[] = "cos(1 + sin(log(-5) - asin(8))^2)";
    List* RPN = turn_to_rev_pol(expression);
    print_list(*RPN);
    free_all_numbers(RPN);
    destroy_list(RPN);
    free(RPN);
}