# 엘리베이터
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> p;

int n, m, dep, des;
//시작층, 간격
p els[101];
//이전에 탄 엘리베이터와 갈아탄 횟수를 기록
int visit[101], dist[101];
bool possible[101];
vector<int> finishes;
vector<int> path;

bool iscon(p a, p b) {
	//엘리베이터 a와 b가 연결되어 있는지 확인
	int item = b.first;
	if (a.first == b.first) return true;
	while (item <= n) {
		if (item >= a.first && (item - a.first) % a.second == 0) return true;
		item += b.second;
	}
	return false;
}

void bfs(int num) {
	//num번째 엘리베이터에서 출발해 옮겨탈 수 있는 모든 엘리베이터를 탐색
	//큐 : 엘리베이터를 탄 횟수, 엘리베이터 번호
	queue<p> que;
	que.push({ 1, num });
	visit[num] = num;
	dist[num] = 1;

	while (!que.empty()) {
		p cur = que.front();
		que.pop();

		int distval = cur.first;
		int elnum = cur.second;

		//목표층에 도달할 수 있다면  종료
		//이 때 elnum은 num에서 목표 층에 도달하는 
		//가장 빠른 경로의 마지막 직전 엘리베이터이다
		if (possible[elnum]) continue;

		//다른 모든 엘리베이터에 대해
		for (int i = 1; i <= m; i++) {
			if (i == elnum) continue;
			//현재 엘리베이터에서 옮겨탈 수 있는 엘리베이터인가?
			if (iscon(els[elnum], els[i])) {
				//이미 방문한 엘리베이터라도 더 빨리 도착할 수 있다면 갱신함
				if (dist[i] > distval + 1) {
					dist[i] = distval + 1;
					visit[i] = elnum;
					que.push({ distval + 1, i });
				}
			}
		}
	}
}

