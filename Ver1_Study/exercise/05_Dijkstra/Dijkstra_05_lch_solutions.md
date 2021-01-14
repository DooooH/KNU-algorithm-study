# 달빛 여우
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

#define INF 9999999999999999

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

int n, m;
ll dist_fox[4001];
ll dist_wolf[4001][2];
vector<p> adj[4001];

void dijkstra_fox() {
	priority_queue<pair<ll, int>> pque;
	dist_fox[1] = 0;
	pque.push({ 0, 1 });

	while (!pque.empty()) {
		pair<ll, int> cur = pque.top();
		pque.pop();

		ll distval = -cur.first;
		int node = cur.second;

		if (dist_fox[node] >= distval) {
			for (int i = 0; i < adj[node].size(); i++) {
				int nextnode = adj[node][i].first;
				ll newDist = distval + adj[node][i].second;
				if (dist_fox[nextnode] > newDist) {
					dist_fox[nextnode] = newDist;
					pque.push({ -newDist, nextnode });
				}
			}
		}
	}
}

void dijkstra_wolf() {
	priority_queue<pair<pair<ll, int>, int>> pque;
	dist_wolf[1][1] = 0;
	pque.push({ { 0, 1 }, 1 });

	while (!pque.empty()) {
		pair<pair<ll, int>, int> cur = pque.top();
		pque.pop();

		ll distval = -cur.first.first;
		int node = cur.first.second;
		int sprint = cur.second;

		if (dist_wolf[node][sprint] >= distval) {
			for (int i = 0; i < adj[node].size(); i++) {
				int nextnode = adj[node][i].first;
				ll newDist;
				if(sprint) newDist = distval + adj[node][i].second / 2;
				else newDist = distval + (long long)adj[node][i].second * 2;

				int nextsprint;
				if (sprint) nextsprint = 0;
				else nextsprint = 1;

				if (dist_wolf[nextnode][nextsprint] > newDist) {
					dist_wolf[nextnode][nextsprint] = newDist;
					pque.push({ { -newDist, nextnode }, nextsprint });
				}
			}
		}
	}
}


void init() {
	int f, s, w;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> f >> s >> w;
		adj[f].push_back({ s, w * 2 });
		adj[s].push_back({ f, w * 2 });
	}

	for (int i = 1; i <= n; i++) {
		dist_fox[i] = INF;
		dist_wolf[i][0] = INF;
		dist_wolf[i][1] = INF;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	dijkstra_fox();
	dijkstra_wolf();

	int answer = 0;
	for (int i = 2; i <= n; i++) {
		if (dist_fox[i] == INF) continue;
		if (dist_fox[i] < min(dist_wolf[i][0], dist_wolf[i][1])) answer++;
	}

	printf("%d\n", answer);

	return 0;
}
```
dist를 2차원으로 두어 2배속으로 도착했을 때와 1/2배속으로 도착했을 때를 구분한다.
***


# 주유소

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 999999999999

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

int n, m, val[2501];
ll dist[2501][2501];
vector<p> adj[2501];

void dijkstra() {
	//총 비용, 노드번호, 최소 기름값 노드
	priority_queue<pair<ll, p>> pque;
	pque.push({ 0, {1, 1} });

	dist[1][1] = 0;

	while (!pque.empty()) {
		pair<ll, p> cur = pque.top();
		pque.pop();

		ll distval = -cur.first;
		int node = cur.second.first;
		int minnode = cur.second.second;

		if (dist[node][minnode] >= distval) {
			for (int i = 0; i < adj[node].size(); i++) {
				int nextnode = adj[node][i].first;
				ll newDist = distval + val[minnode] * adj[node][i].second;
				int newMin = minnode;
				if (val[minnode] > val[nextnode]) newMin = nextnode;

				if (dist[nextnode][newMin] > newDist) {
					dist[nextnode][newMin] = newDist;
					pque.push({ -newDist, {nextnode, newMin} });
				}
			}
		}
	}
}

void init() {
	int f, s, w;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) cin >> val[i];

	for (int i = 0; i < m; i++) {
		cin >> f >> s >> w;
		adj[f].push_back({ s, w });
		adj[s].push_back({ f, w });
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dist[i][j] = INF;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	ll answer = INF;

	init();
	dijkstra();

	for (int i = 1; i <= n; i++) {
		if (dist[n][i] == INF) continue;
		answer = min(answer, dist[n][i]);
	}

	printf("%lld\n", answer);

	return 0;
}
```   
다익스트라 + DP   
dist[i][j] = j번 노드를 최소 기름값 노드로 하여 i번 노드에 도착했을 때의 최소비용
***


