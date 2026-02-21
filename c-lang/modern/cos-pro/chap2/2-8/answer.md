이 코드는 👉 **배열을 양쪽에서 번갈아가며 꺼내는 문제**야.

---

## 🔎 코드 동작 설명

입력:

```
arr = [1, 2, 3, 4, 5]
```

동작 과정:

| idx    | 선택    | 값 |
| ------ | ----- | - |
| 0 (짝수) | left  | 1 |
| 1 (홀수) | right | 5 |
| 2      | left  | 2 |
| 3      | right | 4 |
| 4      | left  | 3 |

👉 결과:

```
[1, 5, 2, 4, 3]
```

---

# ✅ 알고리즘 성질

* Two Pointer 사용
* 시간복잡도: O(n)
* 공간복잡도: O(n)

---

# ⚠️ 개선 포인트

### 1️⃣ malloc 실패 체크

```c
int* answer = malloc(sizeof(int) * arr_len);
if (!answer) return NULL;
```

---

### 2️⃣ idx % 2 대신 boolean 토글이 더 빠름

```c
int fromLeft = 1;

while (left <= right) {
    if (fromLeft) {
        answer[idx++] = arr[left++];
    } else {
        answer[idx++] = arr[right--];
    }
    fromLeft = !fromLeft;
}
```

✔ 나눗셈 연산 제거
✔ 더 읽기 쉬움

---

### 3️⃣ 입력 길이 0일 때 방어 코드

```c
if (arr_len <= 0) return NULL;
```

---

# 🎯 깔끔한 최종 추천 버전

```c
#include <stdlib.h>

int* solution(int arr[], int arr_len) {
    if (arr_len <= 0) return NULL;

    int* answer = malloc(sizeof(int) * arr_len);
    if (!answer) return NULL;

    int left = 0, right = arr_len - 1;
    int idx = 0;
    int fromLeft = 1;

    while (left <= right) {
        if (fromLeft)
            answer[idx++] = arr[left++];
        else
            answer[idx++] = arr[right--];

        fromLeft = !fromLeft;
    }

    return answer;
}
```

---

# 🧠 이 패턴이 쓰이는 문제 유형

* 데크 시뮬레이션
* 지그재그 재배치
* 양끝 선택 그리디
* 카드 게임 문제

---

원하면 확장해볼까?

* 가운데부터 양쪽으로 퍼지는 버전
* 정렬 후 양끝 번갈아 배치 (최대 최소 교차)
* 제자리(in-place)로 구현하는 방법 (난이도 ↑)

어디까지 가볼까?
