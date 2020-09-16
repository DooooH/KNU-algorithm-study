## 1325번: 효율적인 해킹

```c++
#include <bits/stdc++.h>

using namespace std;
stack<int> s;
vector<int> computer_map[100001];
vector<int> visit(100001, 0);
vector<pair<int, int> > cnts;

bool comp(pair<int, int> a, pair<int, int> b)
{
	if (a.second == b.second)
		return a.first < b.first;
	else
		return a.second > b.second;
}

void init_visit(int n)
{
	for (int i = 0; i < n + 1; i++)
		visit[i] = 0;
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n, m;
	int from, dest;

	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> dest >> from;
		computer_map[from].push_back(dest);
	}
	int cnt = 0;
	for (int i = 1; i < n + 1; i++)
	{
		cnt = 0;
		s.push(i);
		visit[i] = 1;
		while (!s.empty())
		{
			cnt++;
			int temp = s.top();
			s.pop();
			for (int j = 0; j < computer_map[temp].size(); j++)
			{
				if (visit[computer_map[temp][j]] != 1)
				{
					visit[computer_map[temp][j]] = 1;
					s.push(computer_map[temp][j]);
				}
			}
		}
		cnts.push_back(make_pair(i, cnt));
		init_visit(n);
	}
	sort(cnts.begin(), cnts.end(), comp);
	int k = 0;
	cout << cnts[k++].first;
	while (k <= n)
	{
		if (cnts[k].second != cnts[k - 1].second)
			break ;
		cout << " " << cnts[k++].first;
	}
	return (0);
}
```

## 16437번: 양 구출 작전

```c++
#include <bits/stdc++.h>
using namespace std;

vector<int> island[123457];
pair<char, int> type_cost[123457];

long dfs(int num)
{
	long sub_sum = 0;

	if (type_cost[num].first == 'S')
		sub_sum += type_cost[num].second;
	for (int i = 0; i < island[num].size(); i++)
	{
		sub_sum += dfs(island[num][i]);
	}
	if (island[num].size() == 0)
		return (sub_sum);
	if (type_cost[num].first == 'W') // has child && Wolf
	{
		sub_sum -= type_cost[num].second;
		if (sub_sum < 0)
			sub_sum = 0;
		return (sub_sum);
	}
	return (sub_sum);
}

int main()
{
	long answer = 0;
	int N;

	cin >> N;
	char	type;
	int		cost;
	int		from;
	for (int i = 2; i <= N; i++)
	{
		cin >> type >> cost >> from;
		island[from].push_back(i);
		type_cost[i] = make_pair(type, cost);
	}
	cout << dfs(1);
	return (0);
}
```

## 2573번: 빙산

```c++
#include <bits/stdc++.h>
using namespace std;

int arr[300][300];
int visit[300][300];
int speed[300][300];
int N, M;
int x[] = {1, -1, 0, 0};
int y[] = {0, 0, 1, -1};

int dfs(int i, int j)
{
	if (i < 0 || i >= N || j < 0 || j >= M)
		return (0);
	if (visit[i][j] == 0 && arr[i][j] != 0)
	{
		visit[i][j] = 1;
		for(int k = 0; k < 4; k++)
			dfs(i + x[k], j + y[k]);
		return (1);
	}
	return (0);
}

int count()
{
	int cnt = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cnt += dfs(i, j);
		}
	}
	memset(visit, 0, sizeof(visit));
	return cnt;
}

void update_speed()
{
	int cnt = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (arr[i][j] != 0)
			{
				for (int k = 0; k < 4; k++)
				{
					if (arr[i + x[k]][j + y[k]] == 0)
						cnt += 1;
				}
				speed[i][j] = cnt;
			}
			cnt = 0;
		}
	}
}

void after_year()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (arr[i][j] != 0)
			{
				arr[i][j] -= speed[i][j];
				if (arr[i][j] < 0)
					arr[i][j] = 0;
			}
		}
	}
}

int main()
{
	int year = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> arr[i][j];
	while (count() != 0)
	{
		update_speed();
		year++;
		after_year();
		if (count() >= 2)
		{
			cout << year;
			return (0);
		}
	}
	cout << 0;
	return 0;
}
```

## 경주로 건설

```c++
#include <bits/stdc++.h>
using namespace std;
#define MAX 627 * 500

int N;
int x[] = {0, 0, 1, -1};
int y[] = {1, -1, 0, 0};
int visit_arr[26][26];

void dfs(vector<vector<int>> board, int i, int j, int prev, int cost)
{
	int first_cost = cost;

	if (i < 0 || i >= N || j < 0 || j >= N)
		return ;
	if (i == N - 1 && j == N - 1)
	{
		visit_arr[i][j] = min(visit_arr[i][j], cost);
		return ;
	}
	if (visit_arr[i][j] == 0 && board[i][j] == 0)
	{
		if (visit_arr[i][j] == 0)
			visit_arr[i][j] = cost;
		else
			visit_arr[i][j] = min(cost, visit_arr[i][j]);
		for (int k = 0; k < 4; k++)
		{
			cost = first_cost;
			cost += 100;
			if (prev != -1 && ((k >= 2 && prev < 2) || (k < 2 && prev >= 2)))
				cost += 500;
			dfs(board, i + y[k], j + x[k], k, cost);
		}
	}
	else if (board[i][j] == 0 && visit_arr[i][j] > 0) // 벽이 아니면서, 방문한 적 있음
	{
		if (visit_arr[i][j] >= cost)
		{
			visit_arr[i][j] = min(cost, visit_arr[i][j]);
			for (int k = 0; k < 4; k++)
			{
				cost = first_cost;
				cost += 100;
				if (prev != -1 && ((k >= 2 && prev < 2) || (k < 2 && prev >= 2)))
					cost += 500;
				dfs(board, i + y[k], j + x[k], k, cost);
			}
		}
	}
}

int solution(vector<vector<int>> board) {
    int answer = 0;
	N = board.size();
	visit_arr[N-1][N-1] = MAX;
	dfs(board, 0, 0, -1, 0);
	answer = visit_arr[N - 1][N - 1];
    return answer;
}
```

테스트케이스 14번 통과 X
