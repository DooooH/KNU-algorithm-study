# 내려가기
이전 줄의 3개 숫자만 다음 줄의 결과에 영향을 주므로, 이 문제는 크기가 3인 배열로도 해결할 수 있다.

이처럼 전체 자료를 특정 크기만큼만 사용해 해결하는 기법을 슬라이딩 윈도우라 한다.

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, arr[3], max_dp[3], min_dp[3];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < 3; i++) {
		cin >> max_dp[i];
		min_dp[i] = max_dp[i];
	}

	int temp_0, temp_2;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 3; j++) cin >> arr[j];
		temp_0 = max_dp[0], temp_2 = max_dp[2];
		max_dp[0] = max(max_dp[0], max_dp[1]) + arr[0];
		max_dp[2] = max(max_dp[1], max_dp[2]) + arr[2];
		max_dp[1] = max(temp_0, max(max_dp[1], temp_2)) + arr[1];
		
		temp_0 = min_dp[0], temp_2 = min_dp[2];
		min_dp[0] = min(min_dp[0], min_dp[1]) + arr[0];
		min_dp[2] = min(min_dp[1], min_dp[2]) + arr[2];
		min_dp[1] = min(temp_0, min(min_dp[1], temp_2)) + arr[1];
	}

	int maxval = max(max_dp[0], max(max_dp[1], max_dp[2]));
	int minval = min(min_dp[0], min(min_dp[1], min_dp[2]));

	printf("%d %d\n", maxval, minval);

	return 0;
}
```
***
# 짚신벌레

k일째 짚신벌레를 dp[k]라 할 때,   
k가 a일 또는 그 이후라면 증식하는 짚신벌레 수는 a일 전의 개체수와 같다.  
(이는 곧 k - a일째의 모든 짚신벌레가 k일째에 성체가 된다는 것을 의미)  

이처럼 증식을 멈추는 짚신벌레, 죽는 짚신벌레의 개체 수도 동일하게 구할 수 있다.

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory.h>

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

int a, b, d, n;
int dp[1000001];

void get_dp() {
	for (int i = 0; i < a; i++) dp[i] = 1;

	for (int i = a; i <= n; i++) {
		//증식만 진행되는 경우 : 증식되어 증가하는 개체수는 a일 전의 개체 수와 같다.
		dp[i] = (dp[i - 1] + dp[i - a]) % 1000;
		//증식을 멈추기 시작 : 개체의 증가량은 a일 전 개체 수에서 b일 전 개체수를 뺀 만큼이다.
		//즉, 증식을 멈추는 개체 수가 곧 b일 전의 개체수이다.
		if (b <= i) {
			dp[i] = (dp[i] - dp[i - b] + 1000) % 1000;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	cin >> a >> b >> d >> n;
	get_dp();
	int answer = dp[n];
	if (n >= d) answer = (answer + 1000 - dp[n - d]) % 1000;
	printf("%d\n", answer);

	//system("PAUSE");
	return 0;
}
```
***
# 최솟값
기본 세그먼트 트리 적용 문제

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

#define MAXSIZE 100001
#define INF 2000000000

using namespace std;
typedef long long ll;

int n, m;
int segtree[MAXSIZE * 4];
int value[MAXSIZE];

int create_segtree(int node, int start, int end) {
	if (start == end) {
		//리프 노드
		segtree[node] = value[start];
		return segtree[node];
	}
	int mid = (start + end) / 2;
	segtree[node] = min(create_segtree(node * 2, start, mid), create_segtree(node * 2 + 1, mid + 1, end));
	return segtree[node];
}

int query(int node, int start, int end, int l, int r) {
	//구간에 포함되지 않는 경우
	if (l > end || start > r) return INF;

	//구간에 완전히 포함되는 경우
	if (l <= start && end <= r) return segtree[node];

	//구간에 걸치는 경우
	int mid = (start + end) / 2;
	return min(query(node * 2, start, mid, l, r), query(node * 2 + 1, mid + 1, end, l, r));
}

void init() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		cin >> value[i];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	create_segtree(1, 1, n);

	int s, e;
	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		printf("%d\n", query(1, 1, n, s, e));
	}
	
	//system("PAUSE");
	return 0;
}
```
