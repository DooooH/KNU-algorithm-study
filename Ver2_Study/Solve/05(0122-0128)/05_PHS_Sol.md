# 사회망 서비스
depth 조절과 효율성을 위해 그래프 작성을 조금 다르게 합니다.

그래프 간선을 저장하며 간선 정보에는 목적지, 다음 간선의 번호로 나타냅니다.

undirect 그래프 이므로 입력받은 u, v 값을 (u, v), (v, u) 모두 저장하며 간선의 번호를 매기고 이를 저장해둡니다.

dfs 탐색 시 해당 간선이 시작하는 인덱스를 s_idx로 불러오고 간선들을 탐색합니다.

탐색시 depth가 가장 깊은 리프 노드를 얼리 어답터로 두는 것보다 리프 노드의 부모 노드를 얼리 어답터로 두는 것이 더 적은 수를 사용할 수 있습니다. 그 후 상위 노드의 경우 주변에 어답터가 없다면 자신을 어답터로 만들어 채워 나갑니다.


```c++
#include <iostream>
using namespace std;
typedef struct node {
    int dest;
    int link;
};
node vtx[2000000 - 1];
int s_idx[1000001], res;
bool dfs(int cur, int prev) {
    bool is_adaptor = false;
    for (int i = s_idx[cur]; i;) {
        int dest = vtx[i].dest;
        if (dest != prev) {
            if (!dfs(dest, cur))
                is_adaptor = true;
        }
        i = vtx[i].link;
    }
    if (is_adaptor)
        res++;
    return is_adaptor;
}
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
 
    int n;
    cin >> n;
    for (int i = 0, cur = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        vtx[++cur] = { v, s_idx[u] };
        s_idx[u] = cur;
 
        vtx[++cur] = { u, s_idx[v] };
        s_idx[v] = cur;
    }
    dfs(1, 0);
    printf("%d", res);
}
```
***
# 칵테일
문제에서 주어진 n개의 vertex와 n-1개의 edge를 가지면서 n개의 vertex에 대한 모든 관계식을 나타내기 위해서는 사이클이 존재할 수 없습니다. 따라서 입력받을 시 edge를 작성하면서 비율을 맞춰가면 됩니다.

 

최대 공약수, 최소 공배수를 활용해 곱할 값을 찾아냅니다.

현재 vertex a의 값을 a_val, vertex b 값을 b_val로 두고 비율을 p, q로 둡니다.

먼저 비율을 맞추기 전에 같은 값으로 만들어 주기 위해 최소공배수로 만들어 줍니다. 이때 서로 곱해야 할 값은 a : b/gcd, b : a/gcd 가 됩니다. 그 후 p, q를 각각 곱해주면 다음과 같아집니다.

a_val = a_val * b / gcd * p

b_val = b_val * a / gcd * q

여기서 주의해야 할 점은 vertex a와 연결된 다른 점들 또한 b / gcd * p 값을 곱해주고 b와 연결된 점들 또한 곱해주어야 전체 비율이 맞춰지게 됩니다. dfs(a, a_mod / g); dfs(b, b_mod / g); 를 통해 간단하게 구현해 줍니다.

그 후 두 점들을 연결하고 이러한 과정을 반복하면 됩니다.


```c++
#include <cstdio>
#include <string.h>
#include <vector>
using namespace std;
typedef struct vertex {
    int val;
    vector<int>edge;
}vertex;
int n;
vertex vtx[10];
bool visited[10];
long gcd(long a, long b) {//최대 공약수, 최소 공배수 = a * b / gcd
    long r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
void dfs(int cur, int val) {
    visited[cur] = true;
    vtx[cur].val *= val;//비율 반영
 
    for (auto next : vtx[cur].edge)
        if (!visited[next])
            dfs(next, val);
}
int main() {
    
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, p, q;
        scanf("%d%d%d%d", &a, &b, &p, &q);
        if (!vtx[a].val)
            vtx[a].val = 1;
        if (!vtx[b].val)
            vtx[b].val = 1;//처음 방문한 경우
 
        int g = gcd(vtx[a].val, vtx[b].val);
        int a_mod = vtx[b].val / g * p, b_mod = vtx[a].val / g * q;//곱할 값 계산
        g = gcd(a_mod, b_mod);
        memset(visited, 0, sizeof visited);
        dfs(a, a_mod / g);//전체 반영
        dfs(b, b_mod / g);
 
        vtx[a].edge.push_back(b);//연결
        vtx[b].edge.push_back(a);
    }
    for (int i = 0; i < n; i++)
        printf("%d ", vtx[i].val);
}
```
***
# IQ test
브루트 포스를 통해 ax + b 식을 구해 풀 수 있지만 느리므로 계산식을 이용해 풀었습니다.

n = 1의 경우 뒤에 어떠한 숫자가 올 수 있으므로 A

n = 2의 경우 x1 = x2 일 때 나올 수 있는 식은 y = x + 0, y = -x + 2 * x1로 2가지가 나옵니다. 하지만 x1 = x2 이므로 두 식의 결과는 항상 일정한 x1 값이 나오므로 x1을 출력합니다.

그 외의 경우는 나올 수 있는 값이 많으므로 A를 출력합니다.

n>2 인 경우 x1, x2, x3의 관계식을 통해 구합니다. 식은 항상 ax + b 1차식 형태를 가지므로 (x1, x2), (x2, x3)로 두어 기울기 a를 구한 후 b값을 (x1, x2) 값을 대입하여 구합니다.

a, b는 정수이므로 기울기 값이 정수가 아니라면 (x2, x3) 대입 시 틀린 값이 나오게 됩니다.

계속해서 입력 받은 값을 대입하여 검증하고 틀리면 B, 마지막까지 맞다면 a*x + b 값을 출력합니다.


```c++
#include <cstdio>
#include <vector>
 
using namespace std;
 
int main() {
    int n;
    scanf("%d", &n);
    if (n > 2) {
        int x, y, z, a, b;
        scanf("%d%d%d", &x, &y, &z);
        a = y-x ? (z - y) / (y - x) : 0;
        b = y - x * a;
        if (y*a + b != z) { printf("B"); return 0; }
        for (int i = 3; i < n; i++) {
            y = z;
            scanf("%d", &z);
            if (y*a + b != z) { printf("B"); return 0; }
        }
        printf("%d", z*a + b);
    }
    else if (n == 2) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x == y)
            printf("%d", x);
        else
            printf("A");
    }
    else
        printf("A");
}
```
***
# 카드 배열

indegree 방식 위상 정렬을 통해 카드 제약 조건을 미리 나열해서 맞는 위치에 최상의 카드를 두는 그리디 방식을 사용합니다.

최댓값을 구할 시 제약 조건 역순으로 마지막 조건에서 아래로 내려가는 방향으로 그래프를 작성합니다.

graph[b].push_back[a], indegree[a]++;

사용할 카드는 k개로 최대의 값을 내기 위해 n-k부터 사용해서 n까지 사용합니다.

최솟값을 구할 시 제약조건 순방향, k부터 0까지를 사용해서 최솟값을 만들어냅니다.

```c++
#include <iostream>
#include <vector>
#include <queue>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int>gph_1[300000], gph_2[300000];
    priority_queue<int, vector<int>, greater<int>>pq;
    int d_1[300000] = { 0 }, d_2[300000] = { 0 }, val[300000];
    int n, k, p;
    cin >> n >> k >> p;
    for (int i = 0; i < p; i++) {
        int a, b;
        cin >> a >> b;
        gph_1[b].push_back(a);//역순
        gph_2[a].push_back(b);
        d_1[a]++;//역순 indegree = a
        d_2[b]++;
    }
    //최댓값
    for (int i = 0; i < k; i++)
        if (!d_1[i])
            pq.push(i);
    int cur = n - k - 1;
    while (!pq.empty()) {
        int t = pq.top();
        pq.pop();
        val[t] = ++cur;//n-k -> n-1
        for (int next : gph_1[t])
            if (!--d_1[next])
                pq.push(next);
    }
    //최솟값
    for (int i = 0; i < k; i++)
        if (!d_2[i])
            pq.push(i);
    cur = k;//k -> 0
    while (!pq.empty()) {
        int t = pq.top();
        pq.pop();
        val[t] -= --cur;
        for (int next : gph_2[t])
            if (!--d_2[next])
                pq.push(next);
    }
    auto fast_pow = [](int base, int power, int m) {//함수보다 람다식이 더 빠름
        long long res = 1, t = base % m;
        while (power > 0) {
            if (power & 1)
                res = res * t % m;
            power >>= 1;
            t = t * t % m;
        }
        return res;
    };
    long long res = 0;
    for (int i = 0; i < k; i++)
        res = (res + val[i] * fast_pow(n, i, 1000000007)) % 1000000007;
    cout << res;
 
}
```
***
