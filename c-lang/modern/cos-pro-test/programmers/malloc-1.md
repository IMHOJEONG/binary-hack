좋다 👍
이건 진짜 **C 실력 올라가는 구간**이야.

너가 지금 헷갈리는 건 딱 하나야:

> ❓ “malloc 했으면 언제 free 해야 하지?”

이걸 정리해주면 동적배열이 안 무서워진다.

---

# 🔥 핵심 원칙 하나

> 💡 **malloc 한 곳이 아니라, “소유권이 끝나는 지점”에서 free 한다**

---

# 1️⃣ 2차원 동적배열 기본 패턴 (정석)

```c
int **arr = malloc(sizeof(int*) * R);
for (int i = 0; i < R; i++) {
    arr[i] = malloc(sizeof(int) * C);
}
```

### 반드시 이렇게 해제해야 함:

```c
for (int i = 0; i < R; i++) {
    free(arr[i]);
}
free(arr);
```

💥 순서 중요
행을 먼저 free → 마지막에 arr free

---

# 2️⃣ 실전에서 free 타이밍은 언제?

## 📌 케이스 1 — 함수 내부에서 만들고 내부에서만 쓰는 경우

```c
int foo() {
    int *a = malloc(sizeof(int) * 10);

    // 사용

    free(a);  // ✅ 여기서 해제
    return 0;
}
```

👉 **함수 끝나기 전에 free**

---

## 📌 케이스 2 — 함수에서 malloc해서 반환하는 경우

```c
int* makeArray() {
    int *a = malloc(sizeof(int) * 10);
    return a;  // 여기서 free ❌
}
```

이 경우:

```c
int *arr = makeArray();
// 사용
free(arr);   // ✅ 여기서 free
```

👉 **malloc한 함수가 아니라, “사용이 끝난 쪽”이 free**

이게 소유권 개념.

---

# 3️⃣ 너가 만든 garden 복사 구조에서 free 시점

```c
int **cur = copyGarden(garden);

while (...) {
    int **next = setValue(cur);
    freeGarden(cur);   // ✅ 여기서 이전 배열 제거
    cur = next;
}

freeGarden(cur);  // 마지막 것도 제거
```

💡 핵심은:

> “새 배열을 만들었으면 이전 배열은 더 이상 필요 없음 → 즉시 free”

---

# 4️⃣ 실전에서 제일 많이 하는 실수

## ❌ 실수 1 — 덮어쓰기

```c
cur = setValue(cur);  // 💥 이전 cur 주소를 잃어버림
```

이러면 free 못함 → 메모리 누수

---

## ❌ 실수 2 — 2차원에서 free 하나만 함

```c
free(arr);   // 💥 내부 행 메모리 누수
```

반드시:

```
free(arr[i]) 전부
→ free(arr)
```

---

# 5️⃣ free 타이밍 판단 공식

이 질문을 스스로에게 해봐:

> ❓ 이 포인터를 앞으로 또 사용할 건가?

* 사용한다 → free ❌
* 더 이상 사용 안 한다 → free ✅

---

# 6️⃣ malloc/free 연습용 미니 문제

## 🔥 연습 과제 1

* 5x5 배열 만들기
* 값 채우기
* 출력
* 완전히 free 하기

## 🔥 연습 과제 2

* 2차원 배열을 복사하는 함수 만들기
* 원본 free
* 복사본 유지 확인

---

# 7️⃣ 실전 감각 키우는 방법

### 💡 디버그 프린트 활용

```c
printf("malloc: %p\n", arr);
printf("free: %p\n", arr);
```

주소를 찍어보면 메모리 흐름이 눈에 들어온다.

---

# 🔥 진짜 중요한 감각 하나

C에서:

> malloc = 내가 메모리 빌림
> free = 내가 반납함

반납 안 하면 → 누수
두 번 반납하면 → 크래시

---

# 🎯 코테에서의 전략

코테는:

* BFS 큐는 보통 스택 배열로
* 2차원은 문제에서 주어짐
* 복사 필요할 때만 malloc

실전 서버 개발에서는

* 소유권 개념
* 구조체 단위로 free
* RAII 없음 → 수동 관리

---

# 🔥 내가 추천하는 다음 단계

원하면 내가:

1. ❓ "왜 이 코드에서 메모리 누수가 발생할까?" 문제 내주고
2. 네가 고쳐보고
3. 내가 리뷰해주는 방식으로 훈련해볼래?

이거 한 번 하면 malloc/free 완전히 잡힌다.
