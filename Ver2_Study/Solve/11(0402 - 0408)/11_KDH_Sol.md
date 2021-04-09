## 스타트 택시

```c++
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> p;

int map_size, customer_size;
long long oil = 0;
bool map[21][21];
bool visited[21][21];

int taxi_x, taxi_y;
int x[] = {0, 1, 0, -1};
int y[] = {-1, 0, 1, 0}; //up right down left
vector<p> customer_start;
vector<p> customer_dest;
priority_queue<p> candid;
queue<p> q;

bool check_customer(int cur_x, int cur_y) {
    for (int i = 0; i < customer_start.size(); i++)
    {
        if (cur_x == customer_start[i].first - 1 && cur_y == customer_start[i].second - 1)
        {
            // y first to sort vector
            candid.push({-cur_y, -cur_x});
            return true;
        }
    }
    return false;
}

// start from taxi
// return false : fail while finding, true: found customer
bool find_customer(int start_x, int start_y) {
    int depth = 0;

    int iter = 1;
    q.push({start_x, start_y});
    visited[start_y][start_x] = true;

    while (iter != 0)
    {
        if (depth > oil) 
            return false;
        int next_iter = 0;
        bool flag = false;
        for (int i = 0; i < iter; i++)
        {
            int cur_x, cur_y;
            cur_x = q.front().first;
            cur_y = q.front().second;
            q.pop();
            if (check_customer(cur_x, cur_y))
                flag = true;
            if (flag) // find on this level
                continue;

            int next_x, next_y;
            for (int j = 0; j < 4; j++)
            {
                next_x = cur_x + x[j];
                next_y = cur_y + y[j];
                if (next_x >= 0 && next_x < map_size &&
                next_y >= 0 && next_y < map_size &&
                map[next_y][next_x] == 0 && visited[next_y][next_x] != true)
                {
                    q.push({next_x, next_y});
                    visited[next_y][next_x] = true;
                    next_iter++;
                }
            }
        }
        if (flag) // found customer
        {
            oil -= depth;
            return true;
        }
        depth++;
        iter = next_iter;
    }
    return false;
}

// return false : fail while finding, true: found dest
bool find_dest(int start_x, int start_y, int dest_x, int dest_y) {
    int depth = 0;

    int iter = 1;
    q.push({start_x, start_y});
    visited[start_y][start_x] = true;

    while (iter != 0)
    {
        if (depth > oil)
            return false;
        int next_iter = 0;
        for (int i = 0; i < iter; i++)
        {
            int cur_x, cur_y;
            cur_x = q.front().first;
            cur_y = q.front().second;
            q.pop();
            if (cur_x == dest_x && cur_y == dest_y) {
                oil += depth;
                return true;
            }

            int next_x, next_y;
            for (int j = 0; j < 4; j++)
            {
                next_x = cur_x + x[j];
                next_y = cur_y + y[j];
                if (next_x >= 0 && next_x < map_size &&
                next_y >= 0 && next_y < map_size &&
                map[next_y][next_x] == 0 && visited[next_y][next_x] != true)
                {
                    q.push({next_x, next_y});
                    visited[next_y][next_x] = true;
                    next_iter++;
                }
            }
        }
        depth++;
        iter = next_iter;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> map_size >> customer_size >> oil;
    for (int i = 0; i < map_size; i++)
        for (int j = 0; j < map_size; j++)
            cin >> map[i][j];
    cin >> taxi_y >> taxi_x;
    for (int i = 0; i < customer_size; i++)
    {
        int temp_y, temp_x;
        cin >> temp_y >> temp_x;
        customer_start.push_back({temp_x, temp_y});
        cin >> temp_y >> temp_x;
        customer_dest.push_back({temp_x, temp_y});
    }

    int start_x = taxi_x - 1;
    int start_y = taxi_y - 1;
    while (customer_start.size() != 0)
    {
        memset(visited, 0, sizeof(visited) * sizeof(bool));
        if (find_customer(start_x, start_y) == false) {
            cout << -1 << "\n";
            return 0;
        }
        else {
            start_y = -candid.top().first;
            start_x = -candid.top().second;
            while (!q.empty())
                q.pop();
            while (!candid.empty())
                candid.pop();
        }
        memset(visited, 0, sizeof(visited) * sizeof(bool));

        int dest_x, dest_y;
        int i;
        for (i = 0; i < customer_start.size(); i++)
        {
            if (start_x == customer_start[i].first - 1 && start_y == customer_start[i].second - 1) {
                dest_x = customer_dest[i].first - 1;
                dest_y = customer_dest[i].second - 1;
                customer_start.erase(customer_start.begin() + i);
                customer_dest.erase(customer_dest.begin() + i);
                break;
            }
        }
        if (find_dest(start_x, start_y, dest_x, dest_y) == false) {
            cout << -1 << "\n";
            return 0;
        }
        else {
            while (!q.empty())
                q.pop();
            start_x = dest_x;
            start_y = dest_y;
        }
    }
    cout << oil << "\n";
    return 0;
}
```

