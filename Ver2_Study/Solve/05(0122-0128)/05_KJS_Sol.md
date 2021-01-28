# 히스토그램에서 가장 큰 직사각형
스택으로 해결.

```c++
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<stack>
#include<algorithm>
#include<memory.h>

using namespace std;

long long item[100001]; //array to store each item;


void solve(int num_data)
{
	memset(item, 0, sizeof(item));
	stack <long long> s;
	item[0] = 0;
	long long ans = 0;
	for (int i = 1; i <= num_data; i++)
	{
		scanf("%lld", &item[i]);
	}
	s.push(0);
	for (int i = 1; i <= num_data + 1; i++) 
	{
		while (!s.empty() && item[s.top()] > item[i]) 
		{
			long long height = s.top();
			s.pop();
			long long x = i - s.top() -1;
			ans = max(ans, x*item[height]);
		}
		s.push(i);
	}
	printf("%lld\n", ans);
}

int main(void)
{
	int num_data;	//1~100,000
	scanf("%d", &num_data);

	while (num_data)
	{
		solve(num_data);
		scanf("%d", &num_data);
	}
	return 0;
}
```
***
# IQ Test
왜안되노?