# 해킹
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 99999999

using namespace std;
typedef pair<int, int> p;

int tc, n, d, c;
vector<p> adj[10001];
int dist[10001];

void dijkstra(int start) {
	priority_queue<pair<int, p>> pque;
	pque.push({ 0, { c, 1 } });
	dist[c] = 0;

	while (!pque.empty()) {
		pair<int, p> cur = pque.top();
		pque.pop();

		int distval = -cur.first;
		int node = cur.second.first;
		int cnt = cur.second.second;

		if (dist[node] >= distval) {
			for (int i = 0; i < adj[node].size(); i++) {
				int nextnode = adj[node][i].first;
				int newDist = distval + adj[node][i].second;

				if (dist[nextnode] > newDist) {
					dist[nextnode] = newDist;
					pque.push({ -newDist, { nextnode, cnt + 1 } });
				}
			}
		}
	}
}

void init() {
	int a, b, s;
	cin >> n >> d >> c;

	for (int i = 1; i <= n; i++) adj[i].clear();

	for (int i = 0; i < d; i++) {
		cin >> a >> b >> s;
		adj[b].push_back({ a, s });
	}

	for (int i = 1; i <= n; i++) dist[i] = INF;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);
	
	cin >> tc;

	for (int i = 0; i < tc; i++) {
		int total = 0, answer = 0;
		init();
		dijkstra(c);

		for (int j = 1; j <= n; j++) {
			if (dist[j] == INF) continue;
			total++;
			if (dist[j] > answer) answer = dist[j];
		}
		
		printf("%d %d\n", total, answer);
	}

	return 0;
}
```
총 노드 수 : 출발점으로부터 연결된 노드들의 갯수, 즉 dist != INF 인 노드의 갯수   
전체 감염 시간 : INF를 제외하고 가장 높은 dist값
***


# 최단경로
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>

#define INF 99999999

using namespace std;
typedef tuple<int, int, int> t;
typedef pair<int, int> p;

int ver, e, start;
int dist[20001];
vector<p> adj[20001];	//인접 리스트
//우선순위 큐 (거리, 현재 노드)
priority_queue<p, vector<p>, greater<p>> pque;

void dijkstra() {
	while (!pque.empty()) {
		//우선순위 큐가 빌 때가 모든 경로의 가중치 합을 구했을 때이다.
		p cur = pque.top();
		pque.pop();

		int curdist = cur.first;
		int curnode = cur.second;
	
		//인접한 점들에 대해, cur에서 edge를 통해 그 점으로 이동했을 때의 가중치 총합과
		//현재 저장되어 있는 가중치 합을 비교한다.
		if (dist[curnode] >= curdist) {
			for (int i = 0; i < adj[curnode].size(); i++) {
				p temp = adj[curnode][i];
				if (dist[temp.first] > curdist + temp.second) {
					dist[temp.first] = curdist + temp.second;
					pque.push({ dist[temp.first], temp.first });
				}
			}
		}
	}
}

void init() {
	int u, v, w;
	cin >> ver >> e;
	cin >> start;

	fill(dist, dist + ver + 1, INF);
	dist[start] = 0;

	for (int i = 0; i < e; i++) {
		cin >> u >> v >> w;
		adj[u].push_back({ v, w });
	}
	//최초 큐 상태 만들기
	for (int i = 1; i <= ver; i++) {
		if(i == start) pque.push({ 0, i });
		else pque.push({ INF, i });
	}
}

int main() {
	init();

	dijkstra();

	for (int i = 1; i <= ver; i++) {
		if (dist[i] == INF) printf("INF\n");
		else printf("%d\n", dist[i]);
	}
	return 0;
}

```
기본적인 다익스트라 알고리즘
***