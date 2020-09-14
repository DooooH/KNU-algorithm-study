#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;
int n;
long long value[123457];
vector<int> tree[123457];

long long dfs(int node) {
	long long retval = 0;

	for (int i = 0; i < tree[node].size(); i++) {
		retval += dfs(tree[node][i]);
	}
	retval += value[node];
	if (retval < 0) retval = 0;

	return retval;
}

void init() {
	char c;
	cin >> n;

	for (int i = 2; i <= n; i++) {
		int val, path;
		cin >> c >> val >> path;
		if (c == 'W') value[i] = -1 * val;
		else value[i] = val;
		tree[path].push_back(i);
	}
}

int main() {
	init();
	long long answer = dfs(1);
	printf("%ld\n", answer);

	return 0;
}
