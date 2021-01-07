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
