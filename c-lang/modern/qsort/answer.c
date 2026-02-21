/**
 * 특히 헷갈리는 포인트 3개만 콕 집기

cmp에서 왜 *(char**)a 임?

qsort는 비교 함수에 “원소 자체”가 아니라 원소의 주소를 void*로 넘겨.

지금 원소 타입은 char* (문자열 포인터)

그래서 a는 “char* 원소의 주소” → 타입으로 치면 char**

*(char**)a 하면 그 주소에 들어있는 “실제 char*”를 꺼내는 거야.

for가 i <= n 까지 도는 이유

i == n일 때는 i < n이 false라서 무조건 else로 가고,

그 else에서 마지막 그룹을 출력하게 되는 트릭이야.

즉, 마지막 그룹 출력용 “가짜 한 번 더” 반복.

정렬 후 카운트가 가능한 이유

정렬하면 같은 문자열이 연속으로 붙음

그래서 한 번 훑으면서 연속 구간 길이만 세면 됨.
 */

#include <stdio.h>     // printf 같은 입출력 함수
#include <stdlib.h>    // qsort, malloc/free 등 표준 라이브러리
#include <string.h>    // strcmp 같은 문자열 함수

int cmp(const void* a, const void* b) {           // qsort가 호출하는 비교 함수
    return strcmp(*(char**)a, *(char**)b);        // a,b는 "원소의 주소" -> char*로 꺼내서 문자열 비교
}

int main() {
    char* arr[] = {"Java", "C++", "Javascript", "Java"}; // 문자열 포인터 배열(문자열 리터럴을 가리킴)
    int n = sizeof(arr) / sizeof(arr[0]);               // 전체 원소 개수 계산

    qsort(arr, n, sizeof(char*), cmp);                  // arr를 문자열 사전순으로 정렬

    int count = 1;                                      // 현재 보고 있는 문자열의 개수(연속 구간 카운트)

    for (int i = 1; i <= n; i++) {                      // i=1부터 시작, i==n까지 도는 게 포인트(마지막 출력 처리)
        if (i < n && strcmp(arr[i], arr[i - 1]) == 0) { // 아직 범위 안(i<n)이고, 현재==이전이면
            count++;                                    // 같은 문자열이 연속이므로 카운트 증가
        } else {                                        // 다르거나(i==n 포함) 끝났으면
            printf("[\"%s\", %d]\n", arr[i - 1], count); // 직전 문자열과 누적 카운트를 출력
            count = 1;                                   // 다음 문자열 카운트는 1부터 다시 시작
        }
    }

    return 0;                                           // 정상 종료
}