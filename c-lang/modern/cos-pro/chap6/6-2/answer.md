이 문제는 **그리디로 왼쪽부터 최대한 채우는 게 최적**이야. (단어 순서를 바꿀 수 없고, 줄 끝에서 단어가 잘리면 무조건 다음 줄로 넘어가야 하니까 선택지가 없음)

그래서 “더 나은 풀이”는 보통

* 분기 최소화(가독성)
* 마지막 줄 처리 확실
* 오버/언더카운트 방지
  쪽으로 개선하는 게 핵심.

---

## 네 풀이에서 아쉬운 점 2가지

1. **마지막 줄 카운트가 누락될 수 있음**
   `answer++`가 “줄이 꽉 찼을 때” 또는 “다음 단어가 안 들어올 때(else)”만 증가하는 구조라, 마지막에 줄이 남아 있으면 카운트가 빠질 수 있어.

2. `count`(남은 칸) 기반이라 공백 처리 분기가 생김
   `count != K`일 때 공백 1칸을 빼는 식이라 조건이 복잡해짐.

---

## 추천 풀이: `used`(현재 줄 사용 길이)로 단순화

가장 깔끔한 표준 해법이 이거야.

핵심 아이디어:

* 현재 줄에 이미 글자가 있으면 다음 단어 앞에 공백 1칸 필요
* `need = len + (used>0 ? 1 : 0)`
* `used + need <= K`면 같은 줄에 쓰고, 아니면 줄 수 +1 하고 새 줄에서 시작

```c
#include <string.h>

int solution(int K, char* words[], int words_len) {
    int lines = 1;   // words_len >= 1 이므로 최소 1줄은 필요
    int used = 0;    // 현재 줄에 사용한 글자 수

    for (int i = 0; i < words_len; i++) {
        int len = (int)strlen(words[i]);
        int need = len + (used > 0 ? 1 : 0); // 공백 포함 필요 길이

        if (used + need <= K) {
            used += need;          // 같은 줄에 배치
        } else {
            lines++;               // 줄 바꿈
            used = len;            // 새 줄에 단어부터
        }
    }
    return lines;
}
```

### 장점

* 조건이 한 줄(`need`)로 정리돼서 실수 포인트가 줄어듦
* “딱 맞아서 0” 같은 특수 분기 없어짐
* 마지막 줄 처리 자연스럽게 됨 (`lines=1`로 시작)

---

## 네 방식(remaining count)을 유지하되 더 깔끔하게

남은 칸 `remain`으로 가고 싶다면, 이렇게도 정리 가능:

```c
#include <string.h>

int solution(int K, char* words[], int words_len) {
    int lines = 1;
    int remain = K;

    for (int i = 0; i < words_len; i++) {
        int len = (int)strlen(words[i]);

        int need = len + (remain < K ? 1 : 0); // 이미 뭔가 썼으면 공백 1칸 필요
        if (need <= remain) {
            remain -= need;
        } else {
            lines++;
            remain = K - len;
        }
    }
    return lines;
}
```

---

## 복잡도

* 시간: O(words_len * 평균단어길이) ≈ O(100*30)이라 매우 작음
* 공간: O(1)

---

원하면, 네가 쓴 코드에서 **최소 수정으로 오답 가능성만 제거한 버전**도 만들어줄게.
하지만 코테에서는 위 `used` 방식이 제일 깔끔하고 안전해.
