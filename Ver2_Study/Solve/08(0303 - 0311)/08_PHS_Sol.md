# 벽 부수고 이동하기 2
문제에서 핵심은 벽을 부수는 경우 최단경로가 달라질 수 있다는 점입니다.

따라서 벽을 부순 횟수에 따라 방문했던 칸을 다시 방문할 수 있으므로 다음과 같이 풀 수 있습니다.

처음 방문 : 현재 벽을 부순 횟수 k를 기록합니다.
n번째 방문 : 기록된 k 횟수보다 큰 경우 이전 방문에서 최단경로를 찾을 수 있기 때문에 넘어가고 k보다 작은 경우 최단경로가 달라질 수 있으므로 기록하고 bfs 탐색을 합니다.
 
기존 bfs와 다르게 visited 배열을 int로 선언하고 depth를 따로 노드마다 적용하지 않고 bfs 특성을 이용해 한 번의 큐 전체 루프가 끝나면 depth를 증가시킵니다.
```c++
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef struct node {
    int x, y, k;
    node(int x, int y, int k) :x(x), y(y), k(k) {};
 
}node;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    char ary[1002][1003] = { 0 };
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> (ary[i] + 1);
 
 
    int visited[1001][1001];
    memset(visited, 0x7f, sizeof visited);
    visited[1][1] = 0;
 
    int dx[] = { 0, 1, 0, -1 },
        dy[] = { 1, 0, -1, 0 }, depth = 1;
    queue<node> que;
    que.emplace(1, 1, 0);
 
    while (!que.empty()) {
 
        int cur_size = que.size();
        while (cur_size--) {
            auto cur = que.front();
            que.pop();
 
            if (cur.x == n && cur.y == m) {
                cout << depth;
                return 0;
            }
            for (int d = 0; d < 4; d++) {
                int nx = cur.x + dx[d], ny = cur.y + dy[d];
                if (!ary[nx][ny]) continue;
                if (cur.k < visited[nx][ny]) {
                    if (ary[nx][ny] != '1') {
                        visited[nx][ny] = cur.k;
                        que.emplace(nx, ny, cur.k);
                    }
                    else if (cur.k < k) {
                        visited[nx][ny] = cur.k + 1;
                        que.emplace(nx, ny, cur.k + 1);
                    }
                }
            }
        }
 
        depth++;
    }
    cout << -1;
}

}
```
***
# 욕심쟁이 판다
판다는 전 지역보다 옮긴 지역이 더 많은 대나무가 있어야 하므로 다음식을 항상 만족합니다.

ary[ path[i][x] ][ path[i][y] ] < ary[ path[i + 1][x] ][ path[i + 1][y] ]

따라서 dfs 탐색 도중 왔던 길을 다시 갈 수 없기 때문에 visited를 사용하지 않아도 됩니다. 

dp[x][y] : 현재 위치에서 갈 수 있는 최대 depth로 두고 문제를 풉니다.

배열 범위를 나가지 않는 선에서 다음 식을 통해 dp를 완성할 수 있습니다.
```c++
#include <iostream>
#include <algorithm>
using namespace std;
int n, ary[500][500], dp[500][500];
int dx[] = { 0, 0, 1, -1 },
dy[] = { 1, -1, 0, 0 };
 
int dfs(int x, int y) {
    int &cur = dp[x][y];
    if (cur) return cur;
 
    for (int d = 0; d < 4; d++) {
        if (x + dx[d] < 0 || n <= x + dx[d] || y + dy[d] < 0 || n <= y + dy[d]) continue;
        if (ary[x][y] < ary[x + dx[d]][y + dy[d]])
            cur = max(cur, dfs(x + dx[d], y + dy[d]));
    }
    return ++cur;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> ary[i][j];
    int mx = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!dp[i][j])
                mx = max(mx, dfs(i, j));
    cout << mx;
}
}
```
***
# 좋다
2개의 수를 잡아서 어떠한 수를 만들 수 있는지 확인하는 방식은  O(N^2), 하나의 수를 잡고 이 수를 만들 수 있는지 확인하는 방식 또한 O(N^2)지만 전자의 경우 그 수가 배열 안에 있는지 확인해야 하는 작업이 필요하므로 더 많은 시간이 필요합니다.

 

