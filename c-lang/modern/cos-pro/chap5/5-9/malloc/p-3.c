// 3
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 0;
    scanf("%d", &n);

    int *p = malloc(sizeof(int) * n);

    for (int i = 0; i < n ; i++) {
        p[i] = i * 10;
        printf("%d\n", p[i]);
    }

}