## 벡터 매칭

```c++
#include <iostream>
#include <vector>
#include <cmath>
#include <memory.h>
#include <algorithm>

using namespace std;

typedef pair<int, int> p;
int test_cases, dots_size;
vector<p> dots;
long long minimum;
bool visit[1 << 20];

void combination2(int idx, int count, long long sum_x, long long sum_y)
{
    // return;

    if (count == dots_size / 2)
    {
        for (int i = idx; i < dots_size; i++)
        {
            sum_x -= dots[i].first;
            sum_y -= dots[i].second;
        }
        minimum = min(minimum, sum_x * sum_x + sum_y * sum_y);
        return ;
    }
    else {
        // for (int i = idx + 1; i < dots_size; i++)
        {
            combination2(idx + 1, count + 1, sum_x + dots[idx].first, sum_y + dots[idx].second);
            if(idx - count < dots_size / 2)
                combination2(idx + 1, count, sum_x - dots[idx].first, sum_y - dots[idx].second);
        }
    }
}

void comb(int state, int cnt){
    if(visit[state]) return;
    visit[state] = true;
    
    if(cnt == (dots_size / 2)){
        //calculation
        long long xsum = 0, ysum = 0;
        for(int i = 0; i < dots_size; i++){
            if(state & (1 << i)) { xsum += dots[i].first; ysum += dots[i].second; }
            else { xsum -= dots[i].first; ysum -= dots[i].second; }
        }
        //update minimum value
        long long sqval = xsum * xsum + ysum * ysum;
        minimum = min(minimum, sqval);
        return;
    }

    for(int i = 0; i < dots_size; i++){
        if(state & (1 << i)) continue;
        comb(state | (1 << i), cnt + 1);
    }
}

double find_min() {
    minimum = 999999999999999999;
    // minimum = -1;
    //vector<int> to_add;
    // for (int i = 0; i <= dots_size / 2; i++)
    {
        // combination(0, to_add);
    }
    combination2(0, 0, 0, 0);
    // comb(0, 0);
    return sqrt(minimum);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> test_cases;
    for (int i = 0; i < test_cases; i++)
    {
        //memset(visit, 0, sizeof(visit));
        cin >> dots_size;
        for (int j = 0; j < dots_size; j++)
        {
            int x, y;
            cin >> x >> y;
            dots.push_back({x, y});
        }
        //cout.precision(12);
        //cout << fixed << find_min() << "\n";
        //printf("\n");
        printf("%.12lf\n", find_min());
        dots.clear();
    }
    return 0;
}
```

## 경사로

