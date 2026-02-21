좋은 코드인데 **치명적인 버그 하나** 있어 👇

```c
snprintf(answer, sizeof(answer), "%.1f", diff);
```

여기서 `sizeof(answer)`는 ❌ **문자열 크기(10)가 아니라 포인터 크기**야.

* `answer`는 `char*`
* `sizeof(answer)` → 8 (64bit 환경) 또는 4
* 그래서 출력이 잘리거나 UB 가능

---

# ✅ 올바른 수정

## 방법 1️⃣: 상수로 직접 넣기 (간단)

```c
char* solution(int hour, int minute) {
    char* answer = malloc(10);

    double hour_angle = (hour % 12) * 30 + minute * 0.5;
    double minute_angle = minute * 6; 

    double diff = fabs(hour_angle - minute_angle);

    snprintf(answer, 10, "%.1f", diff);

    return answer;
}
```

---

## 방법 2️⃣: 안전하게 크기 정의

```c
#define BUF_SIZE 16

char* solution(int hour, int minute) {
    char* answer = malloc(BUF_SIZE);

    double hour_angle = (hour % 12) * 30 + minute * 0.5;
    double minute_angle = minute * 6;

    double diff = fabs(hour_angle - minute_angle);

    snprintf(answer, BUF_SIZE, "%.1f", diff);

    return answer;
}
```

---

# 🔎 추가로 중요한 논리 포인트

시계 각도 차이는 보통 **작은 각도**를 구함.

지금은 그냥 절댓값만 구했어:

```c
fabs(hour_angle - minute_angle);
```

하지만 350도 차이면 실제 최소 각도는 10도야.

### ✅ 정석 보정 추가

```c
double diff = fabs(hour_angle - minute_angle);
if (diff > 180.0)
    diff = 360.0 - diff;
```

---

# 🧠 완성형 정답 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 16

char* solution(int hour, int minute) {
    char* answer = malloc(BUF_SIZE);

    double hour_angle = (hour % 12) * 30 + minute * 0.5;
    double minute_angle = minute * 6;

    double diff = fabs(hour_angle - minute_angle);
    if (diff > 180.0)
        diff = 360.0 - diff;

    snprintf(answer, BUF_SIZE, "%.1f", diff);

    return answer;
}
```

---

# 🧪 주어진 테스트

```
3:00
```

* 시침 = 90도
* 분침 = 0도
* 차이 = 90.0

출력:

```
90.0
```

---

# ⚠️ main에서 free 필요

```c
free(ret);
```

---

원하면
✔ 초(second)까지 포함한 버전
✔ 부동소수점 없이 정수로 계산하는 버전
✔ 오차 없는 방식

까지 확장해줄까?


-----


좋아 👍
코드가 **무엇을 계산하는지**, **왜 이렇게 계산하는지**, 그리고 **각 줄의 의미**를 차근차근 설명해줄게.

---

# 📌 문제 의도

이 함수는:

> 시(hour)와 분(minute)이 주어졌을 때
> 시침과 분침 사이의 각도 차이를 구해서
> 소수점 1자리 문자열로 반환하는 함수

예:

* 3:00 → 90.0
* 12:30 → 165.0
* 6:00 → 180.0

---

# 🧠 시계 각도 계산 원리

## 1️⃣ 분침 각도

분침은 60분에 360도 움직임.

[
360 ÷ 60 = 6
]

→ 1분당 6도

```c
double minute_angle = minute * 6;
```

예:

* 15분 → 90도
* 30분 → 180도

---

## 2️⃣ 시침 각도

시침은 12시간에 360도 움직임.

[
360 ÷ 12 = 30
]

→ 1시간당 30도

하지만 중요한 점 👇

시침은 "분"에 따라 **조금씩 움직인다**

1시간 동안 30도 움직이니까
1분 동안은:

[
30 ÷ 60 = 0.5
]

→ 1분당 0.5도

그래서:

```c
double hour_angle =
    (hour % 12) * 30
    + minute * 0.5;
```

예:
3시 30분이면

* 3 * 30 = 90
* 30 * 0.5 = 15
* 합 = 105도

---

## 3️⃣ 각도 차이 계산

```c
double diff = fabs(hour_angle - minute_angle);
```

* 두 각도의 차이를 구하고
* `fabs()`로 절댓값 처리

※ `fabs`는 double용 abs 함수
(int용은 `abs()`)

---

# 📌 왜 (hour % 12)를 쓰는가?

24시간 입력이 들어올 수 있기 때문.

* 15시 → 15 % 12 = 3
* 24시 → 0

시계는 12시간 기준으로 돌아가니까 반드시 필요함.

---

# 📌 문자열로 반환하는 이유

```c
char* answer = malloc(10);
snprintf(answer, ..., "%.1f", diff);
```

* 결과를 `"90.0"` 같은 문자열로 반환
* `%.1f` → 소수점 한 자리까지 출력

---

# 📌 math.h를 include하는 이유

```c
#include <math.h>
```

* `fabs()`는 math 라이브러리에 정의되어 있음

---

# 📌 전체 흐름 요약

1. 시침 각도 계산
2. 분침 각도 계산
3. 두 각도 차이 절댓값 계산
4. 소수점 1자리 문자열로 변환
5. 반환

---

# 🧪 예시 1

### 3:00

* hour_angle = 3×30 + 0 = 90
* minute_angle = 0
* diff = 90

→ "90.0"

---

# 🧪 예시 2

### 12:30

* hour_angle = 0×30 + 30×0.5 = 15
* minute_angle = 180
* diff = 165

→ "165.0"

---

# ⚠️ 한 가지 논리적으로 빠진 것

현재 코드는 **단순 차이**만 구함.

하지만 실제 시계 각도 문제에서는
보통 "작은 각도"를 구함.

예:

* 350도 차이 → 실제 각도는 10도

그걸 처리하려면:

```c
if (diff > 180)
    diff = 360 - diff;
```

이 부분이 필요함.

---

# 🎯 핵심 개념 요약

| 요소   | 의미            |
| ---- | ------------- |
| 30   | 시침 1시간당 이동 각도 |
| 0.5  | 시침 1분당 이동 각도  |
| 6    | 분침 1분당 이동 각도  |
| fabs | double 절댓값    |
| %12  | 24시간 보정       |

---

원하면
시침 이동 원리를 수학적으로 더 깊게 설명해줄까?
(왜 0.5가 되는지 기하학적으로)
