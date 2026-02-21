이 코드는 `cmd` 명령을 순서대로 처리해서 **단일 연결 리스트**를 만들고/지우고, 마지막에 **노드 개수**를 반환해. 전반적으로 로직은 맞는데, 지금 `solution()`에는 **메모리 누수**가 있고, `remove_node()`에는 **의도에 따라 애매한 동작**(중복 삭제 방식)이 있어. 마지막으로, 네 `main` 입력에 대한 결과도 같이 계산해줄게.

---

## 1) 각 함수가 하는 일

### `insert_node(target, data)`

* `target` **바로 다음** 위치에 새 노드를 끼워넣음 (head 다음에 push 하는 형태)
* 그래서 INSERT가 여러 번 오면 **역순(스택처럼)**으로 쌓임

### `remove_node(head, data)`

* head부터 훑으면서 `data` 값이 같은 노드를 발견하면 제거
* 중요한 점: `free()`까지 해줌 ✅
* 그리고 `curr_node`를 “삭제했을 때는 그대로 둔다” → 그래서 같은 값이 연속으로 여러 개 있어도 계속 삭제 가능 ✅

즉, 현재 구현은 **해당 data 값을 가진 노드를 전부 삭제**하는 동작이야(“첫 번째만” 삭제가 아님).

---

## 2) 주어진 입력(cmd)으로 실제 결과는?

```c
int cmd[7][2] = {
  {1,1}, {1,4}, {1,2}, {1,3}, {1,1}, {2,2}, {2,1}
};
```

리스트 상태를 head 다음부터 나열하면:

1. INSERT 1  → [1]
2. INSERT 4  → [4, 1]
3. INSERT 2  → [2, 4, 1]
4. INSERT 3  → [3, 2, 4, 1]
5. INSERT 1  → [1, 3, 2, 4, 1]
6. REMOVE 2  → [1, 3, 4, 1]
7. REMOVE 1  → **1을 전부 삭제** → [3, 4]

따라서 노드 개수 = **2**

출력:

```
solution 함수의 반환 값은 2 입니다.
```

---

## 3) 현재 코드의 문제점 (중요)

### ✅ (1) 메모리 누수: head와 남은 노드들을 free 안 함

`solution()`은 리스트를 만들고 `count`만 반환하고 끝나는데,

* `head`도 malloc 했고
* 남아있는 노드들도 malloc 했는데
* 전부 해제하지 않음 → 누수

---

## 4) 누수까지 깔끔하게 정리한 버전

```c
int solution(int cmd[][2], int cmd_len) {
    struct NODE *head = (struct NODE*)malloc(sizeof(struct NODE));
    head->next = NULL;

    for (int i = 0; i < cmd_len; i++) {
        if (cmd[i][0] == INSERT)
            insert_node(head, cmd[i][1]);
        else if (cmd[i][0] == REMOVE)
            remove_node(head, cmd[i][1]);
    }

    int count = 0;
    struct NODE *curr = head->next;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    // ✅ 메모리 정리 (head 포함)
    curr = head;
    while (curr != NULL) {
        struct NODE *next = curr->next;
        free(curr);
        curr = next;
    }

    return count;
}
```

---

## 5) remove가 “하나만” 지우는 문제라면?

지금은 “data 값 전부 삭제”인데, 만약 “첫 번째만 삭제”가 요구사항이면 아래처럼 `return` 넣으면 돼:

```c
if (curr_node->next->data == data) {
    ...
    free(temp_node);
    return; // 첫 번째만 삭제
}
```

---

원래 REMOVE의 요구사항이 **“첫 번째만”**이야, 아니면 **“모두”**야?
문제 정의에 맞춰 `remove_node`를 딱 맞게 정리해줄게.
