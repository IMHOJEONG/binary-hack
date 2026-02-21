#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Student {
    int student_number;
    int rank;
} Student;

int compare(const void *a, const void *b) {
    Student first = *(Student *)a;
    Student second = *(Student *)b;

    if (first.rank < second.rank) {
        return -1;
    }
    else if (first.rank > second.rank) {
        return 1;
    }
    else {
        return 0;
    }
}

int* solution(int student_numbers[], int student_numbers_len, 
    int ranks[], 
    int ranks_len
) {

    int len = student_numbers_len;
    Student* students = (Student*) malloc(
        sizeof(Student) * len
    );

    for (int i = 0; i < len ; i++) {
        students[i].student_number = student_numbers[i];
        students[i].rank = ranks[i];
    }


    qsort(students, len, sizeof(Student), compare);

    int* answer = (int*) malloc(sizeof(int)*len);

    for (int i = 0; i < len ; i++) {
        answer[i] = students[i].student_number;
    }

    return answer;


}