투 포인터 알고리즘을 사용하기 위해 먼저 정렬을 합니다.

그 후 두 포인터를 0, n-1에 두고 현재 확인할 수를 i : 0~n-1로 둡니다. 두 포인터의 값을 더한 수가 현재 수와의 대소 비교를 경우의 수로 둡니다. 정렬을 하였기 때문에 right--는 합이 줄어들게 되고 left++은 합이 늘어나게 됩니다.

left + right < ary[i] : 정렬을 해 두었기 때문에 left++ 해 줍니다.
left + right > ary[i] : right--
left + right == ary[i] : 두 수를 더해 다른 수를 만들어야 하므로 예외처리를 해 주고 결과를 반영합니다.
```c++
#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int main() {
    int ary[2000];
    int n, res = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &ary[i]);
 
    sort(ary, ary + n);
    for (int i = 0; i < n; i++) {
        int left = 0, right = n - 1;
        while (left < right) {
            if (ary[i] > ary[left] + ary[right]) left++;
            else if (ary[i] < ary[left] + ary[right])right--;
            else {
                if (left == i) left++;
                else if (right == i) right--;
                else {
                    ++res;
                    break;
                }
            }
        }
    }
    printf("%d", res);
}

}
```
***
# 수상 택시
출발지가 목적지보다 왼쪽, 낮은 수인 경우 M으로 가는 도중 처리할 수 있으므로 배열에 넣지 않습니다.

배열에는 목적지가 출발지보다 왼쪽에 있는 경우만 선택해서 담아 이를 목적지 기준으로 정렬합니다.

 

경로를 합칠 때 돌아갔다가 오는 길이를 줄이기 위해서는 서로 겹치는 부분이 있는 경우만 합쳐서 새 경로를 만들어 줍니다. 예를 들어 다음과 같은 경우 경로를 합치는 것이 좋습니다.

(10 2), (13 9)

경로를 합친 경우 : M + (13 - 2) * 2 = M + 22
따로 처리를 한 경우 : M + (10 - 2) * 2 + (13 - 9) * 2 = 16 + 8 = 24
 

만약 경로가 서로 이어지지 않는다면 불필요한 왕복이 생기므로 경로를 합치지 않는 것이 좋습니다.

(10 2), (13 11)

경로를 합친 경우 : M + (13 - 2) * 2 = M + 22
따로 처리를 한 경우 : M + (10 - 2) * 2 + (13 - 11) * 2 = 16 + 4 = 20
 

스위핑을 통해서 선형 시간에 최솟값을 찾을 수 있으며 left, right 변수를 두고 최소의 목적지, 최대의 출발지를 기록해두며 경로가 겹쳐 있는지 판단합니다.
```c++
#include <iostream>
#include <algorithm>
using namespace std;
typedef struct pir {
    int cur, dest;
};
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    pir ary[300000];
    cin >> n >> m;
 
    for (int i = 0; i < n;) {
        cin >> ary[i].cur >> ary[i].dest;
        if (ary[i].cur > ary[i].dest)i++;
        else n--;
    }
 
    sort(ary, ary + n, [](const pir &a, const pir& b)->bool {
        return a.dest < b.dest;
    });
 
    long long res = 0;
    int left = ary[0].dest, right = ary[0].cur;
    for (int i = 1; i < n; i++) {
        if (ary[i].dest < right) {
            right = right < ary[i].cur ? ary[i].cur : right;
        }
        else {
            res += right - left;
            left = ary[i].dest, right = ary[i].cur;
        }
    }
    res += right - left;
    cout << (res<<1) + m;
}
}
```
***
