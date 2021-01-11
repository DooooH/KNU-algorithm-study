# 철로

각 구간을 끝점 기준으로 오름차순 정렬한 후, 우선순위 큐를 사용

큐에서 한 구간을 뽑은 뒤, 그 구간의 끝점을 기준으로 d 이내에 있는 시작점을 가진 구간들을 카운팅한다. (우선순위 큐를 이용해 먼 지점부터 확인)

만약 d 이내에 담을 수 없는 구간이 있다면, 큐에서 뽑아낸다.

즉, 큐에 담겨 있는 구간의 시작점들은 현재 구간에서 d 이내에 존재하는 구간들의 시작점과 같다. 따라서 큐의 크기가 곧 조건을 만족하는 구간의 개수와 같다.

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory.h>

using namespace std;
typedef pair<int, int> p;

int n, d;
vector<p> lines;

int greedy() {
	priority_queue<int, vector<int>, greater<int>> pque;
	int answer = 0, start, end;

	for (int i = 0; i < n; i++) {
		p curline = lines[i];
		if (curline.second - curline.first > d) continue;
		pque.push(curline.first);

		while (!pque.empty()) {
			int stand = pque.top();
			if (curline.second - stand <= d) break;
			pque.pop();
		}
		answer = max(answer, (int)pque.size());
	}

	return answer;
}

bool compare(p a, p b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second < b.second;
}

void init() {
	int o, h;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> o >> h;
		if (o > h) swap(o, h);
		lines.push_back({ o, h });
	}

	cin >> d;
	sort(lines.begin(), lines.end(), compare);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	int answer = greedy();
	printf("%d\n", answer);

	//system("PAUSE");
	return 0;
}

```
***
# 박성원

비트마스크 + DP 문제이다.

각 수를 이용한 순열을 만든다고 할 때, 그 수의 순서와는 상관없이 사용된 수들에 대한 정보만으로 DP 배열을 설계할 수 있다.

dp[state][r] = 비트마스크 state의 비트가 1인 수들을 사용해 나머지 r을 만드는 경우의 수

이제 dp[0][0]부터 재귀형태로 원하는 값을 구한다. state에 아직 사용하지 않은 수를 하나씩 추가해 새로운 state를 만들어가고, 

state = (1 << n) - 1일 때의 나머지가 0인 Case에 도달할 수 있는 경우를 모두 센다. (즉, 재귀실행을 통해 dp[1111111][0]에 갈 수 있는 가짓수를 센다)

※ 원하는 target 나머지를 만들기 위한 연산에 주의

이러한 접근 방법을 갖는 다른 문제로는 BOJ1176_섞기 가 있음.

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <memory.h>

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

int n, k;
ll dp[1 << 16][100];
int remain_cache[16], remain_len[16];
int rcache[51];
vector<string> inputs;

int get_remain(string input, int k) {
	int ret = 0;
	for (int i = 0; i < input.size(); i++) {
		ret = (ret * 10 + (input[i] - '0')) % k;
	}
	return ret;
}

ll get_dp(int state, int r) {
	//만약 모든 수를 다 사용했을 때, 나머지가 0이 되는지 확인
	if (state == (1 << n) - 1) return r == 0 ? 1 : 0;

	ll& ret = dp[state][r];
	if (ret != -1) return ret;

	ret = 0;

	for (int i = 0; i < n; i++) {
		//i번째 비트가 현재 state에 포함되어 있는지 확인
		if (state & (1 << i)) continue;

		//i번째 비트를 추가한 상태
		int nextstate = state | (1 << i);

		//i + 1번째 수를 마지막으로 했을 때, 마지막 수의 나머지
		int remain_last = remain_cache[i + 1];

		//i + 1번째 수를 추가했을 때의 전체 나머지
		int target = (r * rcache[remain_len[i + 1]] + remain_last) % k;

		//다음 State에 대해 재귀실행
		ret += get_dp(nextstate, target);
	}

	return ret;
}

void prev_action() {
	//cache 저장
	for (int i = 1; i <= n; i++) {
		int remain = get_remain(inputs[i], k);
		remain_cache[i] = remain;
		remain_len[i] = inputs[i].size();
	}
}

void init() {
	string input;
	cin >> n;

	memset(dp, -1, sizeof(dp));

	inputs.push_back("");
	for (int i = 1; i <= n; i++) {
		cin >> input;
		inputs.push_back(input);
	}
	cin >> k;

	rcache[0] = 1 % k;
	for (int i = 1; i <= 50; i++) rcache[i] = (rcache[i - 1] * 10) % k;
}

ll get_gcd(ll a, ll b) {
	while (b != 0) {
		ll temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	prev_action();

	ll answer = get_dp(0, 0);

	if (answer == 0) {
		printf("0/1\n");
		return 0;
	}

	ll total = 1;
	for (int i = 1; i <= n; i++) total *= i;

	if (answer == total) {
		printf("1/1\n");
		return 0;
	}

	ll gcd = get_gcd(total, answer);

	printf("%lld/%lld\n", answer / gcd, total / gcd);

	//system("PAUSE");
	return 0;
}

```
***
# 탈옥

문제에서 감옥 밖의 상근이에 대한 정보가 주어졌기 때문에, 총 3개의 지점에서 BFS 탐색을 실행한다. (두 죄수와 상근이)

이를 위해서는 최초 평면도를 가장자리에 한 줄씩 추가한 (h + 2, w + 2) 형태로 설정해야 한다.

