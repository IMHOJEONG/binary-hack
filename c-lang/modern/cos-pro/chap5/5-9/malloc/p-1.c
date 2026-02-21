// 1
#include <stdlib.h>
#include <stdio.h>

int main() {
    
    int *p = malloc(sizeof(int));
    *p = 100;

    printf("%d", *p);
    free(p);
}