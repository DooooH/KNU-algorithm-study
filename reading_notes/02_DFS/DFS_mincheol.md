# 깊이 우선 탐색 (Depth first search, DFS)

DFS는 그래프 탐색 방법 중 하나로 임의의 노드에서 시작하여 다음 분기로 넘어가기 전 해당 분기를 완벽하게 탐색하는 방법이다. 

모든 노드를 방문하고자 하는 경우 사용한다.



## DFS의 특징

- 순환 알고리즘의 형태를 가지고 있어, 재귀적으로 구현된다.

- 그래프를 DFS로 탐색하는 경우,  트리와 달리 순환이 발생할 수 있으므로 깊이를 결정하거나, 어떤 노드를 방문했었는지 여부를 반드시 검사해야 한다.
- 가중치가 없는 그래프의 경우에는 시작점과의 최단 거리를 보면 깊이를 결정할 수 있다. 이 경우 시작점과의 거리가 같은 노드끼리는 같은 레벨이다.
- 단순 검색은 BFS에 비해서 느리다.



## 구현

- DFS 구현 방법에는 다음 두가지가 있다.
  - 재귀 호출
  - 스택
- 재귀

```java
void dfs(node root){
    if (root != null) {
        if (not visited) {
        	for (each node v in root) {
            	if (visited(v) == false) {
                	dfs(v);
            	}
            }
        }
    }
}
```

- 스택

```java
stack.push(root);
while(stack not empty) {
    node n = stack.pop;
    if (not visited n) {
        visited.n = true;
        for (each node v in n) {
            if (not visited v) {
                stack.push(v);
            }
        }
    }
}
```



## 시간 복잡도

- 그래프의 모든 간선을 조사하므로 시간 복잡도는 다음과 같다.
  - 인접 리스트 O(N+E)
  - 인접 행렬 O(N<sup>2</sup>)
    - N : 정점의 수, E : 간선의 수