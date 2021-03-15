# 탑
2가지 경우로 나눕니다.

전에 입력받은 탑의 크기가 현재 탑 보다 큰 경우 : 현재 탑이 발사한 레이저 신호를 수신한 탑은 i - 1이 됩니다.

현재 탑이 작은 경우 : i - 1부터 수신 가능한 탑을 찾아 내려갑니다.

i - 1 번째 탑이 발사한 레이저 신호를 어느 탑이 수신하였는가(dist[i-1])를 보고 수신한 탑이 현재 탑보다 큰 경우 해당 탑을 고르면 됩니다. 만약 해당 탑(dist[i-1]) 또한 현재 탑 보다 작은 경우 이러한 과정을 큰 탑이 나오거나 0에 도달할 때까지 반복합니다.
```c++
#include <iostream>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    int ary[500001], dist[500001];
 
    ary[0] = 0x7fffffff;
 
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> ary[i];
 
 
    for (int i = 2; i <= n; i++) {
        if (ary[i - 1] < ary[i]) {
            int t = i - 1;
            while (ary[t] < ary[i])
                t = dist[t];
            dist[i] = t;
        }
        else {
            dist[i] = i - 1;
        }
    }
 
    for (int i = 1; i <= n; i++)
        cout << dist[i] << ' ';
}
```
***
# 돌 게임 6
가지고 갈 수 있는 돌의 개수는 1, 3, 4개 이므로 현재 플레이어가 이길 수 있는 경우의 수는 현재 남은 돌에서 x 개를 가져가서 1, 3, 4를 만들 수 없는 수의 돌을 남기는 것입니다.

따라서 2, 7, 9, 14 .. 가 되며 이는 7로 나눈 나머지가 2, 0 인 경우입니다.
```c++
#include <cstdio>
 
int main() {
    long long n;
    scanf("%lld", &n);
    if (n % 7 == 0 || n % 7 == 2)
        printf("CY");
    else
        printf("SK");
}
```
***
# 미확인 도착지
방법은 2가지가 있으며 두 방법 모두 비슷한 결과로 나옵니다.

1번의 다익스트라 알고리즘을 수행하면서 g-h 간선을 지나는 경우를 체크하는 방법
start-g + g-h + h-dest 혹은 start-h + h-g + g-dest 가 start-dest와 값이 같은지 확인하는 방법, 3번의 다익스트라 알고리즘을 수행
결과가 비슷한 이유는 기존 다익스트라 알고리즘 계산 시 dist, graph 배열 2가지를 접근하지만 1번 방법의 경우 조건절이 추가되고 check 배열을 추가로 접근해야 하므로 메모리 접근 관점에서 느려질 수 있습니다.

 

2번 풀이는 다익스트라 알고리즘을 함수로 만들어 간단하게 풀 수 있으므로 1번 방법을 코드로 올리겠습니다.

1번 풀이 시 간선 g-h를 접근하는 경우와 다른 경로를 통해서 오는 경우가 같은 cost를 가질 경우 다익스트라 알고리즘 특성에 의해 문제가 생길 수 있으므로 간선들의 cost 값을 2배 해 주고 g-h 간선의 cost는 1을 빼 주어 예외처리를 할 수 있습니다.
```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
typedef struct edge {
    int dest, cost;
    bool operator<(const edge &t)const {
        return cost > t.cost;
    }
    edge(int d, int c) :dest(d), cost(c) {};
}edge;
 
void solve() {
    int n, m, t;
    cin >> n >> m >> t;
 
    int s, g, h;
    cin >> s >> g >> h;
 
    vector<edge> vtx[2001];
    int a, b, d;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> d;
        d <<= 1;//비용 2배
        vtx[a].emplace_back(b, d);
        vtx[b].emplace_back(a, d);
    }
    for (auto &t : vtx[g])
        if (t.dest == h) --t.cost;//g-h 간선 비용 --
    for (auto &t : vtx[h])
        if (t.dest == g) --t.cost;//h-g 간선 비용 --
 
 
    int cand[100];
    for (int i = 0; i < t; i++)
        cin >> cand[i];
    sort(cand, cand + t);
 
    priority_queue <edge, vector<edge>> que;
 
    bool check[2001] = { 0 };
    int dist[2001];
    memset(dist, 0x7f, sizeof dist);
    que.push({ s, 0 });
    dist[s] = 0;
    while (!que.empty()) {//다익스트라 알고리즘
        int cur = que.top().dest, cost = que.top().cost;
        auto &cur_vtx = vtx[cur];
        que.pop();
        for (int i = 0; i < cur_vtx.size(); i++) {
            if (dist[cur_vtx[i].dest] > dist[cur] + cur_vtx[i].cost) {
 
                dist[cur_vtx[i].dest] = dist[cur] + cur_vtx[i].cost;
                que.push({ cur_vtx[i].dest, dist[cur_vtx[i].dest] });
 
 
                check[cur_vtx[i].dest] = check[cur];//전 경로의 check 값 상속
                if ((cur == g && cur_vtx[i].dest == h) || (cur == h && cur_vtx[i].dest == g))
                    check[cur_vtx[i].dest] = 1;//경로가 g-h 간선을 지나는 경우 체크
            }
 
        }
    }
    for (int i = 0; i < t; i++) {
        if (check[cand[i]])
            cout << cand[i] << ' ';
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
        cout << '\n';
    }
}
```
***
