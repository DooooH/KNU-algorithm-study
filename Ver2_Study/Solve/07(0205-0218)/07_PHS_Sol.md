# 숫자의 신

정렬 기반 풀이

최대의 숫자를 만들기 위해서는 몇 가지를 고려해야 합니다.

맨 앞자리는 1~9 중 재일 높은 수가 나와야 합니다.

모든 수를 고르고 난 후 남은 n-k개의 수는 가장 긴 자릿수 중 재일 높은 수를 선택해야 합니다.

1번을 고려할때 주의해야 할 점은 91, 9 의 경우9/91이 더 높은 숫자를 만들 수 있는 것입니다. 이를 위해 두 숫자 a, b가 있을 때 이들을 a/b : b/a를 비교하여 정렬을 합니다.

c++에서는 string 객체를 통해 간단하게 두 문자열을 비교하고, a/b를 a+b로 구현할 수 있으며 이를 활용해 a+b > b+a로 정렬을 합니다.

2번을 고려할 때 입력받을 시 최대 문자열을 찾아가고 모든 입력이 끝나면 남은 개수만큼 배열에 추가로 삽입해주면 됩니다.

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
 
int main() {
    int n, k;
    cin >> k >> n;
    vector<string> ary(n);
    string mx;
    for (int i = 0; i < k; i++) {
        cin >> ary[i];
        mx = mx.size() < ary[i].size() || (mx.size() == ary[i].size() && mx < ary[i]) ? ary[i] : mx;
    }
    for (int i = k; i < n; i++)
        ary[i] = mx;
 
    sort(ary.begin(), ary.end(), [](string &a, string &b)->bool {
        return a + b > b + a;
    });
 
    for (int i = 0; i < n; i++)
        cout << ary[i];
 
}
```
***
# 제곱 ㄴㄴ수
bool 배열은 char와 마찬가지로 1byte를 사용하기 때문에 메모리 사용량이 적은 bitset 객체를 사용합니다.

조건에 따라 모든 수의 비트를 만들순 없기 때문에 min ~ max 간격의 최댓값인 1000001개의 비트를 만듭니다. min ~ max 사이에 있는 수에 각각 비트를 할당하고 각 수는 index - a 위치에 저장됩니다. 초기값은 false, 0입니다.

제곱수 4, 9, 16, 25 ... 의 배수 중에서 min과 max 사이에 있는 값들을 빼주어 제곱 ㄴㄴ 수들을 구할 수 있습니다. min과 max 사이에 있는 수를 탐색하며 제곱수의 배수가 되는 경우를 1로 만들고 처음으로 1이 되면 count를 1 증가시켜 수를 셉니다.

제곱수부터 배수를 모두 탐색하게 되면 시간 초과가 발생하므로 탐색할 제곱수의 배수를 min에서 가장 가까운 upper bound 수부터 탐색을 합니다.

예를 들어 min = 10 인 경우 4의 배수를 처리해 주기 위해서는 12부터 탐색을 진행합니다.

이 upper bound 수를 구하러면 n의 배수를 처리 해주는 경우 min을 가장 가까운 n의 배수로 만들어 주면 됩니다. 

n의 배수로 만들기 위해서는 min을 n으로 나누고 다시 n을 곱해주는 소수점 삭제 방법을 사용하면 됩니다. 이때 min 자신이 n의 배수면 그대로 두어야 하기 대문에 범위 수정을 위해 식을 (min + n - 1) / n * n을 사용합니다.

가장 배수가 많은 4를 먼저 전처리 해준 후 9, 25, ... 의 배수들을 max를 넘지 않는 선에서 처리를 해 줍니다.
```c++
#include <cstdio>
#include <bitset>
using namespace std;
int main() {
    long long a, b, i, j, t;
    bitset<1000001> ary;
    scanf("%lld%lld", &a, &b);
    int count = 0;
    for (i = (a + 3) / 4 * 4; i <= b; i += 4) {
        ary[i - a] = 1;
        count++;
    }
    for (i = 3, t; (t = i * i) <= b; i += 2) {
        for (j = (t + a - 1) / t * t; j <= b; j += t) {
            if (!ary[j - a]) {
                ary[j - a] = 1;
                count++;
            }
        }
    }
    printf("%d", b - a + 1 - count);
}
```
***
# 코딩은 예쁘게

문제에서 주어진 조건에 따라 연속된 줄을 한번에 편집이 가능하며 주의해야 할 점은 편집할 때 추가, 삭제 중 한가지만 가능하다는 것입니다. 따라서 -2, 1 를 그룹으로 선택하여 편집하는 것 보다 양수, 음수 끼리 그룹을 만들어 편집을 하는 것이 유리합니다. 

그룹으로 나눈 후 같은 부호의 수 끼리 비교를 할 때 2가지 경우로 나눌 수 있습니다.

다음 수가 현재 수 보다 클 때(ary[i-1] < ary[i]) : 이 경우 다음 수를 편집하는 도충에 이전 수를 편집 완료 할 수 있습니다. 3, 5, 8 수가 있을 때 모든 수를 3번 편집 하면 0, 2, 5 가 되고, 남은 2, 5를 2번 편집하면 3이 남아 총 2+3+5, 즉 8번, ary[i] 번으로 편집으로 완료할 수 있습니다. 즉 계속해서 이 경우만 나올경우 마지막 수 만큼 편집을 하면 됩니다.
다음 수가 현재 수 보다 작을 때(ary[i-1] > ary[i]) : 이 경우 이전 수를 처리하기 위해서는 앞의 수를 처리한 후 남은 차이만큼 더 편집을 해야 하기 때문에  | ary[i]-ary[i-1] | 이 됩니다.
수가 같은 경우 그룹으로 묶어서 처리하기 때문에 고려하지 않아도 됩니다.


```c++
#include <cstdio>
#define absol(x) (x&0x80000000 ? -(x) : x)
using namespace std;
int main() {
    int n;
    int ary[1000];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &ary[i]);
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        ary[i] -= t;
    }
        
    int count = absol(ary[n - 1]), prev = ary[0];
    for (int i = 1; i < n; prev = ary[i++]) {
        if ((ary[i] ^ prev) < 0)//부호가 바뀌는 경우
            count += absol(prev);
        else if((ary[i] ^ (ary[i] - prev)) < 0)//== |ary[i-1]| < |ary[i]|
            count += absol(ary[i] - prev);
    }
    printf("%d", count);
}
```
***
