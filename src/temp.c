#include "s21_morphological_analysis.h"
#include "s21_sort_station.h"

#include <stdio.h>

int main() {
    char expression[] = "3 + 4 * 2 / (1 - 5)^2";
    List* RPN = turn_to_rev_pol(expression);
    print_list(*RPN);
    free_all_numbers(RPN);
    destroy_list(RPN);
    free(RPN);
}