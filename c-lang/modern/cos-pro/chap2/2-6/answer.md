지금 코드는 **동작은 되지만** 개선/주의할 점이 몇 가지 있어. 특히 `dr/dc` 매핑이 헷갈리게 되어 있고(`L`이 x를 -1로 움직임), `arr`도 선언만 하고 안 쓰고 있어.

아래처럼 정리하면 더 안전하고 깔끔해져.

---

## ✅ 1) 지금 코드에서 가장 큰 개선 포인트

### (1) `if` 4개 → `else if` 또는 `switch`

지금은 한 글자가 동시에 L/R/U/D일 수 없으니 `else if`나 `switch`가 더 자연스러움.

### (2) 방향 매핑을 “표”로 만들면 실수 줄어듦

`dr/dc`를 쓰려면, “index를 어떻게 구할지”가 핵심인데 지금은 그냥 하드코딩이라 `dr/dc` 의미가 희미해짐.

---

## ✅ 2) 추천: `switch`로 가장 간단히

(좌표를 `(row, col)`처럼 쓰면 L/R은 col, U/D는 row가 자연스러움)

```c
#include <stdlib.h>
#include <string.h>

int* solution(const char* commands) {
    int* answer = (int*)malloc(sizeof(int) * 2);
    answer[0] = 0; // row (y)
    answer[1] = 0; // col (x)

    for (int i = 0; commands[i] != '\0'; i++) {
        switch (commands[i]) {
            case 'L': answer[1] -= 1; break;
            case 'R': answer[1] += 1; break;
            case 'U': answer[0] -= 1; break;
            case 'D': answer[0] += 1; break;
            default: /* 무시 or 에러 처리 */ break;
        }
    }

    return answer;
}
```

* 이게 제일 덜 헷갈리고 실무에서도 많이 씀.
* `strlen()`도 매번 안 구해도 됨(널 종료까지 루프).

---

## ✅ 3) `arr="LRUD"` + dr/dc를 진짜로 활용하는 버전

```c
#include <stdlib.h>
#include <string.h>

int* solution(const char* commands) {
    int* answer = (int*)malloc(sizeof(int) * 2);
    answer[0] = 0;
    answer[1] = 0;

    const char dirs[] = "LRUD";
    const int dr[4] = { 0, 0, -1, 1 };  // row: L,R는 0 / U는 -1 / D는 +1
    const int dc[4] = { -1, 1, 0, 0 };  // col: L은 -1 / R은 +1 / U,D는 0

    for (int i = 0; commands[i] != '\0'; i++) {
        char c = commands[i];
        for (int k = 0; k < 4; k++) {
            if (c == dirs[k]) {
                answer[0] += dr[k];
                answer[1] += dc[k];
                break;
            }
        }
    }

    return answer;
}
```

* `dirs`를 진짜로 써서 매핑이 명확해짐.
* 입력에 다른 문자가 섞여도 무시 가능.

---

## ⚠️ 4) 호출 쪽에서 꼭 free 해줘야 함

```c
int* pos = solution("LRUD");
printf("%d %d\n", pos[0], pos[1]);
free(pos);
```

---

원하는 좌표계가 있어?

* (x, y)로 할지
* (row, col)로 할지
  지금 코드는 `L`에서 `answer[0]`이 바뀌는 형태라 좌표 의미가 섞여 있어서, 한 번만 정해두면 이후 문제들이 훨씬 편해져.
