# 칵테일

첫 노드에 모든 수의 최소공배수를 넣고 시작해 비례식을 이용해 그래프 탐색으로 각 노드 값 갱신

마지막에 모든 수의 최대공약수로 나눠줌

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> p;
typedef pair<int, p> pp;

int n;
ll val[10], lcm_all = 1;
bool visit[10];
vector<pp> adj[10];

ll gcd(ll a, ll b) {
	ll temp;
	if (a < b) swap(a, b);
	while (b) {
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

ll lcm(ll a, ll b) {
	ll g = gcd(a, b);
	return a * b / gcd(a, b);
}

void dfs(int node, int pnode) {
	for (int i = 0; i < adj[node].size(); i++) {
		int child = adj[node][i].first;
		if (child == pnode) continue;

		int p = adj[node][i].second.first;
		int q = adj[node][i].second.second;

		//현재 val[node]를 알고 있으므로
		val[child] = (val[node] * q) / p;
		dfs(child, node);
	}
}

void init() {
	cin >> n;
	for (int i = 0; i < n; i++) val[i] = 1;

	int f, s, w1, w2;
	for (int i = 0; i < n - 1; i++) {
		cin >> f >> s >> w1 >> w2;
		adj[f].push_back({ s, {w1, w2} });
		adj[s].push_back({ f, {w2, w1} });

		lcm_all *= lcm(w1, w2);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	val[0] = lcm_all;
	dfs(0, -1);

	ll gcd_all = val[0];
	for (int i = 1; i < n; i++) gcd_all = gcd(gcd_all, val[i]);

	for (int i = 0; i < n; i++) printf("%lld ", val[i] / gcd_all);

	return 0;
}
```
***
# IQ Test

https://4legs-study.tistory.com/113?category=886580

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <memory.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> p;

int n, seq[50];

void get_answer() {
	//예외 : 처음 두 수가 같은 경우, 반드시 세 번째 항도 같아야 함
	if (seq[0] == seq[1]) {
		for (int i = 2; i < n; i++) {
			if (seq[i] != seq[0]) {
				printf("B\n");
				return;
			}
		}
		printf("%d\n", seq[0]);
		return;
	}

	//첫 번째 수에 대해, 가능한 a, b의 쌍을 구한다.
	int a = (seq[2] - seq[1]) / (seq[1] - seq[0]);
	int b = seq[2] - (seq[1] * a);

	//나머지 수들에 대해 확인하기
	for (int i = 0; i < n - 1; i++) {
		if (seq[i] * a + b != seq[i + 1]) {
			printf("B\n");
			return;
		}
	}

	printf("%d\n", seq[n - 1] * a + b);
}

void init() {
	cin >> n;

	for (int i = 0; i < n; i++) cin >> seq[i];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	if (n == 1) { printf("A\n"); return 0; }
	if (n == 2) {
		if (seq[0] == seq[1]) printf("%d\n", seq[0]);
		else printf("A\n");
		return 0;
	}
	get_answer();

	//system("PAUSE");
	return 0;
}

```
***

# 히스토그램

분할 정복으로 해결

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
typedef long long ll;

int n;
ll h[100010];

ll dq(int start, int end) {
	ll retval = 0;
	int mid = (start + end) / 2;
	int left = mid, right = mid + 1;

	if (start == end) return h[start];

	ll leftval = dq(start, left);
	ll rightval = dq(right, end);

	retval = max(leftval, rightval);
	ll minh = min(h[left], h[right]);

	retval = max(retval, (ll)minh * 2);
	while (left > start || right < end) {
		if (right < end && (left == start || h[left - 1] < h[right + 1])) {
			//오른쪽 이동
			minh = min(minh, h[++right]);
		}
		else {
			minh = min(minh, h[--left]);
		}
		retval = max(retval, minh * (right - left + 1));
	}
	//최소높이 직사각형 넓이 계산
	//retval = max(retval, (ll)minh * (end - start + 1));

	return retval;
}


void init(int k) {
	int input;
	//memset(h, 0, sizeof(h));
	for (int i = 1; i <= k; i++) {
		cin >> input;
		h[i] = input;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	while (1) {
		cin >> n;
		if (n == 0) break;
		init(n);
		ll answer = dq(1, n);
		printf("%lld\n", answer);
	}

	return 0;
}
```
***
# 사회망 서비스

Tree DP

모든 자식 노드가 얼리어답터가 아니라면 부모 노드만 얼리어답터

하나라도 얼리어답터라면 부모 노드도 얼리어답터

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;
typedef pair<int, int> p;

int n;
vector<int> adj[1000001];
int degree[1000001];
bool visit[1000001];	//false면 root
int root, answer = 0;

bool recursive(int node) {
	//리프 노드인 경우 : 고려하지 않음
	visit[node] = true;
	if (node != 1 && degree[node] == 1) return false;
	//node가 root인 부분트리를 기준으로 생각한다.
	//각 자식 노드들마다 재귀실행해 그 자식노드가 EA인지 확인한다.
	//모든 자식들의 EA여부를 확인한 후, 현재 node의 EA 여부를 결정한다.
	int ea_cnt = 0;

	for (int i = 0; i < adj[node].size(); i++) {
		if (visit[adj[node][i]]) continue;
		if (recursive(adj[node][i])) ea_cnt++;
	}

	answer += ea_cnt;
	//node의 자식 노드들 중 EA가 아닌 노드의 갯수
	int ea_child = degree[node] - 1 - ea_cnt;
	if (node == 1) ea_child++;

	//모든 자식이 EA라면 현재 node는 EA가 아니어도 됨
	if (ea_child == 0) return false;
	//하나 이상의 자식이 EA가 아니라면, 자기 자신이 EA가 됨
	else return true;
}

void init() {
	int parent, child;
	cin >> n;

	fill(degree, degree + n + 1, 0);

	for (int i = 0; i < n - 1; i++) {
		cin >> parent >> child;
		adj[parent].push_back(child);
		adj[child].push_back(parent);
		degree[parent] += 1;
		degree[child] += 1;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	bool result = recursive(1);
	if (result) answer++;



	printf("%d\n", answer);

	return 0;
}
```

