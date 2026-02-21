#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

long long solution(long long num) {


    char data[20];

    snprintf(data, sizeof(data), "%lld", num + 1);


    long long answer = atoll(data);

}