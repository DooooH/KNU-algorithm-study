# 도는 스시

덱 사용해서 sliding window 방식 사용

```C++
#include <iostream>
#include<vector>

using namespace std;


int N, d, k, c;// # of plate, # of kind, window size, coupon #

int result = 0;
int kind;
int bucket[3001];
vector<int> line;
deque<int> q;

int max1(int a, int b)
{
	return a >= b ? a : b;
}

int main(void)
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int temp;
	int back, front;
	int max = 0;
	cin >> N >> d >> k >> c;
	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		line.push_back(temp);
	}
	
	for (int i = 0; i < k; i++)
	{
		q.push_front(line[i]);
		if (!bucket[line[i]]++) kind++;
		result = max1(result, kind);
	}
	
	for (int i = 0; i < N-1; i++)
	{
		q.pop_back();
		if (!(--bucket[line[i]])) kind--;
		q.push_front(line[(i + k) % N]);
		if (!(bucket[line[(i + k) % N]]++)) kind++;
		if (!bucket[c]) result = max1(result, kind + 1);
		else result = max1(result, kind);
	}


	printf("%d\n", result);
}
```
---
# 세 용액

sorting 후 1번 용액을 0~n-2까지 for문으로 지정 후
1번 용액+1 ~ 끝까지를 투포인터로 이동하며 비교

```C++
#include <iostream>
using namespace std;

long long ary[5001];
int n;
long long answer[3];

int main(void)
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> n;
	int temp;
	int rear, front;
	long long sum = 0;
	long long min = LLONG_MAX;
	for (int i = 0; i < n; i++)
	{
		cin >> ary[i];
	}
	sort(ary, ary + n);

	for (int i = 0; i < n-2; i++)
	{
		rear = i + 1;
		front = n - 1;
		while (rear < front)
		{
			sum = ary[i] + ary[rear] + ary[front];
			if (abs(sum) < min)
			{
				answer[0] = ary[i];
				answer[1] = ary[rear];
				answer[2] = ary[front];
				min = abs(sum);
			}
			else if (sum < 0) rear++;
			else front--;
		}
	}
	sort(answer, answer + 3);
	printf("%lld %lld %lld", answer[0], answer[1], answer[2]);
}
```
---
# 오큰수

스택. pair로 인덱스를 같이 저장해서 pop할때 해당 index에 기록

> stack
```C++
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <iostream>
#include <stdio.h>
#include<iostream>
#include<cstdlib>
#include <stdlib.h>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<string>
#include<vector>
#include<math.h>
#include <climits>
#include<queue>
using namespace std;

stack<pair<int,int>> stk;
int result[1000001];
int counter = 0;
void insert(int temp, int idx)
{
	while (stk.top().first < temp)
	{
		result[stk.top().second] = temp;
		stk.pop();
	}

	stk.push(make_pair(temp, idx));
}

int main(void)
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	memset(result, -1, sizeof(result));
	int N;
	cin >> N;
	stk.push(make_pair(10000000, 1));
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		insert(temp,i);
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d ", result[i]);
	}
}
```
