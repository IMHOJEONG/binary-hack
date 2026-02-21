지금 코드는 의도(14칸짜리 전광판/스크롤에 문자를 채워서 반환)는 맞는데, **반환이 100% 터지는 코드**야.

가장 큰 문제:

### ❌ 지역변수 `arr`를 리턴하고 있음

```c
char arr[15];   // 함수 끝나면 스택에서 사라짐
answer = arr;
return answer;  // 댕글링 포인터(UB)
```

즉, 호출한 쪽에서 출력하면 운 좋으면 되다가, 어느 순간 갑자기 깨져.

---

## ✅ 고치는 방법 1) 동적 할당해서 반환 (가장 일반적)

```c
#include <stdlib.h>
#include <string.h>

char* solution(const char* phrases, int second) {
    char* arr = (char*)malloc(15);   // 14 + '\0'
    if (!arr) return NULL;

    memset(arr, '_', 14);
    arr[14] = '\0';

    int len = strlen(phrases);
    if (len == 0) return arr; // 빈 문자열이면 그냥 "______________" 반환

    int base = (14 - (second % 14)) % 14;  // 0..13로 정규화 (원래 abs는 의미가 애매함)

    for (int i = 0; i < second; i++) {
        int pos = (base + i) % 14;
        arr[pos] = phrases[i % len];
    }

    return arr; // 호출자가 free 해야 함
}
```

호출 예:

```c
char* out = solution("HELLO", 7);
printf("%s\n", out);
free(out);
```

---

## ✅ 고치는 방법 2) “정적 버퍼” 사용 (free 필요 없음, 하지만 재호출에 취약)

```c
char* solution(const char* phrases, int second) {
    static char arr[15];
    ...
    return arr;
}
```

* 장점: free 안 해도 됨
* 단점: 여러 번 호출하면 값이 덮어써짐 / 스레드 안전 X

---

## 추가로: 너 코드의 다른 문제들

### 1) `memset`, `strlen`, `abs` 헤더 누락

* `memset`, `strlen` → `#include <string.h>`
* `abs` → `#include <stdlib.h>` (이미 있음)

### 2) `base = abs(strlen(arr) - second)`는 의미가 이상함

`strlen(arr)`는 항상 14인데, `second`가 커지면 base가 커져서 결국 `%14`로 깎이긴 하지만, 의도가 “시작 위치 이동”이면 보통 `second % 14`로 정규화하는 게 맞아.

---

원래 의도가 정확히 뭐야?

* `second`초가 흐르면, 14칸 전광판에 **왼쪽→오른쪽으로 차례로 찍히는** 느낌?
* 아니면 **오른쪽에서 들어와서 왼쪽으로 밀리는 스크롤**?

의도에 맞게 `base` 계산도 딱 맞춰서 정리해줄게.
