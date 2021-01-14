# 양 구출 작전
```
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;
int n;
long long value[123457];
vector<int> tree[123457];

long long dfs(int node) {
	long long retval = 0;

	for (int i = 0; i < tree[node].size(); i++) {
		retval += dfs(tree[node][i]);
	}
	retval += value[node];
	if (retval < 0) retval = 0;

	return retval;
}

void init() {
	char c;
	cin >> n;

	for (int i = 2; i <= n; i++) {
		int val, path;
		cin >> c >> val >> path;
		if (c == 'W') value[i] = -1 * val;
		else value[i] = val;
		tree[path].push_back(i);
	}
}

int main() {
	init();
	long long answer = dfs(1);
	printf("%ld\n", answer);

	return 0;
}

```
tree를 vector로 구현하여, root부터 재귀 dfs로 자식 노드들 value를 합해    
원하는 답을 구할 수 있음

# 빙산
```
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory.h>

using namespace std;

//우 - 하 - 좌 - 상
int r[4] = {0, 1, 0, -1};
int c[4] = { 1, 0, -1, 0 };

int n, m;	//n : row, m : col
int board[301][301] = { -1, };
int melboard[301][301];
bool visit[301][301] = { false, };
int answer, startrow, startcol, cnt, dcnt;

int getside(int row, int col) {
	//상하좌우 바닷물과 접한 면의 갯수 반환
	int ret = 0;
	for (int i = 0; i < 4; i++)
		if (!board[row + r[i]][col + c[i]]) ret++;
	return ret;
}

void dfs(int row, int col) {
	visit[row][col] = true;
	dcnt++;
	//우-하-좌-상 순으로 탐색
	if (board[row][col + 1] > 0 && !visit[row][col + 1]) {
		dfs(row, col + 1);
	}
	if (board[row + 1][col] > 0 && !visit[row + 1][col]) {
		dfs(row + 1, col);
	}
	if (board[row][col - 1] > 0 && !visit[row][col - 1]) {
		dfs(row, col - 1);
	}
	if (board[row - 1][col] > 0 && !visit[row - 1][col]) {
		dfs(row - 1, col);
	}
}

void melt() {
	//초기화
	memset(melboard, 0, sizeof(melboard));
	memset(visit, 0, sizeof(visit));
	cnt = 0; dcnt = 0;
	//1년 후 빙산의 감소 높이 저장 (melboard)
	for (int i = 2; i < n; i++) {
		for (int j = 2; j < m; j++) {
			if (board[i][j] < 1) continue;
			if (cnt == 0) {
				//선형으로 읽는 중 가장 처음 만나는 빙산의 위치
				startrow = i; startcol = j;
			}
			//빙산 갯수 증가
			cnt++;
			melboard[i][j] = getside(i, j);
		}
	}
	if (cnt == 0) {
		answer = 0; return;
	}
	//dfs로 (startrow, startcol) 좌표에서 연결된 빙산 탐색.
	//탐색이 끝난 시점에서 방문한 총 빙산 개수가 cnt와 같지 않다면 종료 (떨어진 빙산 존재)
	dfs(startrow, startcol);
	if (dcnt != cnt) return;

	//높이 갱신
	for (int i = 2; i < n; i++) {
		for (int j = 2; j < m; j++) {
			board[i][j] -= melboard[i][j];
			if (board[i][j] < 0) board[i][j] = 0;
		}
	}
	answer++;

	//재귀
	melt();
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> board[i][j];

	melt();

	cout << answer;

	return 0;
}
```

예전에 풀어서 dfs가 다소 깔끔하진 않음

# 효율적인 해킹
```
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
int n, m;
vector<int> tree[10001];
bool visit[10001];
vector<int> rets;
int answer = 0;

int dfs(int node) {
	int retval = 1;
	visit[node] = true;
	for (int i = 0; i < tree[node].size(); i++) {
		if(!visit[tree[node][i]]) retval += dfs(tree[node][i]);
	}
	return retval;
}

void init() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int first, second;
		cin >> first >> second;
		tree[second].push_back(first);
	}
}

int main() {
	init();

	for (int i = 1; i <= n; i++) {
		int ret = 0;
		memset(visit, 0, sizeof(visit));
		ret = dfs(i);
		if (ret > answer) {
			rets.clear();
		}
		if(ret >= answer) {
			answer = ret;
			rets.push_back(i);
		}
	}

	sort(rets.begin(), rets.end());
	for (int i = 0; i < rets.size(); i++) printf("%d ", rets[i]);
	printf("\n");

	return 0;
}

```

# 경주로 건설
```
#include <string>
#include <vector>

using namespace std;
int n;
int visit[26][26];
pair<int, int> dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

void dfs(vector<vector<int>> board, int row, int col, int d, int cost) {
	visit[row][col] = cost;
	if (row == n - 1 && col == n - 1) return;

	for (int i = 0; i < 4; i++) {
		int newR = row + dir[i].first;
		int newC = col + dir[i].second;

		if (newR < 0 || newR > n - 1 || newC < 0 || newC > n - 1) continue;

		int newCost = cost + 100;
		if (cost > 0 && d != i) newCost += 500;		//코너 비용

		if (board[newR][newC]) continue;
		if (visit[newR][newC] > 0) {
			if (visit[newR][newC] != -1 && visit[newR][newC] >= newCost) { dfs(board, newR, newC, i, newCost); continue; }
			else continue;
		}
		else dfs(board, newR, newC, i, newCost);
	}
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    n = board.size();
    visit[1][1] = -1;
    dfs(board, 0, 0, -1, 0);
    answer = visit[n-1][n-1];
    return answer;
}
```

기본적으로 visit 배열을 통해 이미 방문한 칸인지 체크하는 dfs 방식을 따르지만,   
해당 칸에 도착했을 때 더 적은 cost로 해당 칸을 갈 수 있다면 이미 방문한 칸이라도 새로 갱신한다.   
(단, 이 때 같은 cost라도 재방문 하여야 한다. 더 적은 비용의 경로로 갈 수 있기 때문)