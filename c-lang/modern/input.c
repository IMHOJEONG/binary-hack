#include <stdio.h>



int main(void) {
    // 정수
    int n, m; 
    scanf("%d", &n);

    // 엄청 큰 정수
    long long x;
    scanf("%lld, &x");

    // 실수
    double d; 
    scanf("%lf", &d);

    // 여러 값 한 줄 입력 
    int a, b;
    scanf("%d %d", &a, &b);

    // 문자열 입력 
    char s[100];
    scanf("%99s", s);

    // 한 줄 전체 입력 
    char line[256];
    fgets(line, sizeof(line), stdin);

    // for문 최신 
    for (int i = 0; i < n; i++) {

    }

    // for - 역순 
    for (int i = n - 1; i >= 0; i--) {

    }

    // 2중 루프 
    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m ; j++) {

        }
    }

    // while
    int condition = 1;
    while( condition ) {

    }
    do {

    } while (condition);

    // 정적 배열 
    int arr[1000];
    
    for (int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }

    int grid[100][100];

    const int MOD = 100000007;
    

}

int max(int a, int b) {
    return a > b ? a : b;
}