```c++
#include <iostream>

using namespace std;

int road_size, slope_len;
int road[100][100];
bool visitd[2][100][100]; // 0: horizontal, 1: vertical
int answer = 0;

bool if_larger_hor(int i, int j) {
    int count = slope_len;
    if (j - 1 < 0)
        cout << "large error\n";
    int temp_pre = road[i][j - 1];
    int temp_cur = road[i][j - 1];
    int k = j - 1;
    while (k >= 0 && count > 0) {
        temp_cur = road[i][k];
        if (temp_cur != temp_pre || visitd[0][i][k])
            break;
        count--;
        k--;
        temp_pre = road[i][k];
    }
    if (count == 0)
    {
        for (int k = j - slope_len; k < j; k++)
            visitd[0][i][k] = true;
        return true;
    }
    else
        return false;
}

bool if_smaller_hor(int i, int j) {
    int count = slope_len;
    int temp_pre = road[i][j];
    int temp_cur = road[i][j];
    int k = j;
    while (k < road_size && count > 0) {
        temp_cur = road[i][k];
        if (temp_cur != temp_pre || visitd[0][i][k])
            break;
        count--;
        k++;
        temp_pre = road[i][k];
    }
    if (count == 0)
    {
        for (int k = j; k < j + slope_len; k++)
            visitd[0][i][k] = true;
        return true;
    }
    else
        return false;
}

bool if_larger_ver(int i, int j) {
    int count = slope_len;
    if (j - 1 < 0)
        cout << "error";
    int temp_pre = road[j - 1][i];
    int temp_cur = road[j - 1][i];
    int k = j - 1;
    while (k >= 0 && count > 0) {
        temp_cur = road[k][i];
        if (temp_cur != temp_pre || visitd[1][k][i])
            break;
        count--;
        k--;
        temp_pre = road[k][i];
    }
    if (count == 0)
    {
        for (int k = j - slope_len; k < j; k++)
            visitd[1][k][i] = true;
        return true;
    }
    else
        return false;
}

bool if_smaller_ver(int i, int j) {
    int count = slope_len;
    int temp_pre = road[j][i];
    int temp_cur = road[j][i];
    int k = j;
    while (k < road_size && count > 0) {
        temp_cur = road[k][i];
        if (temp_cur != temp_pre || visitd[1][k][i])
            break;
        count--;
        k++;
        temp_pre = road[k][i];
    }
    if (count == 0)
    {
        for (int k = j; k < j + slope_len; k++)
            visitd[1][k][i] = true;
        return true;
    }
    else
        return false;
}

void check_horizontal() {
    for (int i = 0; i < road_size; i++)
    {
        int pre = road[i][0];
        int cur = road[i][0];
        int j = 0;
        for (j = 0; j < road_size; j++)
        {
            cur = road[i][j];
            if (pre < cur) {
                if (pre < cur - 1 || if_larger_hor(i, j) == false)
                    break;
            }
            else if (pre > cur) {
                if (pre - 1 > cur || if_smaller_hor(i, j) == false)
                    break;
            }
            pre = road[i][j];
        }
        if (j == road_size)
            answer++;
    }
}

void check_vertical() {
    for (int i = 0; i < road_size; i++)
    {
        int pre = road[0][i];
        int cur = road[0][i];
        int j = 0;
        for (j = 0; j < road_size; j++)
        {
            cur = road[j][i];
            if (pre < cur) {
                if (pre < cur - 1 || if_larger_ver(i, j) == false)
                    break;
            }
            else if (pre > cur) {
                if (pre - 1 > cur || if_smaller_ver(i, j) == false)
                    break;
            }
            pre = road[j][i];
        }
        if (j == road_size)
            answer++;
    }
}

int main() 
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> road_size >> slope_len;
    for (int i = 0; i < road_size; i++)
    {
        for (int j = 0; j < road_size; j++)
        {
            int height;
            cin >> height;
            road[i][j] = height;
        }
    }
    check_horizontal();
    check_vertical();
    cout << answer << "\n";
    return 0;
}
```

## 외벽 
