# 원판 돌리기

구현문제.

원판을 객체로 구현해 탐색에 용이하도록 구현

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;
typedef pair<int, int> p;

int n, m, t;
bool eliminated_flag = false;

class disk {
private:
	deque<int> dque;
	disk* upper;	//한 단계 높은 디스크
	disk* lower;		//한 단계 낮은 디스크
	int valid = 0;	//유효 숫자의 수
	

public:
	void init_dque(int* list) {
		for (int i = 0; i < m; i++) dque.push_back(*(list + i));
		valid = m;
	}

	void set_upper(disk* up) { upper = up; }
	void set_lower(disk* low) { lower = low; }

	void rotate(int dir, int amount) {
		if (dir) {
			//반시계 방향
			for (int i = 0; i < amount; i++) {
				int temp = dque.front();
				dque.pop_front();
				dque.push_back(temp);
			}
		}
		else {
			//시계 방향
			for (int i = 0; i < amount; i++) {
				int temp = dque.back();
				dque.pop_back();
				dque.push_front(temp);
			}
		}
	}

	int get_val(int pos) { return dque[pos]; }

	int get_sum() {
		int ret = 0;
		for (int i = 0; i < m; i++) ret += dque[i];
		return ret;
	}

	int get_valid() { return valid; }

	void eliminate(int pos, bool adj) {
		//현재 원판의 pos번째 수와 인접한 같은 모든 수를 제거한다. (DFS)
		bool adj_exist = adj;
		if (dque[pos] == 0) return;

		int temp = dque[pos];
		dque[pos] = 0;

		int next = pos == m - 1 ? 0 : pos + 1;
		int prev = pos == 0 ? m - 1 : pos - 1;

		//동일 원판 양 옆에서 인접 제거
		if (temp == dque[next]) { adj_exist = true; eliminate(next, true); }
		if (temp == dque[prev]) { adj_exist = true; eliminate(prev, true); }

		//위, 아래 원판에서 인접 제거
		if (upper != NULL && temp == upper->get_val(pos))
		{ adj_exist = true; upper->eliminate(pos, true); }

		if (lower != NULL && temp == lower->get_val(pos))
		{ adj_exist = true; lower->eliminate(pos, true); }

		if (adj_exist) { valid -= 1; eliminated_flag = true; }
		else dque[pos] = temp;
	}

	void modify_dque(double avgval) {
		for (int i = 0; i < m; i++) {
			if (dque[i] == 0) continue;
			if ((double)dque[i] > avgval) dque[i] -= 1;
			else if ((double)dque[i] < avgval) dque[i] += 1;
		}
	}
};

disk disks[51];

void eliminate_val() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			disks[i].eliminate(j, false);
		}
	}
}

double average() {
	int valid_cnt = 0, val_sum = 0;
	for (int i = 1; i <= n; i++) {
		valid_cnt += disks[i].get_valid();
		val_sum += disks[i].get_sum();
	}
	return (double)val_sum / valid_cnt;
}

