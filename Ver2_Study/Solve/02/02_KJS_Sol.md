## 2560 짚신벌레
벌레. 죽은벌레 배제하는데 시간 오래걸림
```C++
#include <stdio.h>
#include <stdlib.h>
int DP[10000001];
void solve(int a, int b, int d, int N)
{
    for (int i = 0; i <= N; i++){
        if (i < a)
            DP[i] = 1;
        else if (i < b)
            DP[i] = (DP[i - 1] + DP[i - a])%1000;
        else
            DP[i] = (DP[i - 1] + DP[i - a] - DP[i - b]+1000)%1000;
    }
    if (N >= d)
        printf("%d", (DP[N] - DP[N - d]+1000)%1000);
    else
        printf("%d", DP[N]);
}
int main(void){
    int a, b, d, N;
    scanf("%d %d %d %d", &a, &b, &d, &N);
    solve(a, b, d, N);
    return 0;
}

```
## 2096 내려가기

기존 누적값 -> 인접한 현재 step값을 비교하면 대각선을 못잡더라.
step값 -> 인접한 기존 누적값을 비교해야 잘돌아감

```C
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

#include <stdio.h>
#include <stdlib.h>

int DP1[3];
int DP2[3];
int step[3];

int main(void)
{
	int N;
	int Max, Min;
	int max0, max1, max2;
	int min0, min1, min2;
	scanf("%d", &N);
	scanf("%d %d %d", &step[0], &step[1], &step[2]);
	for (int i = 0; i < 3; i++)
	{
		DP1[i] = step[i];
		DP2[i] = step[i];
	}
	for (int i = 0; i < N-1; i++)
	{
		scanf("%d %d %d", &step[0], &step[1], &step[2]);
		max0 = max(DP1[0], DP1[1])+step[0];
		max1 = max(DP1[0], max(DP1[1], DP1[2])) + step[1];
		max2 = max(DP1[1], DP1[2]) + step[2];

		min0 = min(DP2[0], DP2[1]) + step[0];
		min1 = min(DP2[0], min(DP2[1], DP2[2])) + step[1];
		min2 = min(DP2[1], DP2[2]) + step[2];

		DP1[0] = max0;
		DP1[1] = max1;
		DP1[2] = max2;

		DP2[0] = min0;
		DP2[1] = min1;
		DP2[2] = min2;
	}

	Max = max(DP1[0], max(DP1[1], DP1[2]));
	Min = min(DP2[0], min(DP2[1], DP2[2]));
	printf("%d %d", Max, Min);
	return 0;
}
```
