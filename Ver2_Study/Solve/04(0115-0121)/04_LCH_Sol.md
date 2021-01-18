# Parcel

완전 탐색 시 O(N^4)로 시간초과가 발생하므로, 적어도 O(N^2) 또는 O(N^2logN)의 시간복잡도로 문제를 해결해야 한다.

이 점에서 4개의 물건을 뽑아 w의 무게를 만드는 것을 다음과 같은 문제로 바꿀 수 있다.

w1 + w2 + w3 + w4 = w

w1 + w2 = w - (w3 + w4)

따라서 2중 for문으로 한 쌍의 물건 무게 합을 기록해둔 뒤, 앞 순서에 살펴 본 쌍에서 무게의 합이 w - (현재 쌍의 무게 합) 인 쌍을 발견했었는지 확인해주면 된다.

단, 예제의 5, 2, 1 처럼 같은 무게가 두 번 카운팅되지 않도록 별도의 변수를 하나 더 기록한다.

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> p;

int n, w;
int value[5000];
p possible[799995];

bool get_answer() {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			int halfsum = value[i] + value[j];
			if (w < halfsum) continue;
			if (possible[w - halfsum] != make_pair(-1, -1)) {
				p cur = possible[w - halfsum];
				if (i == cur.first || i == cur.second || j == cur.first || j == cur.second) continue;
				return true;
			}
			possible[halfsum] = { i, j };
		}
	}
	return false;
}

void init() {
	cin >> w >> n;

	for (int i = 0; i < n; i++) cin >> value[i];
	for (int i = 0; i <= w; i++) possible[i] = { -1, -1 };
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	if (get_answer()) printf("YES\n");
	else printf("NO");

	return 0;
}
```
***
# 책 페이지

DP로 해결.  

1 ~ 9, 10 ~ 99, 100 ~ 999 범위 내에 등장하는 숫자의 횟수를 미리 구해놓은 뒤,

수의 각 자리에 따라 나누어가며 구할 수 있다.

0의 경우는 동일한 방법을 적용할 순 없고, 누적합이 별도로 필요하다.

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;
typedef long long ll;

int n, len, digit[11];
ll times[10], c[10] ,z[10], acc_z[10];

void set_digit() {
	string n_str = to_string(n);
	len = n_str.size();

	for (int i = len - 1; i >= 0; i--) digit[len - i - 1] = n_str[i] - '0';

	c[1] = 1;
	for (int i = 2; i < 10; i++) c[i] = c[i - 1] * 10 + pow(10.0, i - 1);

	z[1] = 9;
	for (int i = 2; i < 10; i++) z[i] = (ll)i * 9 * pow(10.0, i - 1);
}

void get_answer(int num, int d) {
	int cur = len - 1;
	while (1) {
		if (cur == 0) {
			if (d <= num) times[d] += 1;
			break;
		}

		int factor = pow(10.0, cur);
		int div = num / factor;
		times[d] += c[cur] * div;
		if (d < digit[cur]) times[d] += factor;
		if (d == digit[cur]) times[d] += (ll)num % factor + 1;

		num %= factor;
		cur--;
	}
}

void count_zero(int num) {
	int cur = len - 1, factor = 0;
	acc_z[0] = 1;
	for (int i = 1; i < 10; i++) acc_z[i] = acc_z[i - 1] + z[i];

	int temp = num;
	while (temp > 0) {
		if (temp % 10) times[0] += pow(10.0, factor);
		else times[0] += (ll)num % (int)pow(10.0, factor) + 1;

		times[0] += z[factor++] / 9 * (temp % 10);
		temp /= 10;
	}

	if (factor >= 2) times[0] -= (z[factor - 1] / 9 - acc_z[factor - 2]) + pow(10.0, factor - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	cin >> n;
	set_digit();

	for (int i = 1; i < 10; i++) get_answer(n, i);
	count_zero(n);
	times[0] -= 1;

	for (int i = 0; i < 10; i++) {
		printf("%lld ", times[i]);
	}

	return 0;
}
```
***
# 앱

0-1 Knapsack

DP의 기준을 메모리가 아닌 재실행 시간으로 둔다.

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <memory.h>

using namespace std;
typedef long long ll;

int n, m, max_ctime;
int mem[101], c[101];
//dp[i] : i만큼의 재실행 시간을 통해 확보할 수 있는 최대 메모리
ll dp[10001][101];	

int get_dp() {
	int answer = 1999999999;

	for (int i = 1; i <= n; i++) {
		for (int csum = 1; csum <= max_ctime; csum++) {
			if (c[i] > csum) {
				dp[csum][i] = dp[csum][i - 1];
				if (dp[csum][i] >= m) answer = min(answer, csum);
				continue;
			}
			dp[csum][i] = max((ll)dp[csum - c[i]][i - 1] + mem[i], dp[csum][i - 1]);
			if (dp[csum][i] >= m) answer = min(answer, csum);
		}
	}
	return answer;
}

void init() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> mem[i];
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		max_ctime += c[i];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	int answer = get_dp();
	printf("%d\n", answer);

	//system("PAUSE");
	return 0;
}

```
***
# 사전

풀이 링크 : https://4legs-study.tistory.com/19?category=886580

중복조합 관련 성질을 통해 DP 점화식을 구할 수 있다.

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int n, m;
unsigned long long k, dp[101][101]; //dp : a가 i개, z가 j개 있을 때 가능한 모든 문자열의 갯수

string getanswer() {
	int acnt = 0;
	long long acc = 0; 
	string answer = "";

	if (k > dp[n][m]) answer = "-1";
	else {
		while (1) {
			if (k == 1) {
				for (int i = 0; i < n; i++) answer += "a";
				for (int i = 0; i < m; i++) answer += "z";
				break;
			}
			if (k == dp[n][m]) {
				for (int i = 0; i < m; i++) answer += "z";
				for (int i = 0; i < n; i++) answer += "a";
				break;;
			}
			acnt = 0; acc = 0; 
			//dp누적합을 이용해 z 하나의 위치를 앞쪽으로 당겨가며 
			//z 이후의 문자열에 대한 dp값을 통해 z의 위치 결정
			for (int i = 0; i <= n; i++) {
				if (k <= acc + dp[i][m - 1]) { acnt = n - i; break; }
				acc += dp[i][m - 1];
			}
			//위치를 결정했다면, z의 위치까지 문자열은 확정임
			for (int i = 0; i < acnt; i++) answer += "a";
			answer += "z";
			//k값 갱신
			k -= acc;
			//n, m값 갱신
			n -= acnt; m--;
			if (k == 0) break;
		}
	}
	return answer;
}

void getdp() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
}

void init() {
	cin >> n >> m;
	cin >> k;

	for (int i = 0; i <= n; i++) dp[i][0] = 1;
	for (int i = 0; i <= m; i++) dp[0][i] = 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);
	
	init();
	getdp();
	string answer = getanswer();

	cout << answer << '\n';

	return 0;
}
```
