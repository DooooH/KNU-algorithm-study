## 탑

```c++
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef pair<int, int> p;

vector<p> tower_vec;
stack<p> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tower_num;
    cin >> tower_num;

    for (int i = 0; i < tower_num; i++)
    {
        int tower_height;
        cin >> tower_height;
        tower_vec.push_back({tower_height, 0});
    }

    for (int i = tower_vec.size() - 1; i >= 0; i--)
    {
        if (s.size() == 0)
            s.push({tower_vec[i].first, i});
        else {
            while (s.size() != 0 && s.top().first < tower_vec[i].first)
            {
                tower_vec[s.top().second].second = i + 1;
                s.pop();
            }
            s.push({tower_vec[i].first, i});
        }
    }

    for (int i = 0; i < tower_vec.size(); i++)
        cout << tower_vec[i].second << " ";
    cout << "\n";
    return 0;
}
```

## 미확인 도착지 (메모리 초과)

```c++
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 999999999

using namespace std;

typedef pair<int, int> p;
// typedef pair<long long, int> q_pair;
int TC;
int nodes, roads, targets;
int start, pass_g, pass_h;
vector<p> map[2001];
priority_queue<p> q;
vector<int> target_candidates;
int dist[2001];
int from[2001];

void init_dist() {
    for (int i = 0; i <= nodes; i++)
    {
        from[i] = 0;
        dist[i] = INF;
    }
    dist[start] = 0;
    from[start] = start;
}

void shortest_path() {
    init_dist();
    q.push({-0, start});
    int node;
    int node_cost;
    int to;
    int cost;
    while (!q.empty())
    {
        node = q.top().second;
        node_cost = -q.top().first;
        q.pop();
        if (dist[node] != node_cost)
            continue;
        for (int i = 0; i < map[node].size(); i++)
        {
            to = map[node][i].first;
            cost = map[node][i].second;
            if (node_cost + cost < dist[to])
            {
                dist[to] = node_cost + cost;
                from[to] = node;
                q.push({-dist[to], to});
            }
        }
    }
}

int check_path(int idx)
{
    if (idx == start || 0)
        return -1;
    if ((idx == pass_g && from[idx] == pass_h) ||
    (idx == pass_h && from[idx] == pass_g))
        return 1;
    if (check_path(from[idx]) == 1)
        return 1;
    return 0;
}

void check_target() {
    for (int i = 0; i < target_candidates.size(); i++)
    {
        if (check_path(target_candidates[i]) == 1)
            cout << target_candidates[i] << " ";
    }
    cout << "\n";
}

void clear_data()
{
    for (int i = 0; i < 2001; i++)
        map[i].clear();
    target_candidates.clear();
}

int main() {
    cin >> TC;
    int from, to, cost;
    int target_candid;
    for (int i = 0; i < TC; i++)
    {
        cin >> nodes >> roads >> targets;
        cin >> start >> pass_g >> pass_h;
        for (int j = 0; j < roads; j++)
        {
            cin >> from >> to >> cost;
            map[from].push_back({to, cost});
            map[to].push_back({from, cost});
        }
        for (int j = 0; j < targets; j++)
        {
            cin >> target_candid;
            target_candidates.push_back(target_candid);
        }
        sort(target_candidates.begin(), target_candidates.end());
        shortest_path();
        check_target();
        clear_data();
    }
    return 0;
}
```
