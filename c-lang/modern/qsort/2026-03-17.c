/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name; 
    int score;
} Student;

int compare(const void* a, const void* b) {
        
    Student* a1 = (Student *) a;
    Student* b1 = (Student *) b;
    
    return a1->score - b1->score == 0 
        ? strcmp(a1->name, b1->name) 
        : b1->score - a1->score;
}

int main() {
    Student datas[5] = {
        {"Kim", 90},
        {"Lee", 85},
        {"Park", 90},
        {"Choi", 70},
        {"Jung", 85}    
    };
    
    qsort(datas, 5, sizeof(Student), compare);
    
    for (int i = 0; i < 5; i++) {
        printf("%s %d\n", datas[i].name, datas[i].score);
    }
    
    return 0;
}