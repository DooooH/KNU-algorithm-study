# 원판 돌리기

기준점을 기록하는 배열 사용, 인접한 수 검사할때 그래프 탐색 대신 전체 담색 사용

평균값은 처음 구해두고 수가 삭제될때 마다 갱신

```c++
#include<cstdio>
#define clockwise(idx, m) idx < m ? idx+1 : 1
#define counterwise(idx, m) idx > 1 ? idx-1 : m
#define find_idx(bnck, j) (bnck + j < m ? bnck + j : bnck + j - m) + 1
int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);
 
    int ary[51][51], bnchmark[51] = { 0 };
    int total = 0, cnt = m * n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &ary[i][j]);
            total += ary[i][j];
        }
 
    bool visited[51][51] = { 0 };
 
    while (t--) {
        int x, d, k;
        scanf("%d %d %d", &x, &d, &k);
        for (int i = x; i <= n; i += x) {
            if (d)//반시계
                bnchmark[i] = (bnchmark[i] + k) % m;
            else//시계
                bnchmark[i] = (bnchmark[i] + m - k) % m;
        }
 
        bool flag = 0;//수를 지워야 하는 경우의 수가 있음
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < m; ++j) {
                int idx = find_idx(bnchmark[i], j);
                if (ary[i][idx] && (ary[i][idx] == ary[i][clockwise(idx, m)] //시계방향 인접한 수
                    || ary[i][idx] == ary[i][counterwise(idx, m)] ||//반시계방향
                    (i > 1 && ary[i][idx] == ary[i - 1][find_idx(bnchmark[i - 1], j)]) ||//큰 원판 인접한 수
                    (i < n && ary[i][idx] == ary[i + 1][find_idx(bnchmark[i + 1], j)]))) {//작은 원판
 
                    visited[i][idx] = 1;//지워야 할 수 체크
                    flag = 1;
                }
 
            }
 
        if (flag) //지울 수가 있음
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= m; ++j) {
                    if (visited[i][j]) {
                        total -= ary[i][j];//수를 지우면 total, cnt 반영
                        cnt--;
                        ary[i][j] = 0;
                        visited[i][j] = 0;
                    }
                }
 
        else {//지운 수가 없음
            if (cnt == 0)    break;//더이상 수가 없으면 빠르게 종료
            double avg = (double)total / cnt;//평균
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= m; ++j) {
                    if (!ary[i][j])    continue;
                    if (ary[i][j] < avg) {//평균이하
                        ary[i][j]++;
                        total++;
                    }
                    else if(ary[i][j]!=avg){//이상
                        ary[i][j]--;
                        total--;
                    }
                }
        }
    }
    printf("%d", total);
}

```
***
# ZOAC

구간 처리

```c++
#include <cstdio>
#include <cstring>
 
int main() {
    char ary[101];
    int visited[100] = { 0 };
 
    scanf("%s", ary);
    int n = strlen(ary);
 
    for (int i = 0; i < n; i++) {
        int j = n - 1;
        while (visited[j])--j;//여러 구간 중 뒤의 구간부터 탐색
 
        int mn = j--;//최솟값 찾기
 
        while (j >= 0 && !visited[j]) {
            mn = ary[mn] >= ary[j] ? j : mn;//등호를 통해 예외 처리
            --j;
        }
        visited[mn] = 1;//최솟값 선택
 
        for (int j = 0; j < n; j++)//방문한 문자 출력
            if (visited[j])
                putc(ary[j], stdout);
        putc('\n', stdout);
    }
 
}

```
***
# 어른 상어

주어진 조건대로 풀면 쉽게 풀 수 있는 문제입니다.
 
일일이 모든 냄새의 수명을 -1씩 하면 느리므로 냄새를 뿌리면 해당 냄새의 수명을 depth + k로 기록하여 depth가 이를 넘을 경우 접근할 수 있도록 합니다.

상어를 1부터 m까지 오름차순으로 이동하여 겹치는 상어는 그 순간 내보낼 수 있도록 합니다.