void init() {
	int d, interv;
	fill(visit, visit + 101, -1);
	fill(dist, dist + 101, 999);
	cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		cin >> d >> interv;
		els[i] = { d, interv };
	}

	cin >> dep >> des;

	for (int i = 1; i <= m; i++) {
		if (els[i].first <= des && (des - els[i].first) % els[i].second == 0) {
			//목표층에 도달가능한지 기록. 즉, finish인지 기록
			possible[i] = true;
			finishes.push_back(i);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();

	int answer = 999;
	int finish = -1;
	for (int i = 1; i <= m; i++) {
		//출발 층에 도달 가능한 엘리베이터에 대해서만
		if (dep < els[i].first ||(dep - els[i].first) % els[i].second != 0) continue;
		if (possible[i]) {
			printf("1\n%d\n", i);
			return 0;
		}
		bfs(i);
	}

	for (int i = 0; i < finishes.size(); i++) {
		//최소거리로 목표층에 도착했을 때의 마지막 엘리베이터 찾기
		if (answer > dist[finishes[i]]) {
			answer = dist[finishes[i]];
			finish = finishes[i];
		}
	}

	if (answer >= 999 || finish == -1) {
		//도달 불가
		printf("-1\n");
		return 0;
	}

	printf("%d\n", answer);
	while (1) {
		//경로 찾기
		path.push_back(finish);
		if (finish == visit[finish]) break;
		finish = visit[finish];
	}

	for (int i = path.size() - 1; i >= 0; i--) printf("%d\n", path[i]);

	return 0;
}
```
문제를 그래프로 구성하여 이해하고 알고리즘을 구상하는 것이 중요한 문제이다.
***

# 달이 차오른다, 가자

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
typedef tuple<int, int, int> tup;

int r, c;
//문 또는 열쇠는 board상에서 아스키 값으로 저장
int board[51][51], visit[1 << 6][51][51]; 
pair<int, int> startpoint;
int dir_r[4] = { -1, 0, 1, 0 };
int dir_c[4] = { 0, 1, 0, -1 };

int bfs() {
	//bfs로 start - end 의 최단거리를 구한다.
	queue<tup> que;
	que.push({ 0, startpoint.first, startpoint.second });
	visit[0][startpoint.first][startpoint.second] = true;

	while (!que.empty()) {
		tup cur = que.front();
		que.pop();
		
		int key = get<0>(cur);
		int row = get<1>(cur);
		int col = get<2>(cur);

		//end에 도착한 경우
		if (board[row][col] == -2) return visit[key][row][col];

		//문을 만난 경우
		if (board[row][col] >= 'A' && board[row][col] <= 'F') {
			//맞는 열쇠가 없다면 통과 불가
			bool open = key & (1 << (board[row][col] - 'A'));
			if (!open) continue;
		}

		//열쇠를 만난 경우
		int newkey = key;
		if (board[row][col] >= 'a' && board[row][col] <= 'f') {
			newkey |= (1 << (board[row][col] - 'a'));
		}
		
		for (int i = 0; i < 4; i++) {
			int newr = row + dir_r[i];
			int newc = col + dir_c[i];

			//범위 체크
			if (newr < 1 || newr > r || newc < 1 || newc > c) continue;
			//벽 체크
			if (board[newr][newc] == -1) continue;
			//방문여부 체크
			if (visit[newkey][newr][newc]) continue;
			visit[newkey][newr][newc] = true;

			que.push({ newkey, newr, newc });
			visit[newkey][newr][newc] = visit[key][row][col] + 1;
		}
	}
	//경로가 없는 경우
	return -1;
}

void init() {
	scanf("%d %d", &r, &c);
	for (int i = 1; i <= r; i++) {
		string input;
		cin >> input;
		for (int j = 0; j < c; j++) {
			if (input[j] == '.') { board[i][j + 1] = 0; continue; }
			if (input[j] == '#') { board[i][j + 1] = -1; continue; }
			if (input[j] == '1') { board[i][j + 1] = -2; continue; }
			if (input[j] == '0') { startpoint.first = i; startpoint.second = j + 1; continue; }
			board[i][j + 1] = input[j];
		}
	}
}

int main() {
	init();
	int result = bfs();
	if (result != -1) result -= 1;
	printf("%d\n", result);

	return 0;
}

```
BFS + Bitmask   
단, visit 배열을 3차원으로 구현해야 함을 주의

***
# DSLR
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;
typedef pair<int, string> p;

bool visit[10000];

int L(int num) {
	//1234 -> 2341, 0001 -> 10, 1000 -> 1
	int d = num / 1000;
	int r = num % 1000;
	return r * 10 + d;
}

int R(int num) {
	//1234 -> 4123
	int d = num / 10;
	int r = num % 10;
	return r * 1000 + d;
}

string bfs(int start, int end) {
	queue<p> que;
	que.push({ start, "" });
	visit[start] = true;

	while (!que.empty()) {
		p cur = que.front();
		que.pop();

		int n = cur.first;
		string path = cur.second;

		if (n == end) return path;

		int newN;
		//D연산
		newN = (n * 2) % 10000;
		if (!visit[newN]) {
			visit[newN] = true;
			que.push({ newN, path + "D" });
		}

		//S연산
		if(n > 0) newN = n - 1;
		else  newN = 9999;
		if (!visit[newN]) {
			visit[newN] = true;
			que.push({ newN, path + "S" });
		}

		//L연산
		newN = L(n);
		if (!visit[newN]) {
			visit[newN] = true;
			que.push({ newN, path + "L" });
		}

		//R연산
		newN = R(n);
		if (!visit[newN]) {
			visit[newN] = true;
			que.push({ newN, path + "R" });
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	int tc, s, e;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		memset(visit, 0, sizeof(visit));
		cin >> s >> e;
		
		string result = bfs(s, e);
		cout << result << '\n';
	}

	return 0;
}
```
마찬가지로, 문제를 그래프의 관점에서 이해하는 것이 중요하다.
***
# 타겟 넘버
```c++
#include <string>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> p;

bool visit[1 << 20];

int solution(vector<int> numbers, int target) {
    int answer = 0, sum = 0;
    int n = numbers.size();
    for(int i = 0; i < n; i++) sum += numbers[i];
    
    queue<p> que;
    que.push({sum, 0});
    visit[0] = true;
    
    while(!que.empty()){
        p cur = que.front();
        que.pop();
        
        int val = cur.first;
        int state = cur.second;
        
        if(val == target){
            answer++;
            continue;
        }
        
        for(int i = 0; i < n; i++){
            if(state & (1 << i)) continue;
            int newState = state | (1 << i);
            if(visit[newState]) continue;
            visit[newState] = true;
            que.push({val - 2 * numbers[i], newState});
        }
    }
    return answer;
}
```
BFS + Bitmask   
숫자의 개수가 최대 20개므로, 비트마스크를 적용할 수 있는 문제이다.   
(2^20 = 약 100만)