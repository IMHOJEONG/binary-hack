#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[20];
    int score;
} Student;

int compare(const void *a, const void *b) {
    Student first = *(Student *)a;
    Student second = *(Student *)b;

    if (first.score > second.score) {
        return -1;
    }

    else if (first.score < second.score) {
        return 1;
    }

    else {
        return 0;
    }
}