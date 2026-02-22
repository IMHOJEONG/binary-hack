테스트를 못 통과하는 **핵심 이유는 `setValue()`가 “하루에 동시에 번지는” 규칙을 깨고 있기 때문**입니다.

## 1) 왜 틀리냐: in-place 갱신 때문에 “연쇄 전파”가 같은 날에 일어남

문제 유형(정원에 1이 퍼지는 날짜 계산)은 보통

* **하루(1 step)마다**
* **현재 1인 칸들만** 기준으로
* 상하좌우로 1이 **동시에** 퍼져야 합니다.

그런데 지금 `setValue()`는 `garden`을 **그 자리에서 바로 1로 바꾸고**, 같은 이중 for-loop 안에서 그 **새로 생긴 1**도 뒤에서 다시 만나면 또 퍼뜨립니다.

즉, “하루에 1칸씩 퍼져야 하는데” 코드상으론 **하루에 여러 칸 연쇄로 퍼질 수 있어서** 정답보다 날짜가 작게 나옵니다(케이스에 따라 오답).

### 간단 예시 (연쇄 전파가 발생하는 그림)

`1 0 0 0` 이런 일렬이 있다고 치면,

* 정상 규칙: 1일 후 `1 1 0 0`, 2일 후 `1 1 1 0` …
* 현재 코드: 왼쪽에서 오른쪽으로 스캔하면서 바로 1로 만들기 때문에 **한 번의 setValue에서 끝까지 퍼질 수 있음**

그래서 “동시 전파”를 요구하는 테스트에서 깨집니다.

---

## 2) 추가로 터지는 케이스: 시작부터 1이 하나도 없으면 무한 루프

초기 정원에 `1`이 **아예 없으면**, `setValue()`가 아무것도 못 바꾸고
`isFull()`은 계속 false라서 `while`이 영원히 돕니다.
(플랫폼 테스트에 이런 케이스가 들어있으면 바로 실패)

---

# 해결 방법 (정석)

## 방법 A: BFS(멀티 소스)로 “최소 날짜” 계산 (가장 안전)

초기 `1`들을 전부 큐에 넣고, 거리(날짜)를 BFS로 퍼뜨리면 “동시 전파”가 정확히 구현됩니다.

```c
#include <stdio.h>
#include <stdlib.h>

static int dx[4] = {-1, 1, 0, 0};
static int dy[4] = {0, 0, -1, 1};

typedef struct {
    int x, y, d; // d = day
} Node;

int solution(int **garden, int R, int C) {
    int total = R * C;
    int ones = 0;

    // 큐 최대 크기: R*C
    Node *q = (Node*)malloc(sizeof(Node) * total);
    int head = 0, tail = 0;

    // 초기 1들을 모두 큐에 넣기 (멀티 소스)
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (garden[i][j] == 1) {
                q[tail++] = (Node){i, j, 0};
                ones++;
            }
        }
    }

    // 이미 꽉 참
    if (ones == total) {
        free(q);
        return 0;
    }

    // 시작 1이 하나도 없으면 절대 못 채움 (문제에서 보장 안 하면 처리 필요)
    if (ones == 0) {
        free(q);
        return -1; // 또는 문제 요구값에 맞게
    }

    int answer = 0;

    while (head < tail) {
        Node cur = q[head++];

        for (int k = 0; k < 4; k++) {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;

            if (garden[nx][ny] == 0) {
                garden[nx][ny] = 1;
                ones++;
                int nd = cur.d + 1;
                if (nd > answer) answer = nd;
                q[tail++] = (Node){nx, ny, nd};
            }
        }
    }

    free(q);

    // 다 못 채웠으면 (막힌 칸 같은 게 있다면)
    if (ones != total) return -1;
    return answer;
}
```

* “하루 단위 동시 전파”가 BFS 레벨(거리)로 자연스럽게 맞아떨어집니다.
* 시간복잡도 O(R*C)로도 더 좋아집니다.

---

## 방법 B: `setValue()`에서 “복사본”을 써서 동시 갱신

하루 전 상태를 `prev`로 복사하고, `prev`의 1들만 기준으로 `garden`을 갱신하면 됩니다.
(하지만 매 day마다 복사하니 느리고 구현이 번거로움 → BFS가 보통 정답)

---

원하면, 네 코드 구조(현재 `isFull`, `setValue` 유지)로 **최소 수정만 해서 통과되게** “복사본 방식”으로도 고쳐줄게요.
