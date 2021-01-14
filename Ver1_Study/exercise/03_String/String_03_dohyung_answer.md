## 문자열 뽑기 8913

```c++
#include <bits/stdc++.h>
using namespace std;

vector<string> dp;
vector<string> tests;

void get_status(vector<int> status[], string test)
{
	if (test.length() == 0)
		return ;
	char std;
	const char *str = test.c_str();
	if (str[0] == 'a')
		std = 'a';
	else
		std = 'b';
	int i = 0;
	while (str[i])
	{
		int count = 0;
		while (std == str[i])
		{
			i++;
			count++;
		}
		if (count != 0)
			status[0].push_back(count);
		if (str[i] == 'a')
			std = 'a';
		else if (str[i] == 'b')
			std = 'b';
	}
}

void cumulative(vector<int> status[])
{
	if (status[0].size() == 0)
		return ;
	for (int i = 0; i < status[0].size(); i++)
	{
		if (i == 0)
			status[1].push_back(status[0][i]);
		else
			status[1].push_back(status[0][i - 1] + status[0][i]);
	}
}

int recursion(string test)
{
	vector<int> status[2];
	string temp;
	if (test.length() == 0)
	{
		return (1);
	}
	get_status(status, test);
	cumulative(status);
	for (int i = 0; i < status[0].size(); i++)
	{
		int ret;
		temp = test;
		if (status[0][i] != 1)
		{
			if (i == 0)
				temp.erase(0, status[0][i]);
			else
				temp.erase(status[1][i - 1], status[0][i]);
			if (find(dp.begin(), dp.end(), temp) != dp.end())
				ret = 0;
			else
				ret = recursion(temp);
			if (ret == 1)
				return (1);
			dp.push_back(temp);
		}
	}
	return (0);
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n;
	string temp;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		tests.push_back(temp);
	}
	for (int i = 0; i < n; i++)
	{
		cout << recursion(tests[i]) << "\n";
	}
	return (0);
}
```
