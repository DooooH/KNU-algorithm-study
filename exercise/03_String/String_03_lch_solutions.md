# 반복 패턴   
>Z 알고리즘 풀이
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
string s;
int n, k, answer;
int Z[100001];

void getZ() {
	//Z 알고리즘 - Z배열 구하기
	//l, r : S[i...]의 Prefix와 S의 Prefix가 같은 모든 Prefix들 중, 
	//가장 길고 오른쪽 인덱스를 가진 Prefix의 시작과 끝 인덱스
	int n = s.size(), l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		//비교하는 문자가 l-r 구간 이후의 문자일 경우
		if (i > r) {
			//참고할 정보가 없으므로 단순 비교
			l = i; r = i;
			while (s[r] == s[r - l]) r++;
			Z[i] = r - l;
			r--;
		}
		//비교하는 문자가 l-r 구간 사이일 경우
		else {
			if (Z[i - l] <= r - i) Z[i] = Z[i - l];
			else {
				l = i;
				while (s[r] == s[r - l]) r++;
				Z[i] = r - l;
				r--;
			}
		}
		//Z배열의 값을 통해 k개의 문자를 붙여 패턴이 될 수 있는지 판단
		int len_f = s.substr(0, i).size();
		int len_b = s.substr(i).size();
		if (Z[i] == len_b && len_f <= len_b + k) {
			//Z[i] 가 S[i...]의 길이와 같을 때만 K를 이어붙여 패턴으로 만들 수 있음.
			//단, S[i...] + K의 길이가 S[...i-1]의 길이와 같거나 길어야 함.
			//(즉, S[i...] 전체가 S의 Prefix여야 함

			//둘의 Prefix가 겹치는 예외 처리
			if (i < Z[i]) {
				//겹치는 경우, 패턴 자체는 S[...i-1] 이다. 하지만, S[i...]의 패턴을 초과하는 인덱스의
				//문자열은 k개의 문자를 붙여 또 패턴을 만들 수 있기 때문에 자투리 문자열을 체크해야 함
				int d = Z[i] % len_f;
				if (d > 0 && len_f - d > k) continue;
			}
			
			if (answer < len_f) answer = len_f;
		}
	}
}

int main() {
	cin >> n >> k >> s;

	//예외처리 : k >= n일 때
	if (k >= n) {
		printf("%d\n", n);
		return 0;
	}

	getZ();

	printf("%d\n", answer);

	return 0;
}
```
***
>KMP 알고리즘 풀이
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;
int n, k;
string s;
int Pi[100001];

void getPi() {
	int m = s.size(), j = 0;
	//i : 현재 보는 문자열 위치, j : prefix 다음의 index
	for (int i = 1; i < m; i++) {
		//불일치할 경우 Pi값을 통해 비교 단계 건너뜀
		while (j > 0 && s[i] != s[j]) j = Pi[j - 1];
		//prefix, suffix 같은 부분 발견 시
		if (s[i] == s[j]) Pi[i] = ++j;
	}
}

int main() {
	int answer = 0;
	cin >> n >> k >> s;

	if (k >= n) {
		printf("%d\n", n);
		return 0;
	}

	getPi();

	int cur = n - 1;
	while (1) {
		int plen = n - Pi[cur];	//최소 패턴 길이
		int pat_cnt = (n + k) / plen;	//패턴 최대 등장 횟수
		if (pat_cnt >= 2 && plen * pat_cnt >= n) answer = plen > answer ? plen : answer;
		if (Pi[cur] <= cur + 1 - Pi[cur]) break;
		cur = Pi[cur] - 1;
	}

	printf("%d\n", answer);


	return 0;
}
```
***
# 문자열 뽑기
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>

using namespace std;

int tc;
map<string, bool> dict;

bool dfs(string str) {
	int n = str.size();
	bool result = false;
	std::map<string, bool>::iterator it = dict.find(str);
	if (it != dict.end()) {
		//이미 str에 대한 가능, 불가능 여부가 있는 경우
		//cout << "dict 참조 : " << str << '\n';
		return it->second;
	}

	int cnt = 1;
	char before = 'x';
	for (int i = 0; i < n; i++) {
		if (str[i] == before) cnt++;
		else {
			if (i > 0 && cnt > 1) {
				//뽑아낼 수 있는 그룹인 경우 그 그룹을 제외한 부분문자열 생성
				int left = i - cnt;
				if (left < 0) left = 0;
				string temp = str.substr(0, left) + str.substr(i);
				//그 부분문자열에 대해 재귀탐색함. 만약 성공한다면 빈 문자열로 변환 가능한 것임.
				if (dfs(temp)) { result = true; break; }
				cnt = 1;
			}
		}
		before = str[i];
		if(cnt > 1 && cnt == n) { result = true; break; }
		if (i == n - 1 && cnt > 1) {
			string temp = str.substr(0, n - cnt);
			if (dfs(temp)) result = true;
		}
	}
	//str 문자열에 대한 가능/불가능 여부를 저장
	dict.insert({ str, result });
	return result;
}

