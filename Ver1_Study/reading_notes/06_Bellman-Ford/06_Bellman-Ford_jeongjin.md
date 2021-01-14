# Bellman-Ford 알고리즘
> 하나의 시작점에서 하나의 도착점으로 가는 최단 경로 문제를 해결하는 알고리즘이다.\
> 음의 간선이 있는 경우에도 문제를 해결한다.
+ 경로 중간에 존재하는 음수 순환이 문제가 된다.
+ 최단 경로는 순환을 포함해서는 안된다.
+ 최단 경로의 길이는 최대 **Vertex - 1** 이다.
+ 직선 정점 하위 그래프(Predecessor subgraph)
    + 최단 경로 트리(Shortest-path tree)
    + 최적해 구조(Optimal substructure) 
+ 완화 (Relaxation)
    + 현재 경로 값보다 더 적은 경로가 존재한다면 값을 변경한다.

## 벨만-포드 알고리즘 
```
BELLMAN-FORD(G, w, s)
    INITIALIZE-SINGLE-SOURCE(G,s)
        For i <- to|V[G]|-1
            do for each edge(u,v) ∈ E[G]
                do RELAX(u,v,w)
            for each dege(u,v)∈ E[G]
                do if d[v] > d[u]+w(u,v)
                    then return FALSE
        return True
```
1. 출발 노드 설정
2. 최단 거리 테이블 초기화
3. N-1번 반복
    1. 전체 간선 E개를 하나씩 확인
    2. 각 간선을 거쳐 다른 노드로 가는 비용을 계산해 최단 거리 테이블 갱신
4. 음수 간선 순환이 생기는지 확인하려면, 3번을 한번더 수행.
    - 최단 거리 테이블이 갱신되면 음수 간선 순환이 존재함.
## 벨만-포드 알고리즘
시간복잡도 O(VE)