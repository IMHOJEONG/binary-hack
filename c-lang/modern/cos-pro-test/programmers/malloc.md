좋아, “복사본 방식” 자체는 방향 맞는데 지금 코드에는 **치명적인 메모리 할당 누락**이 있어서 바로 터져요.

## 1) 지금 오류 나는 이유 (핵심)

### ✅ `copy()`에서 행 포인터만 malloc 하고, 각 행(garden2[i])을 malloc 안 함

```c
int **garden2 = (int**)malloc(sizeof(int*) * garden_row_len);

for (int i = 0 ; i < garden_row_len; i++) {
    for (int j = 0; j < garden_col_len; j++) {
        garden2[i][j] = garden[i][j]; // ❌ garden2[i]가 할당된 적이 없음
    }
}
```

`garden2[i]`는 쓰레기 포인터 상태라서 `garden2[i][j]` 접근하는 순간 **segfault(런타임 에러)** 납니다.

---

## 2) 추가로 테스트에서 걸릴 수 있는 문제

### ✅ `solution()`에서 `start = setValue(start, ...)` 할 때 이전 start를 free 안 해서 메모리 누수

코테는 보통 누수로 바로 실패하진 않지만, 큰 입력이면 메모리 초과로 실패할 수 있어요.

---

# 고친 코드 (복사본 방식, 최소 수정)

* `copy()`에서 **각 행도 malloc**
* `setValue()`가 반환한 새 배열을 쓰기 전에 **이전 배열 free**
* (옵션) 시작부터 1이 하나도 없으면 무한루프 방지까지 넣어줌

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static int nx[] = {-1, 1, 0, 0};
static int ny[] = {0, 0, -1, 1};

int** copyGarden(int **garden, int R, int C) {
    int **g = (int**)malloc(sizeof(int*) * R);
    for (int i = 0; i < R; i++) {
        g[i] = (int*)malloc(sizeof(int) * C);
        for (int j = 0; j < C; j++) {
            g[i][j] = garden[i][j];
        }
    }
    return g;
}

void freeGarden(int **garden, int R) {
    for (int i = 0; i < R; i++) free(garden[i]);
    free(garden);
}

bool isFull(int **garden, int R, int C) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (garden[i][j] == 0) return false;
        }
    }
    return true;
}

int countOnes(int **garden, int R, int C) {
    int cnt = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (garden[i][j] == 1) cnt++;
    return cnt;
}

int** setValue(int **garden, int R, int C) {
    int **newArr = copyGarden(garden, R, C);

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (garden[i][j] == 1) {
                for (int k = 0; k < 4; k++) {
                    int nextR = i + nx[k];
                    int nextC = j + ny[k];
                    if (nextR >= 0 && nextR < R && nextC >= 0 && nextC < C) {
                        newArr[nextR][nextC] = 1;
                    }
                }
            }
        }
    }
    return newArr;
}

int solution(int **garden, int R, int C) {
    // 시작부터 1이 하나도 없으면 절대 못 채우므로 무한루프 방지
    if (countOnes(garden, R, C) == 0) return -1;

    int answer = 0;
    int **cur = copyGarden(garden, R, C);

    while (!isFull(cur, R, C)) {
        int **next = setValue(cur, R, C);
        freeGarden(cur, R);   // ✅ 이전 배열 해제
        cur = next;
        answer++;
    }

    freeGarden(cur, R);
    return answer;
}
```

---

## 3) 너 코드에서 “최소 변경”만 딱 말하면

* `copy()` 안에 **`garden2[i] = malloc(sizeof(int) * garden_col_len);`** 이 줄이 반드시 필요
* `solution()`에서 `start = setValue(...)` 하기 전에 이전 `start`를 free 해야 함

---

원하면, 너가 작성한 함수/변수명 그대로 유지해서( copy / setValue / isFull ) **더 더 최소 diff** 버전으로도 바로 맞춰줄게.
