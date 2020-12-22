# 그림 교환

DP문제로, 그림을 산 사람은 다시 그 그림을 살 수 없으므로 필요한 정보는 다음과 같다.   
 - 마지막으로 그림을 산 사람 (그 사람이 그림 가격의 기준이 된다.)
 - 현재까지 그림을 산 사람들에 대한 정보 (이를 비트마스크로 표현한다.)
 - 현재 그림의 가격 (다음 사람은 그보다 같거나 높은 가격에 사야 하므로)

 따라서, 이 3가지 정보를 담은 3차원 dp 배열을 만든다.   
 dp배열의 값은 일반적으로 그림을 가졌던 사람의 최대 수가 되겠지만, 이 문제의 경우 비트마스크 값을 통해 그림을 산 사람을 구할 수 있으므로 dp 배열의 값은 단지 도달 가능 여부만 나타내도록 했다.

 ※ 문제의 N 범위가 15까지의 매우 적은 수이므로, 비트마스크를 적용 가능한 문제임을 캐치할 수 있다.


```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <memory.h>

using namespace std;
typedef pair<int, int> p;

int n, max_cost;
int cost[16][16];
int dp[1 << 16][16][10];
int answer = 1;

int get_answer(int state) {
	int div = pow(2.0, 15);
	int ret = 0;

	while (div > 0) {
		if (state >= div) {
			state -= div;
			ret++;
		}
		div /= 2;
	}

	return ret;
}

void set_dp() {
	dp[1][1][0] = 1;

	for (int i = 1; i < (1 << n); i++) {
		int state = i;

		//state의 j번째 비트에 대해 (j는 마지막으로 산 사람의 번호를 의미)
		for (int j = 0; j < n; j++) {
			//최고 가격이 c인 경우
			for (int c = 0; c <= max_cost; c++) {
				//도달할 수 없는 경우는 무시
				if (dp[i][j + 1][c] == 0) continue;
				answer = max(answer, get_answer(i));

				//현재 state에서 그림을 산 사람에 대해서만
				if (state & (1 << j)) {
					//그림을 산 j번 사람에 대해 그림을 사지 않은 k번째 사람을 계산
					for (int k = 0; k < n; k++) {
						if (state & (1 << k)) continue;
						int newstate = state | (1 << k);
						if (cost[j + 1][k + 1] < c) continue;
						dp[newstate][k + 1][cost[j + 1][k + 1]] = 1;
					}
				}
			}
		}
	}
}

void init() {
	string input;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> input;
		for (int j = 1; j <= n; j++) {
			cost[i][j] = input[j - 1] - '0';
			max_cost = max(max_cost, cost[i][j]);
		}
	}

	//memset(dp, -1, sizeof(dp));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	set_dp();
	printf("%d\n", answer);

	return 0;
}
```
***
# 두 용액

용액들의 특성값을 오름차순으로 정렬한 뒤, 양 끝 용액에 대한 포인터(lp, rp)를 두어 다음과 같은 과정을 거쳐 답을 구한다. 
 - lp, rp에 해당하는 두 용액의 특성값 합을 구한다.
 - 그 합이 양수라면, rp의 값을 1 감소시킨다. 합이 음수라면, lp의 값을 1 증가시킨다. 이를 lp < rp인 동안 반복한다.
 - 이 과정에서 특성값 합의 절댓값이 곧 우리가 원하는 값이 된다. 이 값이 최소가 될 때의 lp, rp를 기록하면 된다.

 ```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 2100000000

using namespace std;
typedef pair<int, int> p;

int n;
vector<int> val;

p get_answer() {
	p ret = { 0, 0 };
	int lp = 0, rp = n - 1;
	int min_diff = INF;

	while (lp < rp) {
		int sum = val [lp] + val[rp];

		if (min_diff > abs(sum)) {
			min_diff = abs(sum);
			ret = { val[lp], val[rp] };
		}

		if (sum > 0) rp--;
		else lp++;
	}

	return ret;
}

void init() {
	int value;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> value;
		val.push_back(value);
	}

	sort(val.begin(), val.end());
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	p answer = get_answer();
	printf("%d %d\n", answer.first, answer.second);

	return 0;
}
 ```
***
# 부분 평균
이 풀이는 분할 정복 기법을 이용한 풀이이다.   
수학적 특성을 발견한 풀이는 시간적 측면에서 더 빨랐지만, 스스로 생각해낸 풀이가 아니라 업로드하지 않음.

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 999999999999

using namespace std;
typedef pair<double, int> p;
typedef long long ll;

int n;
ll arr[1000000];
int answer;

