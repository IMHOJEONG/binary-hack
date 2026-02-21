


+6
C언어의 strlen 함수는 string.h 헤더 파일에 정의되어 있으며, 문자열의 길이를 계산하여 size_t 형식으로 반환합니다. 문자열 끝을 알리는 널 문자('\0')를 제외한 실제 문자 개수만 반환하며, 포인터나 배열 모두 사용 가능합니다. 
핵심 요약 및 사용법
헤더: #include <string.h> 필수
형식: size_t strlen(const char *str);
특징: NULL 문자('\0') 직전까지의 길이를 계산
주의: sizeof 연산자는 널 문자를 포함한 전체 메모리 크기를, strlen은 실제 문자 길이만 반환 
코드 예제
c
#include <stdio.h>
#include <string.h> // strlen 사용을 위해 필요

int main() {
    char str[] = "Hello";
    printf("문자열 '%s'의 길이: %zu\n", str, strlen(str)); // 결과: 5
    return 0;
}
참고: strlen은 문자열 내부에 다른 '\0' 문자가 있으면 그곳까지만 길이를 계산하여, 실제 배열 크기와 다를 수 있습니다. 