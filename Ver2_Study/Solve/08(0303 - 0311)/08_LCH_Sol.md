# 수상 택시

### 문제 유형
스위핑

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

int n, m;
vector<p> points;

ll sweeping() {
	ll ret = 0;
	int paths = 0, startpoint = -1;
	for (auto& cur : points) {
		if (startpoint == -1) startpoint = cur.first;
		paths += cur.second;

		if (paths == 0) {
			ret += (ll)cur.first - startpoint;
			startpoint = -1;
		}
	}
	return ret * 2 + m;
}

bool compare(p a, p b) {
	if (a.first == b.first) return a.second > b.second;
	return a.first < b.first;
}

void init() {
	int s, e;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> s >> e;
		if (s < e) continue;
		points.push_back({ s, 1 });
		points.push_back({ e, -1 });
	}

	sort(points.begin(), points.end());
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	ll answer = sweeping();
	printf("%lld\n", answer);

	return 0;
}
```

# 벽 부수고 이동하기 2

### 문제 유형
BFS

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;
typedef pair<int, int> p;
typedef pair<int, p> pp;

pair<int, int> dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int n, m, k;
int board[1001][1001], visit[1001][1001][11];

int bfs() {
	queue<pp> que;
	que.push({ 0, {1, 1} });
	visit[1][1][0] = 1;

	while (!que.empty()) {
		pp cur = que.front();
		que.pop();

		int brk = cur.first;
		int row = cur.second.first, col = cur.second.second;
		if (row == n && col == m) return visit[row][col][brk];

		for (int i = 0; i < 4; i++) {
			int newR = row + dir[i].first, newC = col + dir[i].second;
			if (newR < 1 || newR > n || newC < 1 || newC > m) continue;

			if (board[newR][newC]) {
				if (brk == k) continue;
				if (visit[newR][newC][brk + 1]) continue;
				visit[newR][newC][brk + 1] = visit[row][col][brk] + 1;
				que.push({ brk + 1, {newR, newC} });
			}

			else {
				if (visit[newR][newC][brk]) continue;
				visit[newR][newC][brk] = visit[row][col][brk] + 1;
				que.push({ brk, {newR, newC} });
			}
		}
	}
	return -1;
}

void init() {
	string input;
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		cin >> input;
		for (int j = 0; j < input.size(); j++) {
			board[i][j + 1] = input[j] - '0';
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	printf("%d\n", bfs());

	return 0;
}
```

# 좋다
### 문제 유형
투 포인터

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <memory.h>

using namespace std;
typedef pair<int, int> p;

int n;
vector<int> list;

bool find_num(int target) {
	int lp = 0, rp = n - 1;

	int tnum = list[target];
	while (lp < rp) {
		int sum = list[lp] + list[rp];
		if (sum == tnum) {
			if (lp != target && rp != target) 
				return true;
		}
		if (sum > tnum) rp--;
		else if(sum < tnum) lp++;
		else {
			if (list[lp] == tnum) lp++;
			if (list[rp] == tnum) rp--;
		}
	}
	return false;
}

void init() {
	int v;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> v;
		list.push_back(v);
	}

	sort(list.begin(), list.end());
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	int answer = 0;
	for (int i = 0; i < n; i++) {
		if (find_num(i)) answer++;
	}
	printf("%d\n", answer);

	//system("PAUSE");
	return 0;
}

```

# 욕심쟁이 판다
### 문제 유형

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> p;

pair<int, int> dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int n, board[500][500], dp[500][500];

int dfs(int row, int col) {
	if (dp[row][col]) return dp[row][col];

	int ret = 1;
	for (int i = 0; i < 4; i++) {
		int newR = row + dir[i].first, newC = col + dir[i].second;
		if (newR < 0 || newR == n || newC < 0 || newC == n) continue;
		if (board[newR][newC] > board[row][col]) {
			ret = max(ret, dfs(newR, newC) + 1);
		}
	}

	return dp[row][col] = ret;
}

void init() {
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> board[i][j];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	int answer = 0;
	for (int i = 0; i < n * n; i++)
		answer = max(answer, dfs(i / n, i % n));
	printf("%d\n", answer);

	return 0;
}
```