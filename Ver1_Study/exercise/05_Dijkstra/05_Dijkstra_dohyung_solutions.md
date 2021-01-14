## 백준 10282번 : 해킹

priority queue에서 pop한 노드는 비용이 결정되어 고정된다는 것을 생각해야한다.

```c++
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define INF 999999999

int test, num, depend, start;
int from, to, cost;
vector<pair<int, int>> link[10001];
int dist[10001];
priority_queue<pair<int, int>> pq;

void init_array()
{
	for (int i = 1; i <= num; i++)
	{
		if (i == start)
		{
			dist[i] = 0;
			continue;
		}
		dist[i] = INF;
	}
}

int find_max()
{
	int max_num = 0;

	for (int i = 1; i <= num; i++)
	{
		if (dist[i] == INF) continue;
		max_num = max(dist[i], max_num);
	}
	return max_num;
}

pair<int, int> dijkstra(int start)
{
	int current;
	int distance;
	int node;
	int node_cost;
	int count = 0;

	init_array();
	pq.push({0, start});
	while (!pq.empty())
	{
		distance = -pq.top().first;
		current = pq.top().second;
		pq.pop();
		if (dist[current] < distance) continue;
		count++;
		for (int i = 0; i < link[current].size(); i++)
		{
			node = link[current][i].first;
			node_cost = link[current][i].second;
			if (dist[node] > (distance + node_cost)){
				dist[node] = distance + node_cost;
				pq.push({-dist[node], node});
			}
		}
	}
	return {count, find_max()};
}

void clear_vector()
{
	for (int i = 0; i < 10001; i++)
		link[i].clear();
}

int main()
{
	pair<int, int> temp;

	cin >> test;
	for (int i = 0; i < test; i++)
	{
		clear_vector();
		cin >> num >> depend >> start;
		for (int j = 0; j < depend; j++)
		{
			cin >> to >> from >> cost;
			link[from].push_back(make_pair(to, cost));
		}
		temp = dijkstra(start);
		cout << temp.first << " " << temp.second << "\n";
	}
	return 0;
}
```

## 백준 1753번 : 최단경로

중복되는 걸 최소 비용만 가지도록 고쳐줘야하나?

```c++
#include <iostream>
#include <vector>
#include <queue>

#define INF 999999999

using namespace std;

int v, e, start;
int from, to, cost;
vector<pair<int, int>> link[20001];
int dist[20001];
priority_queue<pair<int, int>> pq;

bool is_samekey(pair<int, int> a, int val){
	return a.first == val;
}

void init_array()
{
	for (int i = 1; i <= v; i++)
	{
		if (i == start)
		{
			dist[i] = 0;
			continue;
		}
		dist[i] = INF;
	}
}

void dijkstra()
{
	int current;
	int distance;
	int node;
	int node_cost;

	init_array();
	pq.push({0, start});
	while (!pq.empty())
	{
		current = pq.top().second;
		distance = -pq.top().first;
		pq.pop();
		if (dist[current] < distance) continue;
		for (int i = 0; i < link[current].size(); i++)
		{
			node = link[current][i].first;
			node_cost = link[current][i].second;
			if (dist[node] >= distance + node_cost){
				dist[node] = distance + node_cost;
				pq.push({-dist[node], node});
			}
		}
	}
}

int find_key()
{
	for (int i = 0; i < link[from].size(); i++)
	{
		if (link[from][i].first == to)
			return i;
	}
	return -1;
}

int main()
{
	int idx;

	cin >> v >> e;
	cin >> start;
	for (int i = 0; i < e; i++)
	{
		cin >> from >> to >> cost;
		if ((idx = find_key()) != -1)
			link[from][idx].second = min(cost, link[from][idx].second);
		else
			link[from].push_back({to, cost});
	}
	dijkstra();
	for (int i = 1; i <= v; i++)
	{
		if (dist[i] == INF)
			cout << "INF\n";
		else
			cout << dist[i] << "\n";
	}
	return 0;
}
```


## 백준 16118번 : 달빛 여우

```c++
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 999999999999999

int v,e;
int from, to, cost;
// bool status[4001] = {false, };
vector<pair<int, int>> link[4001];
priority_queue<pair<long long, int>> pq_fox;	// 자료형 크기 고려
priority_queue<pair<pair<long long, int>, int>> pq_wolf;	// 자료형 크기 고려
long long dist_fox[4001] ={0, };
long long dist_wolf[4001][2] = {{0, }, {0, }};

void init_fox()
{
	for (int i = 2; i <= v; i++)
		dist_fox[i] = INF;
}

void init_wolf()
{
	for (int i = 2; i <= v; i++)
	{
		dist_wolf[i][0] = INF;
		dist_wolf[i][1] = INF;
	}
	dist_wolf[1][1] = INF;
}

void dijkstra_fox()
{
	int current;
	long long distance;
	int node;
	long long node_cost;

	init_fox();
	pq_fox.push({0, 1}); // cost, start = 1
	while (!pq_fox.empty())
	{
		current = pq_fox.top().second;
		distance = -pq_fox.top().first;
		pq_fox.pop();
		if (dist_fox[current] < distance) continue;
		for (int i = 0; i < link[current].size(); i++)
		{
			node = link[current][i].first;
			node_cost = link[current][i].second;
			if (dist_fox[node] >= distance + node_cost)
			{
				dist_fox[node] = distance + node_cost;
				pq_fox.push({-dist_fox[node], node});
			}
		}
	}
}

void dijkstra_wolf()
{
	int current;
	long long distance;
	int node;
	long long node_cost;
	int status;

	init_wolf();
	pq_wolf.push({{0, 1}, 0}); // cost, start = 1
	while (!pq_wolf.empty())
	{
		current = pq_wolf.top().first.second;
		distance = -pq_wolf.top().first.first;
		status = pq_wolf.top().second;
		pq_wolf.pop();
		if (dist_wolf[current][!status] < distance) continue;
		for (int i = 0; i < link[current].size(); i++)
		{
			node = link[current][i].first;
			if (status)
				node_cost = 2 * link[current][i].second;
			else
				node_cost = 0.5 * link[current][i].second;
			if (dist_wolf[node][status] >= distance + node_cost)
			{
				dist_wolf[node][status] = distance + node_cost;
				pq_wolf.push({{-dist_wolf[node][status], node}, !status});
			}
		}
	}
}

int	count_answer()
{
	int count = 0;

	for(int i = 1; i <= v; i++)
	{
		if (dist_fox[i] < dist_wolf[i][0] && dist_fox[i] < dist_wolf[i][1])
			count++;
		// cout << i << ":: " << dist_fox[i] << " " << dist_wolf[i][0] << " " << dist_wolf[i][1] << "\n";
	}
	return count;
}

int main()
{
	cin >> v >> e;
	for (int i = 0; i < e; i++)
	{
		cin >> from >> to >> cost;
		link[from].push_back({to, 2 * cost});
		link[to].push_back({from, 2 * cost});
	}
	dijkstra_fox();
	dijkstra_wolf();
	cout << count_answer();
	return 0;
}
```
