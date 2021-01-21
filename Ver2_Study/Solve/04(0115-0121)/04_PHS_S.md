# 책 페이지

현재 자리수의 숫자 기준으로 경우의 수를 나눌 수 있습니다. 예를 들어 1234라는 수가 있을 때 첫자리부터 경우의 수를 생각해 봅시다.

XXX0 의 경우 0000은 없는 페이지 이므로 XXX에 001~123 까지 총 123의 경우의 수가 있습니다.

XXX1 ~ XXX4 까지의 경우 XXX 자리에 000~123 까지 총 124의 경우의 수가 있습니다.

XXX5 ~ XXX9 까지의 경우 XXX자리에 000~122 까지 올 수 있으므로 총 122의 경우의 수가 있습니다.

 

다음 자리 수로 넘어가면 비슷하지만 앞에 올 수 있는 수를 고려해야 합니다.

XX0Y 의 경우 XX에서는 01 ~ 12 까지 12번, Y의 경우 0 ~ 9 까지 10번, 12 * 10 총 120의 경우의 수가 있습니다.

XX1Y ~ XX3Y 의 경우 XX : 00 ~ 12, Y : 0 ~ 9 => 13 * 10 = 130

주의해야 할 점은 XX3Y의 경우 XX가 12, 즉 123Y의 경우 뒤에 Y가 0 ~ 4 까지 밖에 올 수 없습니다. 따라서 이를 처리해 주기 위해 5 ~ 9 : 5개의 경우의 수를 빼 주어야 합니다.

XX4Y ~ XX9Y 의 경우 XX : 00 ~ 11, Y : 00 ~ 99 => 12 * 10 = 120

따라서 다음과 같은 식으로 바꿀 수 있습니다. i는 현재 자릿수, idx는 해당 자리의 숫자, X는 앞에 올 수 있는 경우의 수, 10^Y는 뒤에는 어떠한 수도 올 수 있으므로 Y자릿수의 모든 경우의 수를 의미합니다.

i = 0 : (X-1) * (10^Y)

i = 1 ~ idx-1 : X * (10^Y)

i = idx : X * (10^Y) - (10^(Y+1) - Y)

i = idx + 1 ~ 9 : (X-1) * (10^Y)

```C++
#include <cstdio>
 
int main(void) {
    int n, ary[10] = { 0 };
    scanf("%d", &n);
    for (int cur = n, expr = 1; cur; expr *= 10) {
        int idx = cur % 10, next = cur / 10;
        ary[0] += next * expr;
        for (int i = 1; i <= idx; i++)
            ary[i] += (next + 1)*expr;
        ary[idx] -= expr - (n%expr) - 1;
        for (int i = idx + 1; i < 10; i++)
            ary[i] += next * expr;
 
        cur = next;
    }
    for (int i = 0; i < 10; i++)
        printf("%d ", ary[i]);
}
```
***
# 앱

cost의 크기가 작기 때문에 인덱스로 활용할 수 있어 사용할 앱 : i, cost : j, 확보한 메모리 : dp[j] 으로 두고 점화식을 새웁니다.

