이 코드는 👉 **비밀번호에 연속된 3글자 증가/감소 패턴이 있는지 검사**하는 함수야.

---

## 🎯 검사 조건

아래 같은 패턴이 나오면 ❌ `false`

* `"abc"` (1씩 증가)
* `"cba"` (1씩 감소)
* `"123"`
* `"321"`

---

## 🔎 코드 동작 원리

```c
int firstCheck = password[i + 1] - password[i];
int secondCheck = password[i + 2] - password[i + 1];
```

예: `"abc"`

```
'b' - 'a' = 1
'c' - 'b' = 1
```

→ 두 차이가 같고
→ 그 값이 1 또는 -1이면

```c
return false;
```

---

## ✅ 예시 테스트

| 입력     | 결과               |
| ------ | ---------------- |
| "abc"  | false            |
| "cba"  | false            |
| "a1b2" | true             |
| "1357" | true             |
| "abx"  | true             |
| "1234" | false (123에서 걸림) |

---

# ⚠️ 개선 포인트

### 1️⃣ 길이 3 미만 방어 코드

```c
if (length < 3) return true;
```

---

### 2️⃣ `strlen` 매번 안 써도 됨 (이미 한 번만 사용해서 OK)

---

### 3️⃣ bool 사용 시 헤더 필요

```c
#include <stdbool.h>
```

---

# ✅ 더 안전한 최종 버전

```c
#include <stdbool.h>
#include <string.h>

bool solution(const char* password) {
    int length = strlen(password);
    if (length < 3) return true;

    for (int i = 0; i < length - 2; ++i) {
        int diff1 = password[i + 1] - password[i];
        int diff2 = password[i + 2] - password[i + 1];

        if (diff1 == diff2 && (diff1 == 1 || diff1 == -1))
            return false;
    }
    return true;
}
```

---

# 🧠 확장 가능 문제

현재는 **3글자만 검사**함.

만약:

* 4글자 이상 연속 증가도 막고 싶다면?
* 대소문자 구분 없이 검사?
* 숫자/알파벳 구분해서 따로 검사?
* 같은 문자 3개 반복(aaa)도 막고 싶다면?

이런 조건도 추가 가능.

---

원하면
👉 **실무형 비밀번호 검증 로직 (대기업 스타일)** 로 확장해줄까?
