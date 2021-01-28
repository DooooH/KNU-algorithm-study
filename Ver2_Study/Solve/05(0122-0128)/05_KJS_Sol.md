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
되네.

```c++
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int input[50];
int diff[3];
int main(void)
{
    int num_data;
    int a, b;
    int flag;

    scanf("%d", &num_data);



    for (int i = 0; i < num_data; i++)
    {
        scanf("%d", &input[i]);
    }

    if (num_data == 1) // input이 1개인 경우
    {
        printf("A");
        return 0;
    }
    if (num_data == 2)//input이 2개인 경우
    {
        if (input[0] == input[1])
        {
           printf("%d\n", input[0]);
           return 0;
        }
        else
        {
            printf("A");
            return 0;
        }
    }
    else
    {
        if (input[0] == input[1])
        {
            a = 0;
            b = input[1];
        }
        else
        {
            a = (input[2] - input[1])/(input[1]-input[0]);
            b = input[1] - input[0] * a;
        }
    }

    flag = 1;

    for (int i = 1; i < num_data; i++)
    {
        if (input[i] == input[i - 1] * a + b)
            continue;
        else
        {
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        printf("%d\n", input[num_data - 1] * a + b);
    }
    else
        printf("B");
    return 0;
}
```
***