현재 선택한 앱이 i일 때 dp[j] = max(dp[j], dp[j - cost[i]] + memory[i] 가 되며 완전 탐색을 하고 각 스텝에서 확보한 메모리가 m 이상인 경우 cost를 비교해 최솟값을 찾아냅니다.

주의해야 할 점은 dp배열을 1차원으로 사용할 시 dp[j - cost[i]] 값을 활용하기 때문에 충돌을 피해 dp[j] 값을 찾기 위해서는 j를 10000부터 cost[i] 까지 내려가면서 탐색을 해야 합니다.

```C++
#include <cstdio>
#define max(a,b) a>b ? a : b
int main() {
    int n, m, ans = 0x7fffffff;
    int mem[100], cost[100], dp[10001] = { 0 };
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &mem[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &cost[i]);
    for (int i = 0; i < n; i++) {
        for (int j = 10000; j >= cost[i]; j--) {
            dp[j] = max(dp[j], dp[j - cost[i]] + mem[i]);
            if (dp[j] >= m && j < ans)ans = j;
        }
    }
    printf("%d", ans);
}
```
***
# 사전
a를 두고 z를 분배하는 식으로 점화식을 짜봅니다.

예를 들어 a : 3, z : 4 일 경우

_a_a_a_ 로 두고 z를 분배할 수 있는 공간은 4칸이 됩니다. 따라서 총경우의 수는 a+1 H z로 35가지가 나옵니다. 문제의 조건에 따라 k가 35 보다 높은 경우 -1을 출력해 예외처리를 해 줍니다.

 

z를 분배하는 식은 z의 개수에 따라 경우의 수가 일정하지 않으며 단순히 숫자로 구간을 나누게 되면 틀립니다. 따라서 구간을 nHr 식에 대입하여 구해야 하며 사용한 z의 개수에 따라 다음 구간에 반영해 주어야 합니다.

_a_a_a_ 에서 첫 칸에 z를 하나 두는 경우 : za_a_a_ 가 되며 남은 칸 수는 3, z의 수는 3이 됩니다.

차례대로 구해보면 다음과 같습니다.

a_a_a_ : 칸=3, z=4 => 3H4 = 15

za_a_a_ : 칸=3, z=3 => 3H3 = 10

zza_a_a_ : 칸=3, z=2 => 3H2 = 6

zzza_a_a_ : 칸=3, z=1 => 3H1 = 3

zzzza_a_a_ : 칸=3, z=0 => 3H0 = 1

 

따라서 점화식을 다음과 같이 새울 수 있습니다.

칸 = n, z = r 상황에서 가질 수 있는 경우의 수 : nHr, 현재 칸에 둘 수 있는 z의 개수는 남은 k 값과 가장 가까운 nHr의 총 합이 됩니다.

위와 같은 예시에서 k가 15 이하인 경우 앞에 z를 둘 수 없으며 16~25 인 경우 za_ ..., 26~31 : zza_... 이런 식으로 나아가면 됩니다.

다음 루프로 오게 되면 a를 하나 썼으므로 칸 수 n은 1 줄게 되며 z는 그전 구간에서 사용하고 남은 z의 수가 되고 이 과정을 반복하면 됩니다.

주의해야 할 점은 a, z의 개수가 크면 nHr 값이 너무 커지므로 k값의 최대인 1,000,000,000 이상일 때 예외처리를 해 주어야 합니다.


```C++
#include <cstdio>
 
long long nCr(int n, int r) {
    if (r > n - r) r = n - r;
    long long ans = 1;
    int i;
    for (i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
        if (ans > 1000000000 || ans < 0)
            return -1;
    }
    return ans;
}
 
int main() {
    int n, r;
    long long k;
    scanf("%d%d%lld", &n, &r, &k);
    long long t = nCr(n + r, r);
 
    if (t == -1 || k <= t) {
        k--;
        for (; k; n--) {
            for (int j = r; j >= 0; j--) {
                long long t = nCr(n + j - 1, j);
                if (t == -1)
                    break;
                if (t <= k) {
                    k -= t;
                    r = j - 1;
                    printf("z");
                }
                else
                    break;
            }
            printf("a");
        }
        while (n--)
            printf("a");
        while (r--)
            printf("z");
    }
    else
        printf("-1");
}
```
***
# Parcel

무개를 인덱스로 활용해 만들 수 있는 무개를 기록합니다. 각 원소의 최대 크기는 200000으로 dp[400000]을 사용합니다.

2중 포문으로 지나처온 리스트에서 만들 수 있는 w 값을 배열에 기록해두고 다음 i, j를 사용해 만든 w - (i + j) 값이 기록되어 있다면 Yes를 출력합니다.

입력받은 값을 정렬해 ary[i+1] + ary[j] 값이 필요 이상으로 커지게 되면 break를 통해 탐색 횟수를 줄입니다.
```C++
#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    int w, n, ary[5000];
    bool dp[400001] = { 0 };
    scanf("%d%d", &w, &n);
 
    for (int i = 0; i < n; i++)
        scanf("%d", &ary[i]);
    sort(ary, ary + n);
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < i; j++)
            dp[ary[i] + ary[j]] = true;
 
        for (int j = i + 2; j < n; j++) {
            int t = w - ary[i + 1] - ary[j];
            if (t < 0)break;
            if (t <= 400000 && dp[t]) {
                printf("YES");
                return 0;
            }
        }
 
    }
    printf("NO");
}

```
***
