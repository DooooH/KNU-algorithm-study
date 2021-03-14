## 벽 부수고 이동하기 2

```c++
#include <iostream>
#include <queue>
#define MAPSIZE 1000
#define WALL 1
#define ROAD 0

using namespace std;

queue<pair<pair<int, int>, pair<int, int>>> q; // version, breakable, x, y
int map[MAPSIZE][MAPSIZE];
int dist[11][MAPSIZE][MAPSIZE]; // also visit
int h, w;
int breakable;
int x[4] = {0, 1, 0, -1};
int y[4] = {1, 0, -1, 0};

int find_min() {
    q.push({{0, breakable}, {0, 0}});
    dist[0][0][0] = 1;
    while (!q.empty())
    {
        int cur_ver, cur_breakable;
        int cur_x, cur_y;
        cur_ver = q.front().first.first;
        cur_breakable = q.front().first.second;
        cur_x = q.front().second.first;
        cur_y = q.front().second.second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int next_x, next_y;
            if ((next_x = cur_x + x[i]) >= 0 && next_x < w &&
            (next_y = cur_y + y[i]) >= 0 && next_y < h)
            {
                if (map[next_y][next_x] != WALL && dist[cur_ver][next_y][next_x] == 0)
                {
                    dist[cur_ver][next_y][next_x] = dist[cur_ver][cur_y][cur_x] + 1;
                    q.push({{cur_ver, cur_breakable}, {next_x, next_y}});
                }
                else if (map[next_y][next_x] == WALL && cur_breakable != 0 &&
                dist[cur_ver + 1][next_y][next_x] == 0)
                {
                    dist[cur_ver + 1][next_y][next_x] = dist[cur_ver][cur_y][cur_x] + 1;
                    q.push({{cur_ver + 1, cur_breakable - 1}, {next_x, next_y}});
                }
            }
        }
    }
    int min_dist = h * w + 1;
    for (int i = 0; i <= breakable; i++)
    {
        if (dist[i][h - 1][w - 1] == 0)
            continue;
        else
            min_dist = min(min_dist, dist[i][h - 1][w - 1]);
    }
    if (min_dist == h * w + 1)
        return -1;
    else
        return min_dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> h >> w >> breakable;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char val;
            cin >> val;
            map[i][j] = val - '0';
        }
    }
    cout << find_min() << "\n";
}
```

## 좋다

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr_size;
vector<int> arr;

int count_good() {
    int count = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        vector<int> sum_arr = arr;
        vector<int>::iterator idx = sum_arr.begin() + i;
        sum_arr.erase(idx);
        // size check
        if (sum_arr.size() <= 1)
            break;
        int pointer[2];
        pointer[0] = 0;
        // sub_min,max check
        long long sub_min = sum_arr[pointer[0]] + sum_arr[pointer[0] + 1]; // seg fault
        if (sub_min > arr[i])
            continue;
        long long sub_max = sum_arr[sum_arr.size() - 1] + sum_arr[sum_arr.size() - 2];
        if (sub_max < arr[i])
            continue;
        int left = pointer[0], right = sum_arr.size() - 1;
        while (pointer[0] != sum_arr.size() - 1)
        {
            pointer[1] = (left + right) / 2;
            int cur_sum;
            if ((cur_sum = sum_arr[pointer[0]] + sum_arr[pointer[1]]) == arr[i])
            {
                count++;
                break;
            }
            else if (left <= right) {
                if (cur_sum > arr[i]) 
                    right = pointer[1] - 1;
                else if (cur_sum < arr[i])
                    left = pointer[1] + 1;
            }
            else {
                pointer[0]++;
                left = pointer[0];
                right = sum_arr.size() - 1;
            }
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> arr_size;
    for (int i = 0; i < arr_size; i++)
    {
        int temp;
        cin >> temp;
        arr.push_back(temp);
    }
    sort(arr.begin(), arr.end());
    cout << count_good() << "\n";
    return 0;
}
```

## 욕심쟁이 판다

```c++
#include <iostream>
#include <cstring>
#define MAPSIZE 500
#define COMP(a, b) a > b ? a : b
using namespace std;

int map[MAPSIZE][MAPSIZE];
int memory[MAPSIZE][MAPSIZE];
int forest_size;
int x[4] = {0, 1, 0, -1};
int y[4] = {1, 0, -1, 0};

int find_max(int cur_x, int cur_y) {
    if (memory[cur_y][cur_x] != 0)
        return memory[cur_y][cur_x];
    memory[cur_y][cur_x] = 1;
    for (int i = 0; i < 4; i++)
    {
        int next_x, next_y;
        next_x = cur_x + x[i];
        next_y = cur_y + y[i];
        if (next_x >= 0 && next_x < forest_size &&
        next_y >= 0 && next_y < forest_size &&
        map[cur_y][cur_x] < map[next_y][next_x])
        {
            memory[cur_y][cur_x] = max(memory[cur_y][cur_x], find_max(next_x, next_y) + 1);
        }
    }
    return memory[cur_y][cur_x];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> forest_size;
    for (int i = 0; i < forest_size; i++) {
        for (int j = 0; j < forest_size; j++) {
            int val;
            cin >> val;
            map[i][j] = val;
        }
    }
    int max_life = 0;
    for (int i = 0; i < forest_size; i++)
    {
        for (int j = 0; j < forest_size; j++)
        {
            max_life = COMP(find_max(j, i), max_life);
        }
    }
    cout << max_life << "\n";
}
```

## 수상 택시

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> p;
int target;
vector<p> overlap;
vector<p> trimmed;

void trim_overlap() {
    int sum = 0;
    int start = -1, end = -1;
    for (int i = 0; i < overlap.size(); i++)
    {
        if (sum == 0)
            start = overlap[i].first;
        sum += overlap[i].second;
        if (sum == 0)
        {
            end = overlap[i].first;
            sum = 0;
            trimmed.push_back({start, end});
            start = -1;
            end = -1;
        }
    }
}

long long solution() {
    long long answer = 0;
    long long trim_sum = 0;
    trim_overlap();
    answer += target;
    for (int i = 0; i < trimmed.size(); i++)
        trim_sum += (trimmed[i].second - trimmed[i].first) * 2;
    answer += trim_sum;
    return answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int paths;

    cin >> paths >> target;
    for (int i = 0; i < paths; i++)
    {
        int from, to;
        cin >> from >> to;
        if (from < to)
            continue;
        overlap.push_back({to, -1});
        overlap.push_back({from, 1});
    }
    sort(overlap.begin(), overlap.end());
    cout << solution() << "\n";
    return 0;
}
```
