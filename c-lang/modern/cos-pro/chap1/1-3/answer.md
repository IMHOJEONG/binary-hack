아래 코드는 `"12+34"` 같은 **간단한 2항 산술식(정수 2개 + 연산자 1개)** 를 파싱해서 계산하는 코드야. (공백 없음, 괄호 없음, 음수/다중 연산자 없음 가정)

위에서부터 **한 줄씩** 설명할게.

---

## 1) 헤더

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
```

* `stdio.h` : 입출력(여기선 실제로 안 씀)
* `stdbool.h` : bool(여기선 안 씀)
* `stdlib.h` : `atoi`
* `string.h` : `strlen`, `strncpy`

---

## 2) Pair 구조체

```c
typedef struct Pair{
    int first_num;
    int second_num;
}Pair;
```

* 두 정수(`first_num`, `second_num`)를 묶어서 반환하기 위한 구조체.
* `typedef`로 `struct Pair` 대신 `Pair`로 간단히 쓸 수 있게 함.

---

## 3) func_a: 연산 수행

```c
int func_a(int numA, int numB, char exp){
    if (exp == '+')
        return numA + numB;
    else if (exp == '-')
        return numA - numB;
    else
        return numA * numB;
}
```

* 입력: 정수 2개(`numA`, `numB`)와 연산자(`exp`)
* `exp`가

  * `'+'`면 더함
  * `'-'`면 뺌
  * 그 외는 `'*'`로 간주하고 곱함
    ⚠️ 즉 `'/'` 같은 게 들어오면 곱셈으로 처리되는 버그/가정이 있음.

---

## 4) func_b: 연산자 위치 찾기

```c
int func_b(char* exp){
    int len = strlen(exp);
```

* 문자열 길이를 구함.

```c
    for(int i = 0; i < len; i++){
        char e = exp[i];
```

* 왼쪽부터 한 글자씩 검사.

```c
        if(e == '+' || e == '-' || e == '*')
            return i;
```

* 연산자(+, -, *)를 처음 발견하면 그 인덱스를 반환.

```c
    }
    return -1;
}
```

* 끝까지 못 찾으면 -1 반환 (연산자 없음)

---

## 5) func_c: 숫자 2개로 쪼개기

```c
Pair func_c(char* exp, int idx){
    Pair ret;
```

* 반환할 Pair `ret` 선언.

```c
    char first_num[10] = {0};
    char second_num[10] = {0};
```

* 첫 번째 숫자/두 번째 숫자를 담을 문자열 버퍼(각 10칸).
* `{0}`로 전부 `'\0'`로 초기화 → 문자열로 안전하게 쓰기 위한 장치.

```c
    strncpy(first_num, exp, idx);
```

* `exp`의 앞에서부터 `idx`글자(연산자 전까지)를 `first_num`에 복사.
* 예: `"12+34"`, idx=2 → `"12"`

```c
    strncpy(second_num, exp+idx+1, strlen(exp) - idx);
```

* `exp+idx+1`은 연산자 다음 문자부터 시작.
* 뒤쪽 부분을 `second_num`에 복사.
* 예: `"12+34"` → `"34"`
* ⚠️ 복사 길이를 `strlen(exp) - idx`로 줬는데 실제 두 번째 숫자 길이는 `strlen(exp) - (idx+1)`가 더 정확함.
  그래도 `second_num`이 `{0}`으로 초기화돼 있어서 보통은 문제 없이 끝에 `'\0'`이 남아 문자열이 됩니다.

```c
    ret.first_num = atoi(first_num);
    ret.second_num = atoi(second_num);
```

* 문자열을 정수로 변환.
* 예: `"12"` → 12

```c
    return ret;
}
```

* Pair 반환.

---

## 6) solution: 전체 흐름

```c
int solution(char* expression) {
    int exp_index = func_b(expression);
```

* 연산자 위치를 찾음.

```c
    Pair numbers = func_c(expression, exp_index);
```

* 그 위치를 기준으로 문자열을 두 숫자로 분리해서 정수로 변환.

```c
    int result = func_a(numbers.first_num, numbers.second_num, expression[exp_index]);
```

* 연산자(`expression[exp_index]`)를 이용해 계산 수행.

```c
    return result;
}
```

* 결과 반환.

---

# ⚠️ 이 코드의 한계/주의점 (중요)

1. **연산자가 없으면** `func_b`가 -1 → `func_c`에서 인덱스 -1 사용 → 위험(크래시 가능)
2. **버퍼가 10칸 고정**: 숫자가 9자리 넘으면 overflow 가능
3. **음수 처리 어려움**: 예 `"-3+5"`는 `-`를 연산자로 먼저 잡아버릴 수 있음
4. `func_a`에서 `+,-,*` 외 입력이 오면 전부 `*` 처리됨
5. 공백/다중 연산(예 `1+2+3`)은 지원 안 함

---

원하면 이걸 **(1) 더 안전하게**(에러 처리, 길이 체크), 또는 **(2) 음수/공백/여러 연산자까지 지원**하는 파서 형태로 확장한 버전도 만들어줄게.