주의해야 할 점은 냄새와 상어의 위치를 구분지어야 같은 칸에 상어가 들어갈 수 있는 여지가 생기므로 따로 변수를 두어 관리합니다.
```c++
#include <cstdio>
#include <cstring>
 
typedef struct shark {
    int x, y, d;
    int priority[4][4];
}shark;
typedef struct node {
    int num, sk, cnt;
};
int main() {
    int n, m, k;
    shark sk[401];
    node map[20][20];
    
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j].num);
            if (map[i][j].num) {
                map[i][j].sk = map[i][j].num;
                map[i][j].cnt = k;
                sk[map[i][j].num] = { i, j };
            }
                
        }
    
 
    for (int i = 1; i <= m; i++)
        scanf("%d", &sk[i].d), sk[i].d--;
 
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++) {
                scanf("%d", &sk[i].priority[j][k]);
                --sk[i].priority[j][k];
            }
                
    int dx[4] = { -1,1,0,0 },
        dy[4] = { 0,0,-1,1 };
    int depth = 0, cnt = m - 1;
    while (depth < 1000) {
        depth++;
 
        for (int i = 1; i <= m; i++) {
            if (sk[i].x == -1) continue;
 
            map[sk[i].x][sk[i].y].num = 0;
            bool t = true;
 
            for (int d = 0; t && d < 4; d++) {//빈칸
                int nd = sk[i].priority[sk[i].d][d];
                int nx = sk[i].x + dx[nd], ny = sk[i].y + dy[nd];
                if (nx < 0 || ny < 0 || nx == n || ny == n || map[nx][ny].cnt >= depth) continue;
 
                t = false;
                if (map[nx][ny].num) {//오름차순으로 검색하므로 겹치면 내보냄
                    sk[i].x = -1;
                    cnt--;
                }
                else {
                    sk[i].x = nx;
                    sk[i].y = ny;
                    sk[i].d = nd;
                    map[nx][ny].num = i;
                    map[nx][ny].sk = i;
                }
 
            }
            if (t) {//냄새
                for (int d = 0; d < 4; d++) {
                    int nd = sk[i].priority[sk[i].d][d];
                    int nx = sk[i].x + dx[nd], ny = sk[i].y + dy[nd];
                    if (nx < 0 || ny < 0 || nx == n || ny == n || map[nx][ny].sk != i) continue;
                    sk[i].x = nx;
                    sk[i].y = ny;
                    sk[i].d = nd;
                    break;
                }
            }
        }
        for (int i = 1; i <= m; i++) {//냄새 뿌림
            if (sk[i].x == -1) continue;
            map[sk[i].x][sk[i].y].cnt = depth + k;
        }
 
        if (!cnt) {
            printf("%d", depth);
            return 0;
        }
    }
 
    printf("-1");
 
}

```
***
# 길찾기 게임

포인터를 활용하는 것보다 인덱싱을 사용하는 것이 더 빠르므로 이를 사용합니다.

가로의 값 y는 중복될 수 없으므로 이를 이용하여 삽입할 노드의 y값이 현재 노드 y값보다 작으면 왼쪽, 크면 오른쪽 자식 노드로 넘기며 선택 위치가 빈칸인 경우 해당 위치에 삽입합니다.

프리오더, 포스트 오더를 한번에 재귀를 사용하지 않고 구현하기 어려우므로 간단하게 재귀 함수를 이용해 순회합니다.
```c++
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
 
typedef struct node{
    int x, y, idx;
    int left, right;//포인터 대신 인덱싱
}node;
node ary[10001];
 
void travl(vector<vector<int>> &ans, int cur) {
    ans[0].push_back(ary[cur].idx);//프리오더
 
    if (ary[cur].left)
        travl(ans, ary[cur].left);
    if (ary[cur].right)
        travl(ans, ary[cur].right);
    ans[1].push_back(ary[cur].idx);//포스트 오더
}
 
 
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2);
    int n = nodeinfo.size();
 
    
 
    for (int i = 0; i < n; i++) {
        ary[i + 1] = { nodeinfo[i][1], nodeinfo[i][0], i + 1 };//x : 세로, y : 가로
    }
    sort(ary + 1, ary + n + 1, [](const node& a, const node& b)->bool {
        if (a.x != b.x) return a.x > b.x;
        return a.y < b.y;
    });
 
    int root = 1;
 
    for (int i = 2; i <= n; i++) {//트리 생성
        int prnt = root, chld = i;
        while (1) {
            if (ary[chld].y < ary[prnt].y) {//왼쪽
                if (ary[prnt].left)
                    prnt = ary[prnt].left;
                else {
                    ary[prnt].left = chld;
                    break;
                }
            }
            else {//오른쪽
                if (ary[prnt].right)
                    prnt = ary[prnt].right;
                else {
                    ary[prnt].right = chld;
                    break;
                }
            }
        }
    }
    travl(answer, 1);
        
    return answer;
}
 
int main() {
    vector < vector<int>> t = { {5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2} };
    solution(t);
 
}
```
***
