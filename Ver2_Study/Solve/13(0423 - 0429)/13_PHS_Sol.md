# 도는 스시

해싱 + 구현

다음 순서 확인할 때 i-1 빼주고 i + k - 1 추가 해서 탐색시간 O(N)으로 유지

```C++
#include <iostream>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n, d, k, c;
	short ary[33000];
	//scanf("%d%d%d%d", &n, &d, &k, &c);
	cin >> n >> d >> k >> c;
	for (int i = 0; i < n; i++)
		//scanf("%d", &ary[i]);
		cin >> ary[i];
	for (int i = 0; i < k; i++)
		ary[n + i] = ary[i];

	short visited[3001] = { 0 }, count = 1;
	visited[c] = 1;
	for (int i = 0; i < k; i++) {
		if (!visited[ary[i]]++)
			count++;
	}

	int mx = count;
	for (int i = 1; i < n; i++) {
		if (!--visited[ary[i - 1]])
			count--;
		
		if (!visited[ary[i+k - 1]]++)
			count++;

		mx = mx < count ? count : mx;
	}
	cout << mx;
}
```
---
# 세 용액

투포인터, left 지정한 후 mid = left+1, right = n-1 로 지정하여 mid, right를 투 포인터 돌림

```C++
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
	int n;
	int ary[5000];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &ary[i]);

	sort(ary, ary + n);

	int ml, mm, mr;
	long long mval = 1e9 * 3, t, at;

	for (int left = 0; mval && left < n - 2; left++) {
		for (int mid = left + 1, right = n - 1; mid != right;) {
			t = (long long)ary[left] + ary[mid] + ary[right];
			at = t > 0 ? t : -t;
			if (at < mval) {
				mval = at;
				ml = left, mm = mid, mr = right;
			}
			if (t > 0)--right;
			else if (t) ++mid;
			else break;
		}
	}
	printf("%d %d %d", ary[ml], ary[mm], ary[mr]);
}
```
---
# 오큰수

스텍 혹은 인덱싱

전에 풀었던 큰탑이 전파 송신하는 문제랑 똑같음

> stack
```C++
#include <cstdio>

int main() {
	int n;
	int ary[1000000], stk[1000000], ans[1000000], top = 1;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &ary[i]);
	ans[n - 1] = -1;
	stk[0] = ary[n - 1];

	for (int i = n - 2; i >= 0; i--) {
		while (top && ary[i] >= stk[top - 1])--top;
		ans[i] = top ? stk[top - 1] : -1;
		stk[top++] = ary[i];
	}
	for (int i = 0; i < n; i++)
		printf("%d ", ans[i]);
}
```
> 인덱싱
```c++
#include <cstdio>

int main() {
	int n;
	int ary[1000000], nge[1000000];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &ary[i]);
	nge[n - 1] = -1;


	for (int i = n - 2; i >= 0; i--) {
		int idx = i + 1;
		while (idx != -1 && ary[idx] <= ary[i])
			idx = nge[idx];
		nge[i] = idx;
	}
	for (int i = 0; i < n; i++)
		printf("%d ", nge[i] != -1 ? ary[nge[i]] : -1);
}
```
# 모두 0으로 만들기

2가지 방법 dfs, greedy

dfs : 돌면서 cost는 그대로 더해주고 answer은 절댓값 취해서 더해줌

greedy : 간선 들어오는거 inbound 체크하고 inbound가 1일때 처리해줌, 처리하고 연결된 놈들 inbound--

dfs가 처리 로직이 간단해서 더 빠르게 나옴, 깊이가 긴 bad 케이스에서 시간 튐

greedy가 조금 더 안정적인 시간 분포 가짐, 더 느린이유 아마 귀찮아서 최적화 안해가지고 그런듯

> dfs
```C++
#include <string>
#include <vector>
#include <stack>
using namespace std;
long long answer = 0;
vector<long long> cost;
vector<int> gph[300000];
void dfs(int cur, int prev) {
	for (int next : gph[cur]) {
		if (next != prev) {
			dfs(next, cur);
			answer += cost[next] > 0 ? cost[next] : -cost[next];
			cost[cur] += cost[next];
		}
	}
}
long long solution(vector<int> a, vector<vector<int>> edges) {

	cost.assign(a.begin(), a.end());

	for (auto &i : edges) {
		gph[i[0]].push_back(i[1]);
		gph[i[1]].push_back(i[0]);
	}

	dfs(0, -1);
	if (cost[0])return-1;
	return answer;
}

int main() {
	vector<int> a = { -5,0,2,1,2 };
	vector<vector<int>> e = { {0,1},{3,4},{2,3},{0,3} };
	solution(a, e);
}

/*
{-5,0,2,1,2}	{{0,1},{3,4},{2,3},{0,3}}	9
{0,1,0}	{{0,1},{1,2}}
*/
```
> greedy
```C++
#include <string>
#include <vector>
#include <queue>
using namespace std;


long long solution(vector<int> a, vector<vector<int>> edges) {
	long long answer = 0;

	int n = a.size();
	long long cost[300000];
	for (int i = 0; i < n; i++)
		cost[i] = a[i];

	vector<int> gph[300000];
	for (auto &i : edges) {
		gph[i[0]].push_back(i[1]);
		gph[i[1]].push_back(i[0]);
	}

	int inbound[300000];
	queue<int> que;
	for (int i = 0; i < n; i++) {
		inbound[i] = gph[i].size();
		if (gph[i].size() == 1)
			que.push(i);
	}
		
		
	bool visited[300000] = { 0 };
	int cur, next;
	while (!que.empty()) {
		cur = que.front();
		que.pop();
		visited[cur] = 1;

		for (int i = 0; i < gph[cur].size();i++) {
			if (visited[gph[cur][i]])continue;
			next = gph[cur][i];
			cost[next] += cost[cur];
			answer += cost[cur] > 0 ? cost[cur] : -cost[cur];
			if (--inbound[next] == 1)que.push(next);
		}
	}

	if (cost[cur])return -1;
	return answer;
}

int main() {
	vector<int> a = { -5,0,2,1,2 };
	vector<vector<int>> e = { {0,1},{3,4},{2,3},{0,3} };
	solution(a, e);
}

/*
{-5,0,2,1,2}	{{0,1},{3,4},{2,3},{0,3}}	9
{0,1,0}	{{0,1},{1,2}}
*/
```
