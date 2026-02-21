이 코드는 **Union-Find(Disjoint Set Union, DSU)** 로 “간선을 순서대로 추가할 때, **처음으로 사이클이 생기는 간선의 번호(1-indexed)**”를 찾는 코드야.
주어진 입력에서는 3번째 간선 `{2,3}`을 추가할 때 사이클이 생기니까 답은 **3**이 돼.

아래에 함수별로 정확히 설명해줄게.

---

## 1) `find(parent, u)` — 대표(루트) 찾기 + 경로 압축

```c
int find(int parent[], int u) {
    if (u == parent[u]) return u;

    parent[u] = find(parent, parent[u]);
    return parent[u];
}
```

* `parent[x]`는 “x의 부모”를 가리킴
* 어떤 집합(set)의 대표는 **루트 노드**(자기 자신을 부모로 갖는 노드)
* `u == parent[u]`면 u가 루트라서 대표를 u로 반환

### 경로 압축(Path Compression)

```c
parent[u] = find(parent, parent[u]);
```

* 루트를 찾는 과정에서 거쳐간 노드들의 parent를 루트로 바로 붙여서
* 다음 find가 매우 빨라짐 (거의 O(1)에 가까워짐)

---

## 2) `merge(parent, u, v)` — 두 집합 합치기, 사이클 여부 판단

```c
int merge(int parent[], int u, int v) {
    u = find(parent, u);
    v = find(parent, v);

    if (u == v) return 1;  // 이미 같은 집합이면, 이 간선은 사이클 만든다

    parent[u] = v;         // 서로 다르면 합친다
    return 0;
}
```

* `u = find(...)`, `v = find(...)`로 각각 대표를 구함
* 대표가 같으면 이미 연결된 상태 → 여기에 간선을 추가하면 **사이클 발생**

  * 그래서 `1`을 반환
* 대표가 다르면 서로 다른 컴포넌트 → 합침

  * 여기선 단순히 `parent[u] = v`로 u의 루트를 v에 붙임
  * (rank/size 최적화는 없지만 기능은 OK)

---

## 3) `solution(n, connections, connections_len)` — 처음 사이클 생긴 간선 번호 찾기

```c
int *parent = malloc(sizeof(int) * (n+1));
for (int i = 1; i <= n; i++) parent[i] = i;
```

* 1~n까지 각 노드를 자기 자신이 대표인 집합으로 초기화

```c
for (int i = 0; i < connections_len; i++)
    if (merge(parent, connections[i][0], connections[i][1])) {
        answer = i + 1; // 1-indexed
        break;
    }
```

* 간선을 순서대로 하나씩 추가(merge)
* merge가 1을 반환하면 “사이클 생김”
* 그때의 간선 번호(1부터)를 answer에 넣고 종료

---

## 4) 주어진 예시에서 왜 답이 3인가?

입력:

```
n=3
(1,2), (1,3), (2,3)
```

### 초기

* {1}, {2}, {3}

### 1) (1,2)

* 1과 2는 다른 집합 → 합침
* {1,2}, {3}

### 2) (1,3)

* 1은 {1,2}, 3은 {3} → 합침
* {1,2,3}

### 3) (2,3)

* 2와 3은 이미 같은 집합({1,2,3})
* 여기서 연결하면 루프가 생김(사이클)
  → **3번째 간선에서 최초 사이클**, answer=3

출력:

```
solution 함수의 반환 값은 3 입니다.
```

---

## 5) 코드에서 개선하면 좋은 점

### ✅ 메모리 해제 누락

`parent`를 malloc 했는데 free 안 함.

```c
int result = answer;
free(parent);
return result;
```

### ✅ union by rank/size 추가하면 더 빠름

큰 입력에서 안정적인 성능을 위해 흔히 같이 씀.

---

원하면 내가:

* `union by size/rank`까지 포함한 “완성형 DSU 템플릿”
* 사이클 말고 **연결 요소 개수**, **두 노드 연결 여부** 같은 응용

도 같이 정리해줄까?
