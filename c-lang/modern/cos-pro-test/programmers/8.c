// 다음과 같이 include를 사용할 수 있습니다.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int min(int a, int b) {
    return a > b ? b : a;
}
int cmp(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

int solution(int arr[], int arr_len, int K) {
    // 여기에 코드를 작성해주세요.
    int answer = 0;
    
    int *test = malloc(sizeof(int) * arr_len);
    for (int i = 0; i < arr_len ; i++) {
        test[i] = arr[i];
    }
    
    qsort(test, arr_len, sizeof(int), cmp);
    // for (int i = 0; i < arr_len ; i++) {
    //     printf("%d ", test[i]);
    // }
    // printf("%d \n");
    
    int minV = 10001;
    for (int i = 0; i < arr_len - (K-1); i++) {
        // printf("%d \n", test[i+K-1] - test[i]);
        minV = min(minV, test[i+K-1] - test[i]);
    }
    
    
    return minV;
}

// 아래는 테스트케이스 출력을 해보기 위한 main 함수입니다.
int main() {
    int arr[] = {9, 11, 9, 6, 4, 19};
    int arr_len = 6;
    int K = 4;
    int ret = solution(arr, arr_len, K);

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    printf("solution 함수의 반환 값은 %d 입니다.\n", ret);
}