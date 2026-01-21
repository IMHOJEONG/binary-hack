좋은 질문이에요.
이 5개 헤더는 **“알고리즘 문제를 풀 때 가장 자주 쓰이는 C 표준 기능들을 한 번에 커버하기 위한 최소 세트”**라고 보면 됩니다.

아래에서 **각 헤더를 왜 포함하는지 + 안 쓰면 어떤 문제가 생기는지**까지 같이 정리할게요.

---

## 1️⃣ `#include <stdio.h>` — 입출력의 핵심

### 왜 필요?

* 표준 입력/출력 함수 제공

### 대표 기능

```c
printf, scanf
fgets, getchar, putchar
FILE, stdin, stdout
```

### 알고리즘에서 쓰임

* 입력 받기
* 결과 출력

📌 **거의 모든 문제에서 필수**

---

## 2️⃣ `#include <stdlib.h>` — 메모리 & 유틸리티

### 왜 필요?

* 동적 메모리
* 수학/변환/정렬 등 범용 기능

### 대표 기능

```c
malloc, free, realloc
abs, atoi, atol
qsort, bsearch
exit
```

### 알고리즘에서 쓰임

* 큰 배열을 힙에 할당
* `qsort`로 정렬
* 문자열 → 숫자 변환

📌 **중~고급 문제에서 필수**

---

## 3️⃣ `#include <string.h>` — 문자열 & 메모리 조작

### 왜 필요?

* 문자열/메모리 관련 함수 선언

### 대표 기능

```c
strlen, strcmp, strcpy, strcat
memset, memcpy, memcmp
```

### 알고리즘에서 쓰임

* 문자열 길이 계산
* 문자열 비교
* 배열 초기화 (`memset`)

📌 **문자열 문제에서는 필수**

---

## 4️⃣ `#include <limits.h>` — 타입의 경계값

### 왜 필요?

* 정수 타입의 최소/최대값 제공

### 대표 매크로

```c
INT_MIN, INT_MAX
LONG_LONG_MIN, LONG_LONG_MAX
```

### 알고리즘에서 쓰임

* 최소/최대 초기값 설정
* 오버플로우 방지 로직

```c
int min = INT_MAX;
int max = INT_MIN;
```

📌 **DP / 그래프 / 탐색 문제에서 매우 중요**

---

## 5️⃣ `#include <stdbool.h>` — 진짜 boolean

### 왜 필요?

* `bool`, `true`, `false` 사용 가능

### 없으면?

```c
int visited = 0;  // 가짜 bool
```

### 있으면?

```c
bool visited = false;
```

📌 **가독성 & 실수 방지**

---

## 🔥 한 눈에 요약

| 헤더          | 역할      | 알고리즘 중요도 |
| ----------- | ------- | -------- |
| `stdio.h`   | 입출력     | ⭐⭐⭐⭐⭐    |
| `stdlib.h`  | 메모리, 정렬 | ⭐⭐⭐⭐     |
| `string.h`  | 문자열/메모리 | ⭐⭐⭐⭐     |
| `limits.h`  | 타입 경계   | ⭐⭐⭐      |
| `stdbool.h` | bool 타입 | ⭐⭐⭐      |

---

## ❓ 꼭 5개 다 넣어야 할까?

❌ **아니요**

* 실제로 **쓰는 기능이 있을 때만 include** 하면 됨
* 하지만 알고리즘 템플릿에서는:

  * 컴파일 비용 거의 없음
  * 실수 예방
  * 빠른 코딩

그래서 **초기 템플릿에 넣어두는 것**이 일반적입니다.

---

## 🧠 실무/대회 관점 팁

* BOJ / Codeforces:

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  ```

  이 3개만으로도 90% 해결

* 안정성까지 챙기면:

  ```c
  #include <limits.h>
  #include <stdbool.h>
  ```

---

### 한 줄 정리

> **이 5개 헤더는 “알고리즘 문제용 C의 기본 공구함”이다.
> 안 쓰는 공구는 꺼내지 않아도 되지만, 있어두면 빠르고 안전하다.**

원하면 다음으로

* 각 헤더의 “절대 쓰면 안 되는 함수들”
* 알고리즘에서 `qsort` 제대로 쓰는 법
* `memset`으로 int 배열 초기화할 때 주의점

같은 것도 바로 이어서 정리해줄게.
