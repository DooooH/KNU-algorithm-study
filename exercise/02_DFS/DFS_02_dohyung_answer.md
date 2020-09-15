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
