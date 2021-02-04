# 개미굴

-MAP
-VECTOR
-범위기반 Loop


```c++
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<string>
#include<map>
#include<vector>

using namespace std;

map<string, int> trie[10000]; // string을 key로 두어 자동 정렬

int trie_size;// trie size 저장용

void insert(const vector<string>& vs) 
{
	int node = 0;
	for (int i = 0; i < vs.size(); i++) 
	{
		if (trie[node].find(vs[i]) == trie[node].end())  //삽입되지 않은 string
		{
			trie[node][vs[i]] = ++trie_size; // 새로운 string 삽입 및 생성
			node = trie_size; 
		}
		else
			node = trie[node][vs[i]]; //존재한다면 해당 위치로 이동
	}
}

void print_trie(int node, int depth) // preorder 출력
{
	for (auto iter = trie[node].begin(); iter != trie[node].end(); ++iter) {
		for (int i = 0; i < depth * 2; i++) // depth*2만큼 - 출력
		{
			cout << '-';
		}
		cout << iter->first << '\n';

		print_trie(iter->second, depth + 1);
	}
}

int main(void)
{
	int num_query; // 개미수
	int depth; // 각 string depth

	cin >> num_query;
	for (int i = 0; i < num_query; i++)
	{
		cin >> depth;
			vector<string> v(depth); //depth크기만큼 선언
			for (int k = 0; k < depth; k++)
				cin >> v[k];
			
			insert(v);//vector단위 insert
	}
	print_trie(0, 0);
}
```
***
