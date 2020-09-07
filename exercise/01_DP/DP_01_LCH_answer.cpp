#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

#define INF 99999999

using namespace std;

int c, n;
int dp[1201];
pair<int, int> city[21];
vector<int> over;

int getmin(int a, int b) { return a > b ? b : a; }

int main() {
	cin >> c >> n;

	for (int i = 1; i <= n; i++) {
		int cost, people;
		cin >> cost >> people;
		city[i] = { cost, people };
	}

	fill(dp, dp + c + 200, INF);
	dp[0] = 0;

	//������ '���'��� ������ �پ����Ƿ� Bottom-Up ����� ����ϴ� ���� �����ϴ�.
	for (int i = 0; i < c; i++) {
		if (dp[i] == INF) continue;
		for (int j = 1; j <= n; j++) {
			int& curdp = dp[i + city[j].second];
			curdp = getmin(dp[i] + city[j].first, curdp);
			//����ġ�� �ʰ��ϴ� �ε����鸸 ���� ��Ƽ� ���������� ��
			if (i + city[j].second >= c) over.push_back(i + city[j].second);
		}
	}

	int result = INF;
	for (int i = 0; i < over.size(); i++) {
		result = getmin(result, dp[over[i]]);
	}

	printf("%d\n", result);

	return 0;
}