탐색 시 기록하는 것은 연 문의 개수이며, 다익스트라와 유사하게 더 적은 문의 개수로 도달할 수 있을 경우 이를 반영해야 함에 주의한다.

3개의 출발점에서 탐색을 모두 마쳤을 경우, 이 각 탐색에 대해 연 문의 개수를 각 좌표마다 모두 더해준다.

단, 해당 좌표가 원래 문이 있었던 좌표일 경우, 문을 중복으로 여는 것을 고려해 2를 빼준다. (같은 문을 3번 열었으므로)

모든 평면도의 좌표에 대해 이 값의 최솟값을 찾으면 된다.

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory.h>

#define INF 99999999

using namespace std;
typedef pair<int, int> p;

int h, w, board[102][102];
int opened[3][102][102];		//각 출발점 별 연 문의 개수
pair<int, int> dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
vector<p> startpos;

struct compare {
	bool operator()(pair<p, int> a, pair<p, int> b) {
		return a.second > b.second;
	}
};

void bfs(p startpos, int mode) {
	priority_queue<pair<p, int>, vector<pair<p, int>>, compare> que;
	opened[mode][startpos.first][startpos.second] = 0;
	que.push({ startpos, 0 });

	while (!que.empty()) {
		pair<p, int> cur = que.top();
		que.pop();

		int row = cur.first.first;
		int col = cur.first.second;
		int cnt = cur.second;

		for (int d = 0; d < 4; d++) {
			int newR = row + dir[d].first;
			int newC = col + dir[d].second;

			if (newR < 0 || newR > h + 1 || newC < 0 || newC > w + 1) continue;
			if (board[newR][newC] == -1) continue;

			if (board[newR][newC] == 1) {
				if (cnt + 1 < opened[mode][newR][newC]) {
					opened[mode][newR][newC] = cnt + 1;
					que.push({ {newR, newC}, cnt + 1 });
				}
			}
			else {
				if (cnt < opened[mode][newR][newC]) {
					opened[mode][newR][newC] = cnt;
					que.push({ {newR, newC}, cnt });
				}
			}
		}
	}
}

void init() {
	string input_string;
	cin >> h >> w;
	
	memset(board, 0, sizeof(board));
	startpos.clear();

	for (int i = 0; i <= h + 1; i++) {
		for (int j = 0; j <= w + 1; j++) {
			opened[0][i][j] = INF;
			opened[1][i][j] = INF;
			opened[2][i][j] = INF;
		}
	}
	
	for (int i = 1; i <= h; i++) {
		cin >> input_string;
		for (int j = 1; j <= w; j++) {
			int input = input_string[j - 1];
			if (input == '*') board[i][j] = -1;
			if (input == '#') board[i][j] = 1;
			if (input == '$') startpos.push_back({ i, j });
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	int tc;
	cin >> tc;

	for (int i = 0; i < tc; i++) {
		init();
		bfs(startpos[0], 0);
		bfs(startpos[1], 1);
		bfs({ 0, 0 }, 2);

		int answer = 99999999;
		for (int row = 0; row <= h + 1; row++) {
			for (int col = 0; col <= w + 1; col++) {
				if (board[row][col] == -1) continue;
				int result = opened[0][row][col] + opened[1][row][col] + opened[2][row][col];
				if (board[row][col] == 1) result -= 2;
				answer = min(answer, result);
			}
		}

		printf("%d\n", answer);
	}

	return 0;
}
```
***
# 보석 쇼핑

투 포인터 알고리즘 문제라는 것은 알았지만 이를 어떻게 적용하느냐가 어려운 문제였음.

일반적인 투 포인터 문제처럼 양 끝에 포인터를 두는 것이 아닌 최초 지점에서 같이 출발하도록 해야 모든 구간을 확인할 수 있다.

문제의 핵심은 구간의 양 끝에 해당하는 보석이 그 구간 내에서 단 하나만 존재할 경우 더이상 구간을 줄일 수 없다는 것임

```C++
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> dict;

vector<int> solution(vector<string> gems) {
    int items = 0;      //보석 종류 수
    vector<int> answer;
    
    for(int i = 0; i < gems.size(); i++) {
        if(dict.find(gems[i]) == dict.end()){
            items++;
            dict.insert({gems[i], 0});
        }
    }

    int max_diff = 99999999;
    int lp = 0, rp = 0, cnt = 1;
    dict[gems[0]] = 1;
    while(1){
        //printf("lp is %d, rp is %d\n", lp, rp);
        if(rp == gems.size() - 1) break;
        while(cnt < items){
            //모든 종류의 보석을 담을 때까지 구간을 늘림
            if(rp == gems.size() - 1) break;
            rp++;
            if(dict[gems[rp]] == 0) cnt++;
            dict[gems[rp]] += 1;
            //printf("lp is %d, rp is %d\n", lp, rp);
        }
        
        //구간갱신
        if(rp - lp + 1 < max_diff){
            max_diff = rp - lp + 1;
            answer.clear();
            answer.push_back(lp + 1);
            answer.push_back(rp + 1);
        }
        
        while(cnt == items){
            //비는 보석이 생길 때까지 구간을 줄임
            dict[gems[lp]] -= 1;
            if(dict[gems[lp]] == 0) cnt--;
            lp++;
            //printf("lp is %d, rp is %d\n", lp, rp);
        }
        
        if(rp - lp < max_diff){
            max_diff = rp - lp;
            answer.clear();
            answer.push_back(lp);
            answer.push_back(rp + 1);
        }
    }
    return answer;
}
```
