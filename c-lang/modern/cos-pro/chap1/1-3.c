#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pair {
    int first_num;
    int second_num;
} Pair;


int main() {

    Pair ret;
    int idx = 5;
    char* exp;
    char first_num[10] = {0};
    char second_num[10] = {0};
    // strncpy
    strncpy(first_num, exp, idx);
    strncpy(second_num, exp+idx+1, strlen(exp) - idx);

    ret.first_num = atoi(first_num);
    

}
