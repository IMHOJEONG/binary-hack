이 코드는 **두 개의 스택(stack1, stack2)을 이용해서 큐(queue)처럼 동작**하게 만드는 구조입니다.
즉, **2개의 스택으로 Queue의 pop 연산을 구현**한 코드입니다.

---

# 📌 전체 구조 요약

* `stack1` → 입력(push) 용 스택
* `stack2` → 출력(pop) 용 스택
* `solution()` → queue에서 하나 꺼내는 동작

동작 원리:

```
1️⃣ stack2가 비어있다면
   → stack1의 모든 원소를 stack2로 옮긴다 (역순 뒤집기)

2️⃣ stack2에서 pop 한다
```

이 방식은 **Queue의 FIFO(First In First Out)** 특성을 구현하는 전형적인 알고리즘입니다.

---

# 📌 각 함수 설명

---

## 1️⃣ func_c → 스택이 비었는지 확인

```c
bool func_c(int stack_idx){
    return (stack_idx == -1);
}
```

✔️ stack_idx가 -1이면 스택이 비어있다고 판단
✔️ top index를 기준으로 empty 체크

---

## 2️⃣ func_a → 스택 pop

```c
int func_a(int stack[], int *stack_idx) {
    int item = stack[*stack_idx];
    *stack_idx = *stack_idx - 1;
    return item;
}
```

✔️ 현재 top 값 꺼냄
✔️ 인덱스 1 감소
✔️ pop 연산

---

## 3️⃣ func_b → stack1 → stack2 전체 이동

```c
void func_b(int stack1[], int *stack1_idx, int stack2[], int *stack2_idx)
```

### 동작:

```c
while(!func_c(*stack1_idx)) {
    int item = func_a(stack1, stack1_idx);
    *stack2_idx = *stack2_idx + 1;
    stack2[*stack2_idx] = item;
}
```

✔️ stack1이 빌 때까지 반복
✔️ stack1에서 pop
✔️ stack2에 push

### 핵심 포인트

이 과정에서 **순서가 뒤집힘**

예시:

```
stack1: [1, 2, 3] (top=3)
↓ 이동
stack2: [3, 2, 1] (top=1)
```

→ 결과적으로 FIFO 구조 완성

---

# 📌 solution 함수 (핵심)

```c
int solution(int stack1[], int stack1_idx, int stack2[], int stack2_idx)
```

### 동작 순서

```c
if(func_c(stack2_idx)){
    func_b(stack1, &stack1_idx, stack2, &stack2_idx);
}
```

✔️ stack2가 비어있다면
✔️ stack1의 모든 데이터를 stack2로 이동

그 다음

```c
int answer = func_a(stack2, &stack2_idx);
```

✔️ stack2에서 pop
✔️ 가장 오래된 값 반환

---

# 📌 실행 예시 분석

---

## 🔹 첫 번째 케이스

```c
stack1 = {1,2}
stack2 = {3,4}
```

각 idx = 1

stack2는 비어있지 않음 → 바로 pop

```
stack2 top = 4
```

✔️ 반환값: **4**

---

## 🔹 두 번째 케이스

```c
stack1 = {1,2,3}
stack2 = empty
```

stack2_idx = -1 → 비어있음

### 1️⃣ stack1 → stack2 이동

```
stack2 = {3,2,1}
```

### 2️⃣ stack2 pop

```
pop → 1
```

✔️ 반환값: **1**

---

# 📌 이 코드의 알고리즘 이름

👉 **Two Stack Queue**
👉 **Queue using two stacks**

자료구조 면접에서 자주 나오는 문제입니다.

---

# 📌 시간복잡도

* 최악: O(n) (stack1 → stack2 전체 이동)
* 평균(암묵적 amortized): O(1)

---

# 📌 핵심 개념 요약

| 개념        | 설명           |
| --------- | ------------ |
| stack1    | push 전용      |
| stack2    | pop 전용       |
| stack2 비면 | stack1 전체 이동 |
| 결과        | FIFO 구조 완성   |

---

# 📌 시각적 흐름 정리

```
enqueue: stack1에 push
dequeue:
    if stack2 empty:
        stack1 → stack2 이동
    stack2 pop
```

---

# 📌 결론

이 코드는

✔️ 스택 2개로 큐 구현
✔️ FIFO 동작 구현
✔️ 자료구조 기본 문제

---

필요하면:

* 🔥 이걸 완전한 Queue 구조로 리팩토링해줄까?
* 🔥 push 함수까지 포함해서 클래식 구현 보여줄까?
* 🔥 메모리 안정성 문제까지 분석해줄까?

어디까지 깊게 볼지 말해줘 😎
