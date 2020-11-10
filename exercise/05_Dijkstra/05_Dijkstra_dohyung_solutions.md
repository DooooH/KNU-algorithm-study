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
