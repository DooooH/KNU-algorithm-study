## 어른 상어

```c++
#include <iostream>
#include <vector>

using namespace std;

typedef pair<pair<int, int>, int> xy_p;
typedef pair<int, int> p;
// empty, up, down, left, right
int x[5] = {0, 0, 0, -1, 1};
int y[5] = {0, -1, 1, 0, 0};

int map_size, shark_size, smell_last;
int shark_last;
xy_p sharks[401];
bool shark_exist[401];
vector<int> priority[401][5];
// first: shark, second: smell
p visit[20][20];

int move_nosmell(int cur_x, int cur_y, int cur_view, int shark_num) {
    for (int j = 1; j <= 4; j++)
    {
        int next_x, next_y;
        next_x = cur_x + x[priority[shark_num][cur_view][j]];
        next_y = cur_y + y[priority[shark_num][cur_view][j]];
        if (next_x < 0 || next_x >= map_size || next_y < 0 || next_y >= map_size)
            continue;
        if (visit[next_y][next_x].first == 0)
        {
            sharks[shark_num].first.first = next_x;
            sharks[shark_num].first.second = next_y;
            sharks[shark_num].second = priority[shark_num][cur_view][j];
            return 1;
        }
    }
    return 0;
}


int move_mysmell(int cur_x, int cur_y, int cur_view, int shark_num) {
    for (int j = 1; j <= 4; j++)
    {
        int next_x, next_y;
        next_x = cur_x + x[priority[shark_num][cur_view][j]];
        next_y = cur_y + y[priority[shark_num][cur_view][j]];
        if (next_x < 0 || next_x >= map_size || next_y < 0 || next_y >= map_size)
            continue;
        if (visit[next_y][next_x].first == shark_num)
        {
            sharks[shark_num].first.first = next_x;
            sharks[shark_num].first.second = next_y;
            sharks[shark_num].second = priority[shark_num][cur_view][j];
            return 1;
        }
    }
    return 0;
}

int move_smell(int cur_x, int cur_y, int cur_view, int shark_num) {
    for (int j = 1; j <= 4; j++)
    {
        int next_x, next_y;
        next_x = cur_x + x[priority[shark_num][cur_view][j]];
        next_y = cur_y + y[priority[shark_num][cur_view][j]];
        if (next_x < 0 || next_x >= map_size || next_y < 0 || next_y >= map_size)
            continue;
        sharks[shark_num].first.first = next_x;
        sharks[shark_num].first.second = next_y;
        sharks[shark_num].second = priority[shark_num][cur_view][j];
        return 1;
    }
    return 0;
}

int if_collision(int next_x, int next_y, int cur_shark_num) {
    if (shark_exist[cur_shark_num] == false)
        return 0;
    for (int i = 1; i < cur_shark_num; i++)
    {
        if (shark_exist[i] == true && next_x == sharks[i].first.first && next_y == sharks[i].first.second)
        {
            shark_exist[cur_shark_num] = false;
            shark_last--;
            return 1;
        }
    }
    return 0;
}

void cur_smell() {
    for (int i = 1; i <= shark_size; i++)
    {
        if (shark_exist[i] == false)
            continue;
        visit[sharks[i].first.second][sharks[i].first.first].first = i;
        visit[sharks[i].first.second][sharks[i].first.first].second = smell_last;
    }
}

void decrease_smell() {
    for (int i = 0; i < map_size; i++)
    {
        for (int j = 0; j < map_size; j++)
        {
            if (visit[i][j].first != 0)
            {
                visit[i][j].second--;
                if (visit[i][j].second == 0)
                    visit[i][j].first = 0;
            }
        }
    }
}

void move_shark() {
    cur_smell();
    for (int i = 1; i <= shark_size; i++)
    {
        if (shark_exist[i] == false)
            continue;
        int cur_x, cur_y;
        int cur_view;
        cur_x = sharks[i].first.first;
        cur_y = sharks[i].first.second;
        cur_view = sharks[i].second;
        if (move_nosmell(cur_x, cur_y, cur_view, i))\
            ;
        else if (move_mysmell(cur_x, cur_y, cur_view, i))
            ;
        else
            move_smell(cur_x, cur_y, cur_view, i);
    }
    for (int i = 1; i <= shark_size; i++)
    {
        int next_x, next_y;
        next_x = sharks[i].first.first;
        next_y = sharks[i].first.second;
        if_collision(next_x, next_y, i);
    }
}


int process() {
    for (int i = 0; i <= 1000; i++)
    {
        if (shark_last == 1)
            return i;
        move_shark();
        decrease_smell();
    }
    return -1;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> map_size >> shark_size >> smell_last;
    shark_last = shark_size;
    for (int i = 0; i < map_size; i++)
    {
        for (int j = 0; j < map_size; j++)
        {
            int shark_num;
            cin >> shark_num;
            if (shark_num != 0)
            {
                sharks[shark_num] = make_pair(make_pair(j, i), 0);
                shark_exist[shark_num] = true;
            }
        }
    }
    for (int i = 1; i <= shark_size; i++)
    {
        cin >> sharks[i].second; // shark view
    }
    for (int i = 1; i <= shark_size; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            //dummy value
            priority[i][j].push_back(0);
            for (int k = 0; k < 4; k++)
            {
                int priority_view;
                cin >> priority_view;
                priority[i][j].push_back(priority_view);
            }
        }
    }
    cout << process() << "\n";
    return 0;
}
```

## ZOAC

```c++
#include <iostream>
#include <string>

#define MAX 'Z' + 1

using namespace std;

string s;
char print_s[100];
bool used[100];
int first = 0, last = 0;
char min_char = MAX;
int min_idx = -1;

void print_string() {
    for (int i = 0; i < s.size(); i++)
    {
        if (used[i])
            cout << s[i];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    int count = 0;
    while (count != s.size())
    {
        int i = s.size() - 1;
        while (i >= 0 && used[i] == true)
            i--;
        if (i < 0)
            break;
        while (i >= 0 && used[i] == false)
        {
            if (s[i] <= min_char)
            {
                min_char = s[i];
                min_idx = i;
            }
            i--;
        }
        used[min_idx] = true;
        print_string();
        min_idx = -1;
        min_char = MAX;
        count++;
    }
    return 0;
}
```
## 길 찾기 게임

```c++
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

struct TreeNode{
    int index;
    pair<int, int> location;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : index(-1), location(0,0), left(nullptr), right(nullptr) {} //location 초기화??
    TreeNode(int x) : index(x), location(0,0), left(nullptr), right(nullptr) {}
    TreeNode(int x, int y) : index(x), location(y,0), left(nullptr), right(nullptr) {}
    TreeNode(int x, int y, int z) : index(x), location(y,z), left(nullptr), right(nullptr) {}
    TreeNode(int x, int y, int z, TreeNode *left, TreeNode *right) : index(x), location(y,z), left(left), right(right) {}
};

// bool comp(pair<int, int> a, pair<int, int> b)
// {
//  return a.first < b.first;
// }

void tree_insert(TreeNode *parent, TreeNode *child)
{
    if (child->location.first < parent->location.first)
    {
        if (parent->left == nullptr)
            parent->left = child;
        else
            tree_insert(parent->left, child);
    }
    else
    {
        if (parent->right == nullptr)
            parent->right = child;
        else
            tree_insert(parent->right, child);
    }
}

TreeNode *make_node(TreeNode **ptr, int x, int y, int z)
{
    // TreeNode *ptr;

    if ((*ptr = (TreeNode *)malloc(sizeof(**ptr))) == 0)
        return nullptr;
    **ptr = TreeNode(x, y, z);
    return *ptr;
}

void preorder(TreeNode *node, vector<int> &answer)
{
    if (node != nullptr)
    {
        answer.push_back(node->index);
        preorder(node->left, answer);
        preorder(node->right, answer);
    }
}

void postorder(TreeNode *node, vector<int> &answer)
{
    if (node != nullptr)
    {
        postorder(node->left, answer);
        postorder(node->right, answer);
        answer.push_back(node->index);
    }
}
struct comparator{
    bool operator()(pair<int, int> a, pair<int, int> b) const
    {
        if (a.second != b.second)
            return a.second > b.second;
        else
            return a.first < b.first;
    }
};

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    TreeNode *root;
    map<pair<int, int>, int, comparator> m;
    pair<int, int> temp;
    pair<pair<int, int>, int> m_temp;

    for (int i = 0; i < nodeinfo.size(); i++)
    {
        temp = make_pair(nodeinfo[i][0], nodeinfo[i][1]);
        m_temp = make_pair(temp, i + 1);
        m.insert(m_temp);
    }


    // for (auto t = m.begin(); t != m.end(); t++)
    // {
    //  cout << (*t).second << " ";
    // }
    map<pair<int, int>, int, comparator>::iterator it;
    // root->index = (*it).second;
    // root->location.first = (*it).first.first;
    // root->location.second = (*it).first.second;
    // cout << root->index << " " << root->location.first << " " << root->location.second << "\n";
    for (it = m.begin(); it != m.end(); it++)
    {
        TreeNode *node;

        if (it == m.begin())
            root = make_node(&node, (*it).second, (*it).first.first, (*it).first.second);
        else
            tree_insert(root, make_node(&node, (*it).second, (*it).first.first, (*it).first.second));
    }

    vector<int> temp_vector;
    preorder(root, temp_vector);
    answer.push_back(temp_vector);
    // cout << "\n";
    // for (auto t = temp_vector.begin(); t != temp_vector.end(); t++)
    // {
    //  cout << *t << " ";
    // }
    // cout << "\n";
    temp_vector.clear();

    postorder(root, temp_vector);
    answer.push_back(temp_vector);
    // for (auto t = temp_vector.begin(); t != temp_vector.end(); t++)
    // {
    //  cout << *t << " ";
    // }
    // cout << "\n";
    return answer;
}

int main()
{
    vector<vector<int>> nodeinfo = {{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}};
    solution(nodeinfo);
    return 0;
}


// vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
//     vector<vector<int>> answer;

//  // cout << (*max(answer.begin(), answer.end(), cmp))[1] << "\n";

//  for (auto iter = m.begin(); iter != m.end(); iter++)
//  {
//      cout << (*iter).second << " / " << (*iter).first.first << " " << (*iter).first.second << "\n";
//  }
//     return answer;
// }
```

## 원판 돌리기
