
## 2579: 계단오르기

```c++
#include <bits/stdc++.h>
using namespace std;

int solve(int points[], int answer[], int N)
{
	for (int i = 1; i <= N; i++)
	{
		if (i == 1)
		{
			answer[i] = points[i];
			continue ;
		}
		if (i == 2)
		{
			answer[i] = points[i] + points[i - 1];
			continue ;
		}
		int temp1 = points[i] + points[i - 1] + answer[i - 3];
		int temp2 = points[i] + answer[i - 2];
		answer[i] = max(temp1, temp2);
	}
	return answer[N];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int N;
	cin >> N;
	int points[N + 1];
	int answer[N + 1];
	points[0] = 0;
	answer[0] = 0;
	for (int i = 1; i <= N; i++)
	{
		cin >> points[i];
		answer[i] = 0;
	}
	cout << solve(points, answer, N) << "\n";
	return (0);
}
```