void init() {
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		int val_arr[51];

		for (int i = 0; i < m; i++) cin >> val_arr[i];
		disks[i].init_dque(val_arr);

		if (i > 1) disks[i].set_lower(&disks[i - 1]);
		if (i < n) disks[i].set_upper(&disks[i + 1]);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	int x, d, k;
	init();
	for (int i = 0; i < t; i++) {
		cin >> x >> d >> k;

		for (int j = x; j <= n; j += x) {
			//x의 배수 번호인 원판에 대해, 회전 수행
			disks[j].rotate(d, k);
		}

		//원판 내에 존재하는 인접 수들을 모두 제거
		eliminated_flag = false;
		eliminate_val();

		if (!eliminated_flag) {
			double avgval = average();
			for (int i = 1; i <= n; i++) disks[i].modify_dque(avgval);
		}
	}

	int answer = 0;
	for (int i = 1; i <= n; i++) answer += disks[i].get_sum();
	printf("%d\n", answer);

	return 0;
}
```

# 어른 상어

구현문제.

상어를 객체로 구현. 이동 순서를 번호 내림차순으로 해 겹치기 예외처리를 하지 않아도 됨.

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> p;
typedef pair<p, int> pp;

p dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int board[21][21], scent[21][21];
int n, m, k;
bool dead[401];

class shark {
private:
	int num;
	int curdir;
	int dir_priority[4][4];
	int row, col;

public:
	pp find_nextpos() {
		//현재 위치에서 다음으로 이동할 칸을 찾는다
		p secondary = { 0, 0 };
		int res_dir = -1;
		bool flag = false;

		//빈칸을 먼저 찾음
		for (int i = 0; i < 4; i++) {
			int nextdir = dir_priority[curdir][i];
			int newR = row + dir[nextdir].first, newC = col + dir[nextdir].second;

			if (newR < 1 || newR > n || newC < 1 || newC > n) continue;

			//냄새가 없는 칸을 발견
			//이전에 이동했던 상어가 이동한 후여도 그 결과를 반환
			//번호가 높은 상어는 이미 이동을 마쳤다는 가정이 있으므로, 덮어씌울 수 있다.
			if (scent[newR][newC] == 0 ) {
				if (board[newR][newC]) {
					//이미 상어가 있는 경우
					dead[board[newR][newC]] = true;
				}
				return { { newR, newC }, nextdir };
			}

			//자신의 냄새인 칸을 발견 시 보류
			if (board[newR][newC] == num) {
				if (!flag) {
					flag = true; 
					secondary = { newR, newC }; 
					res_dir = nextdir; 
				}
			}
		}

		//냄새가 없는 칸을 발견하지 못했을 경우, secondary 반환
		return { secondary, res_dir };
	}

	void move() {
		//다음 이동할 칸을 찾음
		pp res = find_nextpos();
		p nextpos = res.first;

		//위치 및 방향정보 갱신
		row = nextpos.first; col = nextpos.second;
		curdir = res.second;
		board[row][col] = num;
	}

	void left_scent() {
		//현재 칸에 냄새를 남김
		scent[row][col] = k;
		board[row][col] = num;
	}

	void set_num(int number) { num = number; }

	void set_pos(int r, int c) { row = r; col = c; }

	void set_curdir(int d) { curdir = d; }

	void set_dir_priority(int d, int* priority) {
		for (int i = 0; i < 4; i++) dir_priority[d][i] = *(priority + i);
	}
};

shark sharks[401];

int get_alive() {
	int ret = 0;
	for (int i = 1; i <= m; i++)
		if (!dead[i]) ret++;

	return ret;
}

void update_scent() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (scent[i][j]) {
				scent[i][j] -= 1;
				if (scent[i][j] == 0) board[i][j] = 0;
			}
		}

	for (int i = 1; i <= m; i++)
		if (!dead[i]) sharks[i].left_scent();
}

void sharks_move() {
	for (int i = m; i >= 1; i--)
		if(!dead[i]) sharks[i].move();
}

void init() {
	int dval;
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> board[i][j];
			if (board[i][j]) {
				scent[i][j] = k;
				sharks[board[i][j]].set_num(board[i][j]);
				sharks[board[i][j]].set_pos(i, j);
			}
		}

	for (int i = 1; i <= m; i++) {
		cin >> dval;
		sharks[i].set_curdir(dval - 1);
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < 4; j++) {
			int priority[4];

			for (int d = 0; d < 4; d++) {
				cin >> dval;
				priority[d] = dval - 1;
			}

			sharks[i].set_dir_priority(j, priority);
		}
	}
}

void print() {
	printf("[board]\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			printf("%d ", board[i][j]);
		printf("\n");
	}

	printf("[scent]\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			printf("%d ", scent[i][j]);
		printf("\n");
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	int answer = 0;
	init();
	//print();
	while (get_alive() > 1) {
		if (answer > 1000) break;
		//printf("------------------\nTime : %d\n", answer + 1);
		sharks_move();
		update_scent();
		//print();
		answer++;
	}

	if (answer > 1000) answer = -1;
	printf("%d\n", answer);

	return 0;
}
```

