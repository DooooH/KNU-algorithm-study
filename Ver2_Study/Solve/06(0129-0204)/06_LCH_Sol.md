# 개미굴

트라이 또는 트리구조

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory.h>

using namespace std;
typedef pair<int, int> p;

class space {
private:
	string name;
	int level = 0;
	vector<space> childs;
public:
	void connect(vector<string> input, int idx);
	void print_childs();
	string get_name();

	space(string nm, int lv) {
		this->name = nm;
		this->level = lv;
	}
};

int n, k;

bool cmp(space a, space b) {
	return a.get_name() < b.get_name();
}

string space::get_name() {
	return name;
}

void space::connect(vector<string> input, int idx) {
	if (idx == input.size()) return;
	for (int i = 0; i < childs.size(); i++) {
		if (input[idx] == childs[i].name) {
			//input의 idx에 해당하는 문자열이 이미 자식으로 존재한다면
			childs[i].connect(input, idx + 1);
			return;
		}
	}
	space c = space(input[idx], level + 1);
	c.connect(input, idx + 1);
	childs.push_back(c);
}

void space::print_childs() {
	//현재 객체의 자식들을 사전순 정렬
	sort(childs.begin(), childs.end(), cmp);
	//출력
	if (level > 0) {
		for (int i = 0; i < level - 1; i++) cout << "--";
		cout << name << '\n';
	}

	for (int i = 0; i < childs.size(); i++) {
		//자식들마다 재귀
		childs[i].print_childs();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	space root = space("root", 0);
	string input;
	vector<string> input_seq;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> k;
		input_seq.clear();
		for (int j = 0; j < k; j++) {
			cin >> input;
			input_seq.push_back(input);
		}
		root.connect(input_seq, 0);
	}

	root.print_childs();

	//system("PAUSE");
	return 0;
}
```
***

# 개구리 공주

연결리스트

처음 노드들이 대각선으로 연결되는지 판별하는 아이디어가 핵심

x + y값이 같으면 B-C, x - y값이 같으면 A-D

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef pair<int, int> p;

typedef struct node{
	int x, y;
	node* conn[4];		//0123 : abcd
}node;
typedef struct node* link;

int n, k;
string path;
node* frog;
vector<node> list;
vector<int> sorted_idx;

void jump_action(int dir) {
	if (frog->conn[dir] == NULL) return;
	for(int i = 0; i < 4; i++)
		if (frog->conn[i]) frog->conn[i]->conn[3 - i] = frog->conn[3 - i];
	
	frog = frog->conn[dir];
}

void get_answer() {
	int jump = 0;
	while (jump < path.size()) {
		int action = path[jump] - 'A';
		jump_action(action);
		jump++;
	}

	printf("%d %d\n", frog->x, frog->y);
}

node create_node(int x, int y) {
	node temp;
	temp.x = x; temp.y = y;
	for (int i = 0; i < 4; i++) temp.conn[i] = NULL;
	return temp;
}

bool cmp_down(int ai, int bi) {
	node a = list[ai], b = list[bi];
	int a_val = a.x + a.y;
	int b_val = b.x + b.y;
	if (a_val == b_val) return a.x < b.x;
	return a_val < b_val;
}

bool cmp_up(int ai, int bi) {
	node a = list[ai], b = list[bi];
	int a_val = a.x - a.y;
	int b_val = b.x - b.y;
	if (a_val == b_val) return a.x < b.x;
	return a_val < b_val;
}

void set_uplink() {
	sort(sorted_idx.begin(), sorted_idx.end(), cmp_up);

	for (int i = 1; i < n; i++) {
		link cur = &list[sorted_idx[i]];
		link prev = &list[sorted_idx[i - 1]];
		if (cur->x - cur->y == prev->x - prev->y) {
			cur->conn[3] = prev;
			prev->conn[0] = cur;
		}
	}
}

void set_downlink() {
	sort(sorted_idx.begin(), sorted_idx.end(), cmp_down);

	for (int i = 1; i < n; i++) {
		link cur = &list[sorted_idx[i]];
		link prev = &list[sorted_idx[i - 1]];
		if (cur->x + cur->y == prev->x + prev->y) {
			cur->conn[2] = prev;
			prev->conn[1] = cur;
		}
	}
}

void init() {
	int x, y, sx, sy;
	cin >> n >> k;
	cin >> path;

	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		list.push_back(create_node(x, y));
		sorted_idx.push_back(i);
		if (i == 0) { sx = x; sy = y; }
	}
	frog = &list[0];

	set_uplink();
	set_downlink();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	get_answer();

	return 0;
}
```
***
# 직사각형

Swippnig + Segment Tree + 좌표압축

시간복잡도가 O(NlonN)이므로 lazy까지 사용하지는 않아도 됨.

https://www.acmicpc.net/problem/3392 화성지도와 같은 유형에 좌표 압축만 추가됨.

각 직사각형의 세로변만을 모은 후 정렬해 세그먼트 트리로 해당하는 범위를 세줌

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

#define MAXSIZE 400001

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

typedef struct vert {
	int x;
	p y;
	bool start;
}vert;

int n;
ll segtree[MAXSIZE * 4];
ll cnt[MAXSIZE * 4];
vector<vert> verts;
vector<int> ylist;

void update_range(int node, int start, int end, int l, int r, int val) {
	if (l > end || r < start) return;		//범위를 벗어난 경우

	if (l <= start && end <= r) {
		//완전히 포함되는 경우
		cnt[node] += val;
	}
	else {
		//범위가 걸치는 경우
		int mid = (start + end) / 2;
		update_range(node * 2, start, mid, l, r, val);
		update_range(node * 2 + 1, mid + 1, end, l, r, val);
	}

	if (cnt[node]) {
		segtree[node] = (ll)ylist[end] - ylist[start - 1];
	}
	else {
		if (start == end) segtree[node] = 0;
		else segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
	}
}

ll get_answer() {
	ll ret = 0;
	int diff_x = 0, diff_y;
	for (int i = 0; i < verts.size(); i++) {
		if (i > 0) {
			diff_x = verts[i].x - verts[i - 1].x;
			//diff_y = verts[i].y.second - verts[i].y.first;
			ret += segtree[1] * diff_x;
		}
		int val = verts[i].start == true ? 1 : -1;
		int y1_idx = lower_bound(ylist.begin(), ylist.end(), verts[i].y.first) - ylist.begin();
		int y2_idx = lower_bound(ylist.begin(), ylist.end(), verts[i].y.second) - ylist.begin();
		update_range(1, 1, ylist.size(), y1_idx + 1, y2_idx, val);
	}

	return ret;
}

vert create_vert(int x, int y1, int y2, bool start) {
	vert temp;
	temp.x = x;
	temp.y.first = y1; temp.y.second = y2;
	temp.start = start;
	return temp;
}

bool cmp_vert(vert a, vert b) {
	return a.x < b.x;
}

void init() {
	int x1, x2, y1, y2;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x1 >> x2 >> y1 >> y2;
		verts.push_back(create_vert(x1, y1 + 1, y2 + 1, true));
		verts.push_back(create_vert(x2, y1 + 1, y2 + 1, false));
		ylist.push_back(y1 + 1);
		ylist.push_back(y2 + 1);
	}

	sort(ylist.begin(), ylist.end());
	ylist.erase(unique(ylist.begin(), ylist.end()), ylist.end());
	sort(verts.begin(), verts.end(), cmp_vert);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	ll answer = get_answer();
	printf("%lld\n", answer);

	return 0;
}
```
