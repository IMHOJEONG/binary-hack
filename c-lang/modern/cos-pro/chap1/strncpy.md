## 1️⃣ `strncpy`

![Image](https://i.pinimg.com/736x/89/25/ab/8925abf4d9841538aa55367186eaed02.jpg)

![Image](https://scaler.com/topics/images/flowchart-of-strcpy-in-c.webp)

![Image](https://i.sstatic.net/7uiSD.jpg)

![Image](https://overiq.com/media/uploads/character-array-in-memory-1504599203175.png)

### 📌 개념

`strncpy`는 **문자열을 지정한 길이만큼 복사하는 함수**입니다.

```c
char *strncpy(char *dest, const char *src, size_t n);
```

* `dest` → 복사될 대상 버퍼
* `src` → 원본 문자열
* `n` → 최대 복사할 문자 수
* 반환값 → `dest`

---

### 📌 동작 방식

1. `src`에서 최대 `n`개 문자까지 복사
2. `src` 길이가 `n`보다 짧으면 남은 공간을 `'\0'`으로 채움
3. ❗ `src` 길이가 `n` 이상이면 **자동으로 NULL 종료 안 됨**

---

### 📌 예제

```c
char src[] = "Hello";
char dest[10];

strncpy(dest, src, 10);
```

→ `dest`에는 `"Hello\0\0\0\0\0"` 저장됨

---

### ⚠️ 위험한 예

```c
char src[] = "HelloWorld";
char dest[5];

strncpy(dest, src, 5);
```

→ `"Hello"`만 복사됨
→ **NULL 종료 없음** → 문자열 함수 사용 시 버그 가능

---

### ✅ 안전하게 쓰는 방법

```c
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';
```

또는
가능하면 `snprintf`, `strlcpy` (BSD 계열) 사용 권장

---

## 2️⃣ `atoi`

![Image](https://i.sstatic.net/tQeoC.png)

![Image](https://i.sstatic.net/XrpR9.png)

![Image](https://rezmoss.com/images/blog/strconv-1.png)

![Image](https://fastercapital.com/i/Handling-Errors-in-atoi--Best-Practices-and-Troubleshooting--Understanding-the-atoi-Function.webp)

### 📌 개념

`atoi`는 **문자열을 정수(int)로 변환하는 함수**입니다.

```c
int atoi(const char *str);
```

---

### 📌 동작 규칙

1. 앞쪽 공백 무시
2. `+` 또는 `-` 처리
3. 숫자 부분만 읽음
4. 숫자가 아닌 문자 나오면 중단

---

### 📌 예제

```c
atoi("123");      // 123
atoi("   -45");   // -45
atoi("10abc");    // 10
atoi("abc");      // 0
```

---

### ⚠️ 문제점

* 에러 검출 불가능
* 오버플로우 체크 없음
* 잘못된 문자열도 0 반환

---

### ✅ 더 안전한 대안: `strtol`

```c
#include <stdlib.h>

char *end;
long num = strtol("123abc", &end, 10);
```

* 어디까지 변환됐는지 확인 가능
* 오버플로우 감지 가능
* 실무에서는 `atoi` 대신 `strtol` 사용 권장

---

## 🔥 정리 비교

| 함수        | 역할        | 문제점            | 실무 권장                 |
| --------- | --------- | -------------- | --------------------- |
| `strncpy` | 문자열 복사    | NULL 종료 보장 안 됨 | `snprintf`, `strlcpy` |
| `atoi`    | 문자열 → int | 에러 체크 불가       | `strtol`              |

---

원하면:

* 🔹 `strncpy` vs `strcpy` 차이
* 🔹 `atoi` vs `strtol` 내부 동작 원리
* 🔹 C 문자열 메모리 구조 깊이 설명

어디까지 파볼까?
