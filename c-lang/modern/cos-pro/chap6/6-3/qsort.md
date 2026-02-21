좋다 👍
C에서 배열 정렬은 **3가지 레벨**로 나눠서 이해하면 깔끔하다.

---

# ✅ 1️⃣ 가장 많이 쓰는 방법: `qsort` (표준 라이브러리)

C 표준 정렬 함수는 `qsort` 하나뿐이다.

## 📌 기본 형태

```c
#include <stdlib.h>

void qsort(
    void *base,      // 배열 시작 주소
    size_t nmemb,    // 요소 개수
    size_t size,     // 요소 하나의 크기
    int (*compar)(const void *, const void *)
);
```

---

## 🔹 예제 1 — int 배열 오름차순

```c
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    int arr[] = {5, 2, 9, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
```

출력:

```
1 2 3 5 9
```

---

## 🔹 내림차순

```c
return y - x;
```

---

# ⚠️ 자주 하는 실수

❌ 이렇게 쓰면 위험함:

```c
return x - y;
```

이건 **오버플로우 가능성 있음**

안전한 방식은:

```c
if (x < y) return -1;
if (x > y) return 1;
return 0;
```

---

# ✅ 2️⃣ 구조체 배열 정렬

예:

```c
typedef struct {
    int score;
    int id;
} Student;
```

점수 기준 정렬:

```c
int compare(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;

    return s1->score - s2->score;
}
```

---

# ✅ 3️⃣ 문자열 배열 정렬

```c
#include <string.h>

int compare(const void *a, const void *b) {
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;

    return strcmp(s1, s2);
}
```

---

# 🧠 왜 `char**` 인가?

문자열 배열은 이렇게 생겼다:

```
char *words[]
```

즉 배열 원소가 "char*"라서
`void*` → `char**`로 받아야 함.

---

# 🔥 4️⃣ 직접 정렬 구현 (연습용)

## 🔹 버블 정렬

```c
for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
        if (arr[j] > arr[j+1]) {
            int tmp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = tmp;
        }
    }
}
```

시간복잡도: O(n²)

---

# 🔥 5️⃣ 언제 qsort를 쓰는 게 좋은가?

| 상황     | 추천                |
| ------ | ----------------- |
| 코딩테스트  | 거의 항상 qsort       |
| 성능 중요  | 직접 quick/merge 구현 |
| 구조체 정렬 | qsort             |
| 문자열 정렬 | qsort + strcmp    |

---

# 🎯 코테에서 자주 나오는 패턴

### 1️⃣ 가장 큰 수 문제

```c
int compare(const void *a, const void *b) {
    char ab[20], ba[20];

    sprintf(ab, "%s%s", *(char **)a, *(char **)b);
    sprintf(ba, "%s%s", *(char **)b, *(char **)a);

    return strcmp(ba, ab);
}
```

---

# 📌 정리

| 방법           | 난이도  | 실전성   |
| ------------ | ---- | ----- |
| qsort        | ⭐⭐   | ⭐⭐⭐⭐⭐ |
| 버블           | ⭐    | ⭐     |
| 직접 quicksort | ⭐⭐⭐⭐ | ⭐⭐⭐   |

---

원하면:

* 🔥 qsort 내부 원리 설명
* 🔥 void* 포인터 완전 정리
* 🔥 안정 정렬 vs 불안정 정렬
* 🔥 비교 함수 제대로 이해하기 훈련 문제

어디까지 갈까 😎
