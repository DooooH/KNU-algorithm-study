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

## 프로그래머스 : 타겟 넘버

초기 인덱스 설정을 잘못해서 고치는데 좀 걸림.  
시간 줄이려고 미리 나가게 한 부분도 있는데 시간 고려안해도 되는 경우면 dfs만 간결하게 더해서 재귀, 빼서 재귀 나열해서 하는게 더 깔끔했을 듯  

```c++
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int answer_cnt = 0;

// set subsum = 0, idx = 0
void dfs(vector<int> &numbers, int &target, vector<int> &subsums, int subsum, int idx)
{
    if (idx == numbers.size())
        return ;
    if (abs(target - subsum) > subsums[idx])
        return ;
    for (int i = 0; i < 2; i++)
    {
        int tempsum = subsum;
        int add = 1;
        if (i == 1)
            add = -1;
        tempsum += add * numbers[idx];
        if ((idx == numbers.size() - 1) && tempsum == target)
            answer_cnt++;
        dfs(numbers, target, subsums, tempsum, idx + 1);
    }
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int tempsum = 0;
    vector<int> subsums(numbers.size(), 0);
    for (int i = numbers.size() - 1; i >= 0; i--)
    {
        tempsum += numbers[i];
        subsums[i] = tempsum;
    }
    dfs(numbers, target, subsums, 0, 0);
    answer = answer_cnt;
    return answer;
}
```


## 백준 9019번 : DSLR

인덱스접근을 잘못해서 런타임에러가 났음.

```c++
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int from, to;
bool visit[10001] = {false, };
queue<pair<string, int>> q;

int oper_D(int num)
{
	return (num * 2) % 10000;
}

int oper_S(int num)
{
	if (num == 0)
		return 9999;
	else
		return num - 1;
}

int oper_L(int &num)
{
	int d1, d2, d3, d4;
	int temp = num;

	d1 = temp / 1000;
	temp = temp % 1000;
	d2 = temp / 100;
	temp = temp % 100;
	d3 = temp / 10;
	temp = temp % 10;
	d4 = temp;

	temp = 0;
	temp += d2 * 1000;
	temp += d3 * 100;
	temp += d4 * 10;
	temp += d1;
	return temp;
}

int oper_R(int &num)
{
	int d1, d2, d3, d4;
	int temp = num;

	d1 = temp / 1000;
	temp = temp % 1000;
	d2 = temp / 100;
	temp = temp % 100;
	d3 = temp / 10;
	temp = temp % 10;
	d4 = temp;

	temp = 0;
	temp += d4 * 1000;
	temp += d1 * 100;
	temp += d2 * 10;
	temp += d3;
	return temp;
}

void BFS()
{
	string path;
	int current_num;

	q.push(make_pair("", from));
	visit[from] = true;
	while (!q.empty())
	{
		path = q.front().first;
		current_num = q.front().second;
		q.pop();
		if (current_num == to)
			break;
		if (visit[oper_D(current_num)] == false)
		{
			q.push(make_pair(path + "D", oper_D(current_num)));
			visit[oper_D(current_num)] = true;
		}
		if (visit[oper_S(current_num)] == false)
		{
			q.push(make_pair(path + "S", oper_S(current_num)));
			visit[oper_S(current_num)] = true;
		}
		if (visit[oper_L(current_num)] == false)
		{
			q.push(make_pair(path + "L", oper_L(current_num)));
			visit[oper_L(current_num)] = true;
		}
		if (visit[oper_R(current_num)] == false)
		{
			q.push(make_pair(path + "R", oper_R(current_num)));
			visit[oper_R(current_num)] = true;
		}
	}
	cout << path << "\n";
}

void clear_queue()
{
	while (!q.empty())
		q.pop();
}

int main()
{
	int T;

	cin >> T;
	for (int i = 0; i < T; i++)
	{
		memset(visit, false, sizeof(visit));
		cin >> from >> to;
		BFS();
		clear_queue();
	}

	return 0;
}
```