int main() {
	cin >> tc;

	dict.insert({ "", true });
	dict.insert({ "a", false });
	dict.insert({ "b", false });

	for (int i = 0; i < tc; i++) {
		string s;
		cin >> s;
		bool res = dfs(s);
		printf("%d\n", res);
	}

	return 0;
}
```
Top-Down의 재귀호출 DP를 활용해 문제 해결
***


# Cube Editor
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <memory.h>

using namespace std;
int answer = 0;
int Pi[5000];

void getPi(string s) {
	int m = s.size(), j = 0;
	//i : 현재 보는 문자열 위치, j : prefix 다음의 index
	for (int i = 1; i < m; i++) {
		//불일치할 경우 Pi값을 통해 비교 단계 건너뜀
		while (j > 0 && s[i] != s[j]) j = Pi[j - 1];
		//prefix, suffix 같은 부분 발견 시
		if (s[i] == s[j]) Pi[i] = ++j;
		if (Pi[i] > answer) answer = Pi[i];
	}
}

int main() {
	string str;
	cin >> str;

	for (int i = 0; i < str.size(); i++) {
		memset(Pi, 0, sizeof(Pi));
		string temp = str.substr(i);
		getPi(temp);
	}

	printf("%d\n", answer);

	return 0;
}

```
***

# 전화번호 목록
>Trie 풀이
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
const int child_size = 10;
bool error = true;
string answer[2] = { "NO", "YES" };

class Tri {
private:
	Tri* child[child_size];

public:
	Tri() {
		//생성자
		for (int i = 0; i < child_size; i++) child[i] = NULL;
	}

	~Tri() {
		//소멸자
		for (int i = 0; i < child_size; i++)
			if (child[i] != NULL) delete child[i];
	}

	void insert(int len, int idx, string words) {
		//삽입
		if (idx == len) return;
		int next = words[idx] - '0';
		if (child[next] == NULL) child[next] = new Tri();
		else {
			if (idx == len - 1) { error = false; return; }
		}
		child[next]->insert(len, idx + 1, words);
	}

	bool geterr() { return error; };
};

int main() {
	int tc, n;
	vector<string> inputs;

	cin >> tc;
	for (int i = 0; i < tc; i++) {
		Tri tri;
		error = true;
		inputs.clear();
		inputs.push_back("");

		cin >> n;
		for (int j = 0; j < n; j++) {
			string input;
			cin >> input;
			inputs.push_back(input);
		}
		sort(inputs.begin(), inputs.end());
		for (int j = 1; j < inputs.size(); j++) {
			int len, len1 = inputs[j - 1].size(), len2 = inputs[j].size();
			if (j == 1 || len1 > len2) len = len2; else len = len1;

			tri.insert(len, 0, inputs[j]);
			if (!error) break;
		}
		if (error) error = 1;
		cout << answer[error] << '\n';
		//tri.~Tri();
	}

	return 0;
}

```
핵심 : 문자열들을 정렬하면, 인접한 문자열 하나에 대해서만 비교하면 됨   
Trie에 한 글자씩 삽입해가며 앞 인덱스 문자열의 길이만큼 Trie에 이미 존재하면 실패
***
>단순비교 풀이
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
string answer[2] = { "NO", "YES" };

bool compare(string s1, string s2, int len) {
	for (int i = 0; i < len; i++) {
		if (s1[i] != s2[i]) return 1;
	}
	return 0;
}

int main(){
	bool result = 1;
	int tc, n;
	vector<string> inputs;

	cin >> tc;

	for (int i = 0; i < tc; i++) {
		cin >> n;
		inputs.clear();
		result = 1;
		for (int j = 0; j < n; j++) {
			string input;
			cin >> input;
			inputs.push_back(input);
		}

		sort(inputs.begin(), inputs.end());

		for (int j = 0; j < inputs.size() - 1; j++) {
			//inputs를 정렬했을 때, 한 문자열에 대해 그 바로 아래의 문자열은 두 가지 경우가 존재한다.
			//1. 자신의 위 문자와 특정 인덱스의 숫자가 더 큰 경우 (정렬 상 우위)
			//			(이 경우, 위 문자열과 길이가 같거나 짧을 수도 있음)
			//2. 자신의 위 문자를 포함하고 길이가 더 긴 경우
			//따라서, 한 문자열에 대해 그 다음 문자열의 길이를 비교해 포함 여부를 확인하면 된다.
			int len1 = inputs[j].size();
			int len2 = inputs[j + 1].size();
			if (len1 < len2) result = compare(inputs[j], inputs[j + 1], len1);
			if (!result) break;
		}
		cout << answer[result] << '\n';
	}

	return 0;
}

```
