# 다익스트라(Dijksta Algorithm)
다익스트라 알고리즘은 DP를 활용한 최단경로 탐색 알고리즘이다. 특정한 하나의 정점에서 다른 모든 정점으로 가는 최단경로를 알려준다.
### 최단 경로 구하는 문제
+ Single source and single destination shortest path problem 
+ Single source shortest path problem :  **다익스트라 알고리즘**
+ Single destination shortest path problem
+ All pairs shortest path problem

## DP인 이유
+ 최단 거리는 여러 개의 최단 거리로 이루어져 있기 때문.
+ Memoziation을 사용함.

## 최단 경로 알고리즘 (배열 이용)
+ 네트워크에서 하나의 시작 정점으로 부터 모든 다른 정점까지의 최단 경로를 찾는 알고리즘이다. 
+ 네트워크에서 가중치는 가중치 인접 행렬인 2차원 배열에 저장된다. 간선이 없을 때 0이라는 값을 사용하는 것에 대해 제한된다.
+ 최단 거리를 기록하는 1차원 배열을 **Distance**라고 한다. 시작 정점을 v라고 했을 때, ```distance[v] = 0``` 이고 다른 정점에 대한 distance 값은 시작 정점과 해당 정점 간의 가중치가 된다. 가중치는 인접행렬에 저장되므로 **가중치 인접 행렬을 weight, ```distance[w] = wight[v][w]```과 같이 사용 할 수 있다.**
+ 단, 정점 v에서 정점 w로의 직접 간선이 없을 경우에는 무한대의 값을 저장한다. 시작 단계에서는 아직 최단 경로를 발견하지 못했으므로 ```S={v}```와 같을 것이다. 알고리즘이 진행되면서 최단 거리가 발견되는 정점들이 S에 하나씩 추가될 것이다.
+ 알고리즘의 매 단계에서 **집합 S안에 있지 않은 정점 중에서 가장 distance값이 작은 정점을 S에 추가**한다.
+ 정점 u가 S에 추가되면, S에 있지 않는 다른 정점들의 distance 값을 수정한다. 시작 기준점이 u로 바뀌었기 때문에, 새로 추가된 정점 u를 거쳐서 정점까지 가는 거리와 기존의 거리를 비교, 작은 값을 기준으로 distance 값을 수정한다. ```distance[w] = min(distance[w], distance[u]+weight[u][w])```

## 시간복잡도
+ 선형 탐색일 경우 O(N^2)
+ 힙 구조를 활용할 경우 O(NlogN)
