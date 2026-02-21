가능. 다만 C에서 `"2차원 배열"`이 **(A) 고정 길이 char 배열 2차원**인지, **(B) `char*` 포인터 배열 + 카운트 배열**인지에 따라 구현이 달라져.

코테/실무에서 제일 무난한 건 **결과를 구조체 배열로 모으는 방식**(= 사실상 2차원 느낌)이고, 그걸로 다시 정렬도 쉽다.

아래에 **둘 다** 바로 쓸 수 있게 예시 줄게.

---

## 1) 추천: 결과를 `struct` 배열에 넣기 (나중에 정렬/가공 최강)

### 결과 타입

```c
typedef struct {
    char *key;   // 문자열(포인터)
    int count;   // 횟수
} Pair;
```

### qsort로 묶고 → Pair 배열로 저장

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int count;
} Pair;

int cmp_strptr(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

// 예: count 내림차순, 같으면 key 오름차순
int cmp_pair_count_desc(const void *a, const void *b) {
    const Pair *pa = (const Pair *)a;
    const Pair *pb = (const Pair *)b;
    if (pa->count != pb->count) return (pb->count - pa->count);
    return strcmp(pa->key, pb->key);
}

int main(void) {
    char *arr[] = {"Java", "C++", "Javascript", "Java"};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    qsort(arr, n, sizeof(char *), cmp_strptr);

    Pair *out = (Pair *)malloc(sizeof(Pair) * n); // 최악(모두 유니크) n개
    int m = 0; // out에 실제로 들어간 개수

    int count = 1;
    for (int i = 1; i <= n; i++) {
        if (i < n && strcmp(arr[i], arr[i - 1]) == 0) {
            count++;
        } else {
            out[m].key = arr[i - 1];   // 정렬된 arr 안의 포인터를 그대로 참조
            out[m].count = count;
            m++;
            count = 1;
        }
    }

    // 이제 out[0..m-1]를 "원하는 기준"으로 재정렬 가능
    qsort(out, m, sizeof(Pair), cmp_pair_count_desc);

    // 확인 출력
    for (int i = 0; i < m; i++) {
        printf("[\"%s\", %d]\n", out[i].key, out[i].count);
    }

    free(out);
    return 0;
}
```

### 포인트

* `out[m].key = arr[i-1];` 는 “문자열 복사”가 아니라 **포인터만 저장**
  (지금은 문자열 리터럴이라 안전)
* 입력이 동적 문자열이면, 나중에 안전하게 쓰려면 `strdup`/`malloc+strcpy`로 복사해두는 게 좋음.

---

## 2) 진짜 “2차원 배열”로 넣기 (고정 길이)

`char out_key[MAX][MAX_LEN]` 같은 진짜 2차원 배열에 문자열을 **복사해서** 넣는 방식.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_LEN 50

int cmp_strptr(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main(void) {
    char *arr[] = {"Java", "C++", "Javascript", "Java"};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    qsort(arr, n, sizeof(char *), cmp_strptr);

    char keys[MAX][MAX_LEN];  // "2차원 배열"로 문자열 저장
    int counts[MAX];
    int m = 0;

    int count = 1;
    for (int i = 1; i <= n; i++) {
        if (i < n && strcmp(arr[i], arr[i - 1]) == 0) {
            count++;
        } else {
            strncpy(keys[m], arr[i - 1], MAX_LEN - 1);
            keys[m][MAX_LEN - 1] = '\0';
            counts[m] = count;
            m++;
            count = 1;
        }
    }

    // 여기서 keys/counts를 같이 다시 정렬하려면 "인덱스 swap" 정렬을 직접 구현하거나
    // Pair 구조체로 옮겨서 qsort 하는 게 편함.

    for (int i = 0; i < m; i++) {
        printf("[\"%s\", %d]\n", keys[i], counts[i]);
    }

    return 0;
}
```

### 단점

* “키 배열”과 “카운트 배열”이 분리되어 있어서 **재정렬이 귀찮아짐**
  → 그래서 보통은 `Pair` 구조체 배열로 묶어서 정렬한다.

---

## 결론

* **“그 후에 한 번 더 정렬”**이 목표면: **1번(Pair 구조체 배열)**이 정답에 가까워.
* 정말 2차원 배열이 필요하면 2번처럼 복사해서 넣되, 재정렬 편의성은 떨어짐.

원하는 “두 번째 정렬 기준”이

1. count 내림차순?
2. key 길이순?
3. 사전순?
   같은 구체 조건이면, 그 comparator까지 딱 맞춰서 만들어줄게.
