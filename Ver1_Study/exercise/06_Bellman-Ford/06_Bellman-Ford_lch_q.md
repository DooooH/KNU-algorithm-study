# 할로윈 묘지

문제 링크 : https://www.acmicpc.net/problem/3860

> 문제

오늘은 할로윈이다. 상근이와 친구들은 할로윈을 기념하기 위해 묘지를 방문했다. 상근이와 친구들은 한 명씩 묘지로 들어가고, 혼자서 묘지의 출구를 찾아야 한다. 이제, 상근이의 차례가 돌아왔다.

상근이가 어렸을 적에 할머니는 상근이에게 할로윈 밤에 묘지에는 귀신 구멍이 나타난다고 말해주었다. 귀신 구멍으로 들어가면, 묘지의 다른 장소로 다시 나오게 된다. 이 구멍은 시간을 이동할 수 있는 구멍이다. 귀신 구멍에 떨어지면, 특정 시간이 지난 후(또는 이전)에 평행 우주의 다른 구멍에서 나오게 된다. 

묘지는 W × H 크기의 그리드로 나타낼 수 있다. 묘지의 입구는 (0, 0)이고, 출구는 (W-1, H-1)이다. 상근이는 겁이 많기 때문에, 최대한 빨리 묘지를 나가려고 한다. 그리고 상근이는 이동하던 도중 출구에 도달하면 뒤도 돌아보지 않고 그 즉시 묘지를 빠져나갈 생각이다. 상근이는 현재 있는 칸과 동, 서, 남, 북으로 인접한 칸으로 이동할 수 있다. 각 칸은 잔디, 묘비, 또는 귀신 구멍이다.

묘비는 매우 높기 때문에, 묘비가 있는 칸으로는 이동할 수 없다.
귀신 구멍이 있는 칸으로 이동하면, 특정 시간이 지난 후에 묘지의 다른 곳에서 상근이가 나타나게 된다. 시간은 귀신 구멍마다 다르며, 양수, 음수, 0 중 하나이다.
잔디가 있는 칸으로는 자유롭게 이동할 수 있다.
상근이는 묘지를 빨리 나가기 위해 귀신 구멍도 이용할 것이다. 묘지를 나갈 수 없는 경우나, 계속해서 과거로 이동하는 경우가 존재할 수도 있다.


> 입력

입력은 여러 개의 테스트 케이스로 이루어져 있다.

각 테스트 케이스의 첫째 줄에는 묘지의 너비 W와 높이 H가 주어진다. (1 ≤ W, H ≤ 30) 다음 줄에는 묘비의 개수 G (G ≥ 0)가 주어진다. 다음 G개 줄에는 묘비의 위치를 나타내는 두 정수 X와 Y가 주어진다. (0 ≤ X < W, 0 ≤ Y < H)

다음 줄에는 귀신 구멍의 수 E (E ≥ 0)가 주어진다. 다음 E개 줄에는 귀신 구멍의 정보를 나타내는 X1, Y1, X2, Y2, T 가 주어진다. (X1, Y1)은 귀신 구멍의 위치이고, (X2, Y2)는 그 귀신 구멍으로 들어갔을 때, 나오는 곳의 위치이다. (0 ≤ X1, X2 < W, 0 ≤ Y1, Y2 < H) (X1,Y1)과 (X2,Y2)가 같을 수도 있다. T는 귀신 구멍에서 나오는데 걸리는 시간이다. (-10,000 ≤ T ≤ 10,000) T가 양수인 경우에는 귀신 구멍을 들어간 이후에 나온다는 의미이다. 두 귀신 구멍이 같은 장소에 있거나, 구멍에서 나오는 지점이 묘비인 경우는 없다. 묘비와 귀신 구멍이 (0, 0)이나 (W-1, H-1)에 있는 경우는 없다.

입력의 마지막 줄에는 0 0이 주어진다.


> 출력

각 테스트 케이스 마다 상근이가 과거로 계속해서 돌아간다면 "Never"를 출력하고, 출구를 빠져나올 수 없으면 "Impossible"을 출력한다. 그 외의 경우에는 묘지를 빠져나오는데 가장 빠른 시간을 출력한다.


>유의

문제에서 우선되는 것은 Never의 출력이다. 즉, 도달할 수 없는 곳에서 과거로 계속 돌아가더라도 프로그램은 Never를 출력해야 한다.