#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int price;
    double rating;
} Product;

int cmp(const void* a, const void* b) {
    const Product* p1 = (const Product*)a;
    const Product* p2 = (const Product*)b;

    // 실수 비교 시 주의
    // 평점 내림차순 -> 큰 값이 먼저오도록 수정
    if (p1->rating < p2->rating) return 1;
    if (p1->rating > p2->rating) return -1;

    if (p1->price != p2->price) {
        return p1->price - p2->price;
    }

    return strcmp(p1->name, p2->name);
}

int main() {
    Product products[4] = {
        {"Apple", 1000, 4.5},
        {"Banana", 500, 4.5},
        {"Orange", 800, 4.7},
        {"Grape", 800, 4.5},
    };

    qsort(products, 4, sizeof(Product), cmp);

    for (int i = 0; i < 4; i++) {
        printf("%s %d %.1f\n", products[i].name, products[i].price, products[i].rating);
    }

    return 0;
}