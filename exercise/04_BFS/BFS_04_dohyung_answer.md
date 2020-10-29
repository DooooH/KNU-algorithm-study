## BOJ 1194번 : 달이 차오른다, 가자.

비트마스크를 활용해서 3차원 배열을 이용하는 것은 처음 해봄.  
BFS를 돌 때 큐에 넣으면서 방문표시를 해야하는데 pop하면서 방문체크해서 메모리초과가 났었음

```c++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int x[] = {0, 1, 0, -1};
int y[] = {1, 0, -1, 0};
int n,m;
char maze[50][50];
bool visit[1 << 6][50][50];
queue<pair<int, int>> q;
queue<pair<int, int>> cnt_key_q;

int BFS()
{
	pair<int, int> current;
	int count = 0;

	while (!q.empty())
	{
		current = q.front();
		q.pop();
		char current_char = maze[current.second][current.first];
		count = cnt_key_q.front().first;
		int cur_key_stat = cnt_key_q.front().second;
		if (current_char == '1')
			return (count);
		if (current_char >= 'a' && current_char <= 'f')
			cur_key_stat |= 1 << (current_char - 'a');
		cnt_key_q.pop();
		for (int i = 0; i < 4; i++)
		{
			int next_x = current.first + x[i];
			int next_y = current.second + y[i];
			if (next_x >= 0 && next_x < m && next_y >= 0 && next_y < n && !visit[cur_key_stat][next_y][next_x])//boundary & visit check
			{
				char next_char = maze[next_y][next_x];
				if (next_char != '#') // check wall
				{
					if (next_char >= 'A' && next_char <= 'F') //check_key
					{
						int idx = next_char - 'A';
						if (cur_key_stat & (1 << idx))
						{
							q.push(make_pair(next_x, next_y));
							cnt_key_q.push(make_pair(count + 1, cur_key_stat));
							visit[cur_key_stat][next_y][next_x] = true;	// queue에 넣을 때 방문표시
						}
					}
					else
					{
						q.push(make_pair(next_x, next_y));
						cnt_key_q.push(make_pair(count + 1, cur_key_stat));
						visit[cur_key_stat][next_y][next_x] = true;
					}
				}
			}
		}
	}
	return -1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	char temp;
	pair<int, int> start;	// 시작위치

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> temp;
			if (temp == '0')
				start = make_pair(j, i);
			maze[i][j] = temp;
			// maze[i].push_back(temp);
		}
	}
	q.push(start);
	cnt_key_q.push(make_pair(0, 0));
	cout << BFS();
	return 0;
}
```
