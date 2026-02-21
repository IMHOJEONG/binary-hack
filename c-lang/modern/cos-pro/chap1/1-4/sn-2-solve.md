좋다 😎 아주 좋다.
지금부터는 **실전 알고리즘 감각 + C 문자열 처리 기본기**다.

---

# 🔎 먼저 4번, 5번 빠르게 교정

---

## ❌ 4번 (시간 계산 틀림)

```c
int minute = (total / 3600 / 60);   ❌
int second = (total / 3600 % 60);   ❌
```

### 올바른 계산

```c
int hour   = total / 3600;
int minute = (total % 3600) / 60;
int second = total % 60;
```

### 전체 수정

```c
int total = 3661;

int hour   = total / 3600;
int minute = (total % 3600) / 60;
int second = total % 60;

char result[32];

snprintf(result, sizeof(result),
    "%02d:%02d:%02d",
    hour, minute, second
);
```

→ `"01:01:01"`

---

## ❌ 5번 (따옴표 문제)

```c
"\"( %+d , %+d )\""
```

문제에서 따옴표는 요구 안 했어.

### 정답:

```c
snprintf(result, sizeof(result),
    "( %d , %d )",
    x, y
);
```

→ `( -3 , 10 )`

---

# 🔥 이제 핵심 질문

## 3번: `"2026 2 5"` → 3개로 나누는 방법

방법은 3가지 있다.

---

# 🥇 방법 1 — `sscanf` (알고리즘에서 가장 많이 씀)

이게 제일 깔끔하고 실전용.

```c
char data[32] = "2026 2 5";

int year, month, day;

sscanf(data, "%d %d %d", &year, &month, &day);

char result[32];

snprintf(result, sizeof(result),
    "%04d-%02d-%02d",
    year, month, day
);
```

✔ 결과:

```
2026-02-05
```

---

### 왜 이게 좋냐면

* 공백 기준 자동 분리
* 추가 파싱 코드 필요 없음
* 알고리즘에서 매우 자주 쓰임

---

# 🥈 방법 2 — `strtok`

```c
char data[32] = "2026 2 5";

char *token = strtok(data, " ");
int year  = atoi(token);

token = strtok(NULL, " ");
int month = atoi(token);

token = strtok(NULL, " ");
int day   = atoi(token);
```

⚠ 단점:

* 원본 문자열이 수정됨
* 스레드 안전 아님

---

# 🥉 방법 3 — 직접 루프 돌리기 (비추천)

문자 하나씩 돌면서 공백 만나면 나누는 방식
→ 시험에서 굳이 안 씀

---

# 🎯 결론

알고리즘에서는 거의 항상:

```
sscanf
```

쓴다.

---

# 🔥 최종 3번 완성 코드

```c
char data[32] = "2026 2 5";
int year, month, day;

sscanf(data, "%d %d %d", &year, &month, &day);

char result[32];

snprintf(result, sizeof(result),
    "%04d-%02d-%02d",
    year, month, day
);
```

---

# 🔥 실전 팁

`sscanf` 패턴 기억해두면 좋음:

| 패턴         | 의미          |
| ---------- | ----------- |
| `%d %d %d` | 공백 기준 숫자 3개 |
| `%d-%d-%d` | - 기준        |
| `%[^,],%d` | , 기준 문자열+숫자 |

---

# 🎯 다음 단계 갈래?

* 🔥 `sscanf` 고급 문제
* 🔥 문자열 파싱 실전 알고리즘 문제
* 🔥 쉼표 숫자 파싱 문제
* 🔥 주민번호 파싱 스타일 문제

어디까지 가볼까 😎