# ZOAC

그냥 substr로 완탐 조져버리기

시간복잡도는 O(N^2logN) 이긴 한데 substr 까지 고려하면 O(N^3log)이 될수도 있음

N : 문자열 길이

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
typedef pair<int, int> p;

int len;
string s;
vector<int> pos;
vector<p> chars;
bool turnon[100];

void recursive(string base) {
	if (base.size() == len) return;

	string print = "Z" + base;
	int minpos = len + 1;
	for (int i = 0; i < len; i++) {
		if (turnon[i]) continue;
		int idx = lower_bound(pos.begin(), pos.end(), i) - pos.begin();
		string temp;
		if (idx == 0) temp = s[i] + base;
		else if (idx == base.size()) temp = base + s[i];
		else temp = base.substr(0, idx) + s[i] + base.substr(idx);
		
		if (temp < print) {
			print = temp;
			minpos = i;
		}
	}

	turnon[minpos] = true;
	pos.push_back(minpos);
	sort(pos.begin(), pos.end());
	cout << print << '\n';
	recursive(print);
}

void init() {
	cin >> s;

	len = s.size();
	for (int i = 0; i < s.size(); i++) {
		chars.push_back({ s[i], i });
	}

	sort(chars.begin(), chars.end());
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	init();
	string start = "" + chars[0].first;
	recursive(start);

	return 0;
}
```

# 길 찾기 게임

자바로 풀기

트리 구성 후 순회하는 문제

```java
import java.util.*;

class Node implements Comparable<Node>{
    public int num;
    public int x, y;
    public Node left = null, right = null;
    
    public Node(int n, int x, int y) { 
        this.num = n;
        this.x = x; 
        this.y = y; 
    }
    
    @Override
    public int compareTo(Node node){
        if(this.y == node.y){
            if(this.x > node.x) return 1;
            return -1;
        }
        if(this.y < node.y) return 1;
        return -1;
    }
}

class Solution {
    public int numberOfNode = 0, ord = 0;
    ArrayList<Node> nlist = new ArrayList<>();
    public int[][] answer;
    
    public void set_tree(Node node, Node parent){
        //System.out.println("node is " + node.num + ", parent is " + parent.num);
        if(node.x < parent.x){
            if(parent.left == null) parent.left = node;
            else set_tree(node, parent.left);
        }
        
        else{
            if(parent.right == null) parent.right = node;
            else set_tree(node, parent.right);    
        }
    }
    
    public void preorder(Node cur){
        answer[0][ord++] = cur.num;
        if(cur.left != null) preorder(cur.left);
        if(cur.right != null) preorder(cur.right);
    }
    
    public void postorder(Node cur){
        if(cur.left != null) postorder(cur.left);
        if(cur.right != null) postorder(cur.right);
        answer[1][ord++] = cur.num;
    }
    
    public int[][] solution(int[][] nodeinfo) {
        numberOfNode = nodeinfo.length;
        answer = new int[2][numberOfNode];

        int idx = 1;
        for(int[] node : nodeinfo){
            Node newNode = new Node(idx, node[0], node[1]);
            nlist.add(newNode);
            idx++;
        }
        
        //Collections.sort(nlist, new NodeComparator());
        Collections.sort(nlist);
        //for(Node n : nlist) System.out.println(n.x + ", " + n.y);
        
        Node root = nlist.get(0);
        for(int i = 1; i < numberOfNode; i++) set_tree(nlist.get(i), root);
        
        preorder(root);
        ord = 0;
        postorder(root);
        
        //for(int i : answer[0]) System.out.print(i + " ");
        //for(int i : answer[1]) System.out.print(i + " ");
        
        return answer;
    }
}
```