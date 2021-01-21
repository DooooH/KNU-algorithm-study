
# 앱

```JAVA
import java.io.*;
import java.util.*;

public class App_01 {
	
	static int num_item = 0;	//number of items from the file
	static int M = 0;
	static int total_cost = 0;
	
	
	static int[] mem;
	static int[] cost;
	static int[][] DP;
	
	public static void read()
	{
	   	Scanner sc = null;	//scanner initialization
	   	
	   	try {
				//sc = new Scanner(new File("d:\\Users\\USER\\desktop\\input.txt"));//input file directory here
				sc = new Scanner(new File("C:\\Users\\김지수\\Desktop\\input.txt"));//input file directory here
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	   		num_item = sc.nextInt();
	   		M = sc.nextInt();
	   		mem = new int[num_item + 1];
	   		cost = new int[num_item + 1];
	   	 for (int i = 1; i <= num_item; i++)//reading points from file
	   	{
	   		mem[i] = sc.nextInt();
	   		//System.out.println(mem[i]);
	   	}
	   	 for (int i = 1; i <= num_item; i++)//reading points from file
	   	{
	   		cost[i] = sc.nextInt();
	   		//System.out.println(cost[i]);
	   		total_cost+=cost[i];
	   	} 
	}
	
	public static void solve()
	{
		DP = new int[num_item+1][total_cost+1];
		
		for(int i = 1; i<=num_item; i++)
		{
			for(int j = 0; j <=total_cost; j++)
			{
//				 if (i==0 || j==0) 
	//				 DP[i][j] = 0; 
	//	           else
		        	   if (cost[i] <= j) 
		        	   DP[i][j] = Math.max(mem[i] + DP[i-1][j-cost[i]],  DP[i-1][j]); 
		           else
		        	   DP[i][j] = DP[i-1][j]; 
			}
		}
		int Ans = 0;
		boolean exit = false;
		for(int j = 0; j <=total_cost; j++)
		{	for(int i = 0; i<=num_item; i++)
			{
				if(DP[i][j] >= M)
				{Ans = j;
			  exit = true;}
			}
		if(exit) break;
		}
	
		System.out.println(Ans);
	}
	public static void main(String[] args) {	
	   	
	   read();
	   solve();
	}
}

```
***
# 사전

```C++
#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000000000
#include <stdio.h>
#include <stdlib.h>

int DP[201][201];
void calc(int n)
{
	DP[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		DP[i][0] = 1;
		DP[i][i] = 1;
	}
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
			if (DP[i][j] > MAX) 
				DP[i][j] = MAX;
		}
	}
}

int main(void)
{
	int n, m, k;
	int N, R;
	scanf("%d%d%d", &n, &m, &k);
	calc(n + m);

	k--;
	if (DP[n + m][m] <= k)
	{
		printf("-1"); 
		return 0;
	}
	for (int i = m + n - 1; i >= 0; i--)
	{
	
		if (i >= m && DP[i][m] > k)
			putchar('a');
		else 
		{
			putchar('z');
			k -= DP[i][m]; 
			m--;
		}
	}
	putchar('\n');

}
```
***
# Parcel

```C++
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
int visited[800000];
int item[5000];
int main(void)
{
	int W, N,i,j;
	scanf("%d %d", &W, &N);
	for (i = 0; i < N; i++)
		scanf("%d", &item[i]);

	for (i = 0; i < N; i++)
	{
		for (j = i + 1; j < N; j++)
		{
			if (item[i] + item[j] < W)
			{

				if (visited[W - item[i] - item[j]])
				{
					printf("YES");
					return 0;
				}
			}
		}
		for (j = 0; j < i; j++)
		{
			if (item[i] + item[j] < W)
				visited[item[i] + item[j]] = 1;
		}
	}
	printf("NO");
	return 0;
}

```
***
