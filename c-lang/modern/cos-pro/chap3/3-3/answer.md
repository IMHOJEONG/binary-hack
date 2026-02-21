이 코드는 “비숍들이 공격할 수 있는 칸(대각선)을 표시(-1)하고, 남은 안전 칸(0)의 개수”를 세려는 거지? 의도는 맞는데, 지금 구현에는 **치명적인 버그/누수/좌표 변환 문제**가 몇 개 있어. 핵심만 딱 정리해서 고쳐줄게.

---

## 1) 지금 코드의 문제점

### ✅ (1) `matrix` malloc 타입/크기 불일치 (가장 위험)

```c
int (*matrix)[8] = malloc(sizeof(int) * 8 * 8);
```

* 포인터 타입은 `int (*)[8]` (8칸짜리 int 배열의 포인터)라서 접근은 `matrix[r][c]`로 맞는데,
* malloc은 “`int 64개`”만 할당해서 운 좋게 맞아 보이지만, **의도가 불명확하고 실수 유발**.
* 제일 안전한 건 이렇게:

```c
int (*matrix)[8] = malloc(sizeof(int[8][8]));
```

### ✅ (2) `free(matrix)`가 주석 처리됨 → 메모리 누수

반드시 `free(matrix);`

### ✅ (3) `getCount()`가 “0인 칸 개수”를 세는데, 비숍이 있는 칸도 -1로 바꾸니 OK

다만 함수 이름이 의미가 애매함(안전 칸 세기면 safeCount 같은 이름이 더 좋음)

### ✅ (4) 좌표 변환은 괜찮지만 입력이 `"A1"` 형태인지 가정함

```c
int nowR = '8' - bishops[k][1];
```

* `"A1"`이면 `'8' - '1' = 7` → 아래쪽 행이 7 → 보드(0=top) 기준으로 맞음.
* `"A8"`이면 0. OK.

### ✅ (5) 대각선 마킹 루프에서 `curR/curC`는 사실 필요 없음

지금은 매번 `curR = nowR; curC = nowC;`로 리셋하고 있어서, 그냥 `nowR/nowC` 기준으로 계산하면 됨.

---

## 2) 더 깔끔하고 안전한 정답 코드

```c
#include <stdlib.h>
#include <stdbool.h>

static int getIndex(const char data[8], char ch) {
    for (int i = 0; i < 8; i++) if (data[i] == ch) return i;
    return -1;
}

int solution(char* bishops[], int bishops_len) {
    char alphabet[8] = {'A','B','C','D','E','F','G','H'};
    int dr[4] = {-1, -1,  1,  1};
    int dc[4] = {-1,  1, -1,  1};

    int (*matrix)[8] = malloc(sizeof(int[8][8]));
    if (!matrix) return 0;

    // init
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            matrix[r][c] = 0;

    // mark attacked squares (including bishop squares)
    for (int k = 0; k < bishops_len; k++) {
        int nowR = '8' - bishops[k][1];
        int nowC = getIndex(alphabet, bishops[k][0]);
        if (nowC < 0 || nowR < 0 || nowR >= 8) continue; // 방어

        matrix[nowR][nowC] = -1;

        for (int d = 0; d < 4; d++) {
            for (int step = 1; step < 8; step++) {
                int nr = nowR + step * dr[d];
                int nc = nowC + step * dc[d];
                if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) break;
                matrix[nr][nc] = -1;
            }
        }
    }

    // count safe squares
    int safe = 0;
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (matrix[r][c] == 0) safe++;

    free(matrix);
    return safe;
}
```

---

## 3) 참고: “비숍이 다른 비숍에 막혀서 그 뒤는 공격 못한다” 규칙이면?

체스 규칙대로라면 대각선에 다른 비숍(말)이 있으면 그 뒤 칸은 공격 못 함.
지금 코드는 **막힘을 고려하지 않고 끝까지 -1**을 찍는 방식이야.

* 만약 “막힘 고려”가 필요하면:

  * 먼저 비숍 위치를 `occupied`로 표시
  * 대각선 이동하다가 `occupied` 만나면 `break`

원하면 그 버전도 바로 수정해줄게.
문제 조건이 “다른 비숍이 막아도 계속 공격으로 본다/안 본다” 중에 어느 쪽이야?
