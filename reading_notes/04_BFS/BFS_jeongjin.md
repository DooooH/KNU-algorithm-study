# BFS(Breadth First Search) 너비 우선 탐색
### 박영철교수님 수업자료
    Breadth first search starts at vertex v and marks it as visited. It then visits each of the vertices on v's adjacency list. When we have visited all the vertices onv's adjacency list, we visit all the unvisited vertices that are adjacent to the first vertex on v's adjacency list. To implement this scheme, as we visit each vertex we place the vertex in a queue. When we have exhausted an adjacency list, we remove a vertex from the queue and proceed by examining each of the vertices on its adjacency list. Unvisited vertices are visited and then placed on the queue; visited vertices are ignored. We have finished the search when the queue is empty

### 김용태교수님 수업자료
#### BFS Procedure 
1) Starting at vertex v and marking it as visited
2) Visiting each of the vertices on v’s adjacency lists
– Visiting all the unvisited vertices that are adjacent to the first vertex on v’s
adjacency list
– Each visited vertex is placed into a queue
3) When an adjacency list is exhausted, a vertex needs to be removed from
a queue
4) Continuing the search by examining each of vertices on its adjacency list
5) The search terminates when the queue is empty


## 너비 우선 탐색
루트 노드(혹은 다른 임의의 노드)에서 시작해서 인접한 노드를 먼저 탐색하는 방법
 + 시작 정점으로 부터 가까운 정점을 방문하고 멀리 떨어져 있는 정점을 나중에 방문하는 순회방법이다.
 + 두 노드사이의 최단경로 혹은 임의의 경로를 찾고 싶을 때 이방법을 사용한다.
 ### 너비 우선 탐색의 특징
 + 직관적이지 않은 면이 있다. -> BFS는 시작 노드에서 시작해서 거리에 따라 단계별로 탐색한다고 볼 수 있다.
 + BFS는 재귀적으로 동작하지 않는다.
 + 그래프 탐색의 경우 어떤 노드를 방문했었는지 여부를 반드시 검사해야한다.
 + BFS는 방문한 노드들을 차례로 저장한 후 꺼낼 수 있는 자료구조인 큐(Queue)를 사용한다.
   + 선입선출 원칙으로 탐색
   + 일반적으로 큐를 이용해서 반복적 형태로 구현하는 것이 가장 잘 동작한다.
 + Prim, Dijkstra 알고리즘과 유사함.

 ## BFS 구현 (Geeksforgeeks)
 ```java
 // Java program to print BFS traversal from a given source vertex. 
// BFS(int s) traverses vertices reachable from s. 
import java.io.*; 
import java.util.*; 

// This class represents a directed graph using adjacency list 
// representation 
class Graph 
{ 
	private int V; // No. of vertices 
	private LinkedList<Integer> adj[]; //Adjacency Lists 

	// Constructor 
	Graph(int v) 
	{ 
		V = v; 
		adj = new LinkedList[v]; 
		for (int i=0; i<v; ++i) 
			adj[i] = new LinkedList(); 
	} 

	// Function to add an edge into the graph 
	void addEdge(int v,int w) 
	{ 
		adj[v].add(w); 
	} 

	// prints BFS traversal from a given source s 
	void BFS(int s) 
	{ 
		// Mark all the vertices as not visited(By default 
		// set as false) 
		boolean visited[] = new boolean[V]; 

		// Create a queue for BFS 
		LinkedList<Integer> queue = new LinkedList<Integer>(); 

		// Mark the current node as visited and enqueue it 
		visited[s]=true; 
		queue.add(s); 

		while (queue.size() != 0) 
		{ 
			// Dequeue a vertex from queue and print it 
			s = queue.poll(); 
			System.out.print(s+" "); 

			// Get all adjacent vertices of the dequeued vertex s 
			// If a adjacent has not been visited, then mark it 
			// visited and enqueue it 
			Iterator<Integer> i = adj[s].listIterator(); 
			while (i.hasNext()) 
			{ 
				int n = i.next(); 
				if (!visited[n]) 
				{ 
					visited[n] = true; 
					queue.add(n); 
				} 
			} 
		} 
	} 

	// Driver method to 
	public static void main(String args[]) 
	{ 
		Graph g = new Graph(4); 

		g.addEdge(0, 1); 
		g.addEdge(0, 2); 
		g.addEdge(1, 2); 
		g.addEdge(2, 0); 
		g.addEdge(2, 3); 
		g.addEdge(3, 3); 

		System.out.println("Following is Breadth First Traversal "+ 
						"(starting from vertex 2)"); 

		g.BFS(2); 
	} 
} 
// This code is contributed by Aakash Hasija 
```

## 시간복잡도
+ 인접 리스트로 표현된 그래프 : **O(N+E)**
+ 인접 행렬로 표현된 그래프: **O(N^2)**
+ 그래프 내에 적은 숫자의 간선만을 가지는 희소 그래프의 경우 인접 행렬보다 인접리스트를 사용하는 것이 유리함.


### Reference
 https://gmlwjd9405.github.io/2018/08/15/algorithm-bfs.html
