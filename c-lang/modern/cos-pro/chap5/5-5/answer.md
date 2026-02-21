이 코드는 “아군 병사(armies)와 적군(enemies)의 전투력 숫자”가 있을 때, **아군 한 명이 자신보다 작거나 같은 적을 잡을 수 있다**는 규칙으로 **잡을 수 있는 적의 수(count)**를 세려는 코드야. (정확히는 “매칭” 문제)

그런데 지금 구현은 **논리 버그 때문에 count가 과하게 증가**해. 또한 `qsort` 비교 함수 시그니처도 잘못됐어(UB 가능).

아래에 **무슨 의도인지**, **현재 코드가 왜 틀리는지**, **정석 풀이(투포인터)**로 고쳐줄게.

---

## 1) 현재 코드가 하는 일

1. enemies, armies를 복사해서 `newEnemies`, `newArmies`에 넣음
2. 둘 다 오름차순 정렬
3. 각 아군 `armiesData`에 대해 모든 적을 돌며

   * `armiesData >= enemiesData` 이고 적이 아직 안 잡혔으면(`!= -1`)
   * `count++` 하고 그 적을 -1로 표시

---

## 2) 치명적 버그: 한 아군이 “여러 명”을 잡아버림

이 부분:

```c
for (int i = 0; i < armies_len; i++) {
  int armiesData = newArmies[i];
  for (int j = 0; j < enemies_len; j++) {
    int enemiesData = newEnemies[j];

    if (armiesData >= enemiesData && enemiesData != -1) {
      count++;
      newEnemies[j] = -1;
    }
  }
}
```

여기서는 **한 명의 아군(armiesData)이 조건을 만족하는 적을 만나면 계속 잡아버려**.
즉, 아군 1명이 여러 적을 잡을 수 있게 되어 있음.

보통 매칭 문제는:

* **아군 1명당 적 1명만** 잡을 수 있어야 함.

그렇다면 잡았으면 `break;` 해야 함.

---

## 3) 또 다른 버그: -1로 바꿔도 비교가 계속 참이 됨

적을 잡으면 `newEnemies[j] = -1`로 바꾸는데,
다음 아군이 볼 때:

* `enemiesData = -1`
* `armiesData >= -1` 는 거의 항상 참

근데 조건이

```c
armiesData >= enemiesData && enemiesData != -1
```

라서 `enemiesData != -1` 덕분에 카운트는 안 늘지만,
정렬된 배열을 -1로 망가뜨려서 “매칭” 관점에서 깔끔하지 않음.

---

## 4) qsort compare 시그니처가 잘못됨 (UB 가능)

`qsort`는 비교 함수가 `const void*`를 받아야 해.

지금:

```c
int compare(const int* a, const int* b)
```

정석:

```c
int compare(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}
```

---

## 5) 정답은 보통 “투포인터”로 O(n log n) (정렬 후 O(n))

### 규칙: 아군 1명은 적 1명만 잡는다 (최대로 많이 잡기)

* 둘 다 정렬
* 가장 약한 아군부터, 잡을 수 있는 가장 약한 적부터 처리

```c
#include <stdlib.h>

static int compare(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int solution(int enemies[], int enemies_len, int armies[], int armies_len) {
    int* E = (int*)malloc(sizeof(int) * enemies_len);
    int* A = (int*)malloc(sizeof(int) * armies_len);
    for (int i = 0; i < enemies_len; i++) E[i] = enemies[i];
    for (int i = 0; i < armies_len; i++) A[i] = armies[i];

    qsort(E, enemies_len, sizeof(int), compare);
    qsort(A, armies_len, sizeof(int), compare);

    int i = 0; // enemies pointer
    int j = 0; // armies pointer
    int count = 0;

    while (i < enemies_len && j < armies_len) {
        if (A[j] >= E[i]) {  // 이 아군이 이 적을 잡을 수 있음
            count++;
            i++; // 다음 적
            j++; // 다음 아군 (1명당 1명)
        } else {
            j++; // 이 아군은 너무 약함 -> 더 센 아군으로
        }
    }

    free(E);
    free(A);
    return count;
}
```

---

## 6) 네 main 테스트의 정답

### 테스트 1

* enemies = [1,4,3]
* armies = [1,3]
  정렬:
* E=[1,3,4]
* A=[1,3]

매칭:

* 1은 1 잡음 (count=1)
* 3은 3 잡음 (count=2)
  → 결과 **2**

### 테스트 2

* enemies=[1,1,1]
* armies=[1,2,3,4]
  정렬 후
* E=[1,1,1]
* A=[1,2,3,4]
  매칭:
* 1 잡음
* 2 잡음
* 3 잡음
  → 결과 **3**

---

## 7) “현재 코드”를 최소 수정만 하면?

만약 정말로 “아군 1명이 1명만 잡는다”면, 이 줄만 추가해도 큰 버그가 해결돼:

```c
if (armiesData >= enemiesData && enemiesData != -1) {
    count++;
    newEnemies[j] = -1;
    break; // ✅ 한 명 잡으면 끝
}
```

하지만 투포인터가 더 깔끔하고 빠르다.

---

원래 규칙이 **아군 1명이 여러 명도 잡을 수 있는 게임**이었어?
아니면 **1대1 매칭**이었어? (보통은 1대1이라 위가 정석이야.)