p dnc(int start, int end) {
	int diff = end - start + 1;
	if (diff == 1) return { INF, start };
	if (diff == 2) return { (arr[start] + arr[end]) / 2, start };

	p ret = { 0, 0 };
	int mid = (start + end) / 2;
	p left = dnc(start, mid);
	p right = dnc(mid + 1, end);

	int lp = mid, rp = mid + 1, avg_diff = 2;
	ll sum = arr[lp] + arr[rp];
	ret.first = (double)sum / 2;
	ret.second = lp;

	//mid를 지나는 구간에 대한 평균 비교
	while (start < lp || rp < end) {
		//더 작은 쪽으로 이동
		//오른쪽으로 이동하는 경우
		if (rp < end && (start < lp || arr[lp - 1] > arr[rp + 1])) {
			sum += arr[++rp]; avg_diff++;
			double avg = (double)sum / avg_diff;
			if (ret.first >= avg) {
				ret.first = avg;
				ret.second = lp;
			}
		}
		else {
			sum += arr[--lp]; avg_diff++;
			double avg = (double)sum / avg_diff;
			if (ret.first >= avg) {
				ret.first = avg;
				ret.second = lp;
			}
		}
	}

	if (ret.first > left.first) ret = left;
	if (ret.first > right.first) ret = right;

	return ret;
}

void init() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	p answer = dnc(0, n - 1);
	printf("%d\n", answer.second);

	return 0;
}
```
***
# 진법 변환
음수에 대한 나머지를 잘 정의하고 이를 통해 진법을 변환하는 문제이다.   
처음에는 계수를 분할하는 방식으로 접근했는데, 예외를 잡지 못해 이 방법으로 다시 설계했다.
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;
typedef pair<int, int> p;

string trans(int n, int b) {
	string ret = "";
	int number;

	if (b > 0) number = abs(n);
	else number = n;

	while (number) {
		int r = number % abs(b);
		if (r < 0) r += abs(b);
		number = (number - r) / b;
		ret += to_string(r);
	}
	if (ret.size() == 0) ret = "0";
	return ret;
}

int main() {
	int x, b;
	cin >> x >> b;

	string answer = trans(x, b);
	if (x < 0 && b > 0) printf("-");
	for (int i = answer.size() - 1; i >= 0; i--) {
		cout << answer[i];
	}
	printf("\n");

	return 0;
}
```
***
# 러버덕을 사랑하는 모임
다룰 수 있는 케이스의 수가 많지 않으므로, 완전탐색이 가능하다.   
러버덕을 나눠준 사람의 상태를 비트마스크로 나타낼 수 있으며, 이를 dfs로 탐색해 정확히 e개의 러버덕을 분배할 수 있는 경우를 찾는다.   
러버덕을 정확히 e개 나눌 수 있는 경우는 곧 각 사람들의 러버덕 갯수 범위를 더해, 최종적으로 그 범위가 e를 포함하는지를 확인하면 된다.   
출력해야 하는 답인 러버덕의 분배는 분배할 사람들에게 그 사람들이 원하는 최솟값만큼 모두 배분해 준 뒤, 남은 러버덕을 채워나가는 식으로 구현했다.
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pa;

int n, p, e;
int arr[21][2];
int distribute[20];
int result;
bool visit[1 << 20];

void dfs(int state, int l, int r, int cnt) {
	if (result > 0) return;
	if (visit[state]) return;
	visit[state] = true;

	if (cnt == p) {
		//정확히 분배할 수 있는 경우가 존재한다면
		if (l <= e && e <= r) result = state;
		return;
	}

	for (int j = 0; j < n; j++) {
		if (state & (1 << j)) continue;
		int newstate = state | (1 << j);
		dfs(newstate, l + arr[j][0], r + arr[j][1], cnt + 1);
		if (result > 0) return;
	}
}

void init() {
	int f, s;
	cin >> n >>p >> e;

	for (int i = 0; i < n; i++) {
		cin >> arr[i][0] >> arr[i][1];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	for (int i = 0; i < n; i++) {
		int start = 1 << i;
		dfs(start, arr[i][0], arr[i][1], 1);
		if (result > 0) break;
	}

	if (result == 0) {
		printf("-1\n");
		return 0;
	}

	//printf("result : %d\n", result);
	vector<pair<pa, int>> hopes;
	for (int i = 0; i < n; i++) {
		if (!(result & (1 << i))) continue;
		hopes.push_back({ { arr[i][0], arr[i][1] }, i });
	}
	
	sort(hopes.begin(), hopes.end());

	for (int i = 0; i < hopes.size(); i++) {
		//일단 모두 최솟값만큼 채워넣음
		pa cur = hopes[i].first;
		e -= cur.first;
		distribute[hopes[i].second] = cur.first;
	}

	for (int i = 0; i < hopes.size(); i++) {
		//남은 러버덕을 빈칸만큼 채워 나눠줌
		if (e == 0) break;
		pa cur = hopes[i].first;
		int diff = cur.second - cur.first;
		if (e < diff) {
			distribute[hopes[i].second] += e;
			e = 0;
		}
		else {
			distribute[hopes[i].second] += diff;
			e -= diff;
		}
	}

	for (int i = 0; i < n; i++) printf("%d ", distribute[i]);
	printf("\n");

	return 0;
}
```