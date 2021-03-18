# 탑
스택을 이용하여 품
ios_base::sync_with_stdio(false); << 없어서 시간초과남

1. top > current height -> top의 index 출력
2. top < current height -> 1.이나 3.까지 pop
3. stack is empty -> 0 출력
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
패턴 찾기

1 -> 필승(-1)
2 -> 필패(-1, -1)
3 -> 필승(-3)
4 -> 필승(-4)
5->(-3)->2 => 승리
6->(-4)->2 => 승리
7-> 6,4,3 => 패배

이후 반복
```c++
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<string>
#include<map>
#include<vector>
#include<math.h>
using namespace std;

int main() 
{
    long long n;
    cin >> n;
    if (n%7 == 0 || n%7 == 2)
        cout << "CY";
    else
        cout << "SK";
}
```
***
