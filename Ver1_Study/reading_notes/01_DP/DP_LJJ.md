## DP
특정 범위까지의 값을 구하기 위해서 그것과 다른 범위까지의 값을 이용하여 효율적으로 값을 구하는 알고리즘 설계기법이다. 
DP(Dynamic Programming)으로 동적계획법 이라한다.
>분할 정복 알고리즘과 비슷하다. 
>시간 복잡도를 줄이기 위해 도입됨.

### 메모제이션(Memoizaion)
재귀 호출시, 반복적으로 계산되는 것들의 계산횟수를 줄이기 위해 이전에 **계산했던 값들을 저장해두었다가**, 나중에 **재사용** 하는 것

### Top down VS Botton up
피보나치 수열을 예로 들었을 때, 큰줄기를 작은가지로 쪼개는 것을 Top-down이라 하고, 작은가지를 모아 큰 줄기로 가는 것을 Bottom-up이라고 한다.