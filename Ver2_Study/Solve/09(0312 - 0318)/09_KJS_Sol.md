# 탑
스택을 이용하여 품
ios_base::sync_with_stdio(false); << 없어서 시간초과남

1. top > current height -> top의 index 출력
2. top < current height -> 1.이나 3.까지 pop
3. stack is empty -> 0 출력
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

stack<pair<int, int>> s;

int main(void)
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	int n; //# of towers
	int h; // current height of tower
	cin >> n;
	for (int i = 1; i < n + 1; i++)
	{
		cin >> h;
		while (!s.empty())
		{
			if (s.top().second > h) // 1. top > current height
			{
				printf("%d ", s.top().first);
				break;
			}
			else // 2. top < current height
				s.pop();
		}
		if (s.empty())//3. stack is empty
		{
			printf("0 ");
		}
		s.push(make_pair(i, h));
	}
	return 0;
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
