#include <stdio.h>
#include "utils.h"

void printNum(double num) {
    if (num == (int)num) {
        printf("%d", (int)num);
    } else {
        printf("%g", num);
    }
}