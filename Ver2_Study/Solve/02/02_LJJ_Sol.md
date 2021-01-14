## 최솟값 BJ10868번
이 문제는 Segment-Tree와 관련된 문제임!
```java
import java.io.*;
import java.util.StringTokenizer;

public class Main {
        static long[] arr,tree;
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(bf.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        arr = new long[N+1];
        tree = new long[4*N];

        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(bf.readLine());
        }initTree(0,N-1,1);

        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(bf.readLine());
            bw.write(searchTree(0,N-1,1,Integer.parseInt(st.nextToken())-1,Integer.parseInt(st.nextToken())-1)+"\n");
        }
        bw.close();
    }
    public static long initTree(int start, int end, int index){
        if(start == end)
            return  tree[index] = arr[start];
        else{
            int mid = (start+end)/2;
            return tree[index] = Long.min(initTree(start,mid,index*2),initTree(mid+1,end,index*2+1));
        }
    }
    public static long searchTree(int start, int end, int index, int left, int right){
        if(start > right || end < left){
            return Integer.MAX_VALUE;
        }
        if(start>=left && end <= right){
            return tree[index];
        }
        int mid = (start + end)/2;

        return Long.min(searchTree(start,mid,index*2,left,right),searchTree(mid+1,end,index*2+1,left,right));

    }
}
```

## 2096번 내려가기
메모리랑 시간 제한 보고 괜히 겁먹고 시간 오래걸림;;
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    static int N;
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(bf.readLine());
        StringTokenizer st = new StringTokenizer(bf.readLine());
        int[] input = new int[3];
        int[][] dp = new int[N][6];
        for (int i = 0; i < 3; i++)
            input[i] = Integer.parseInt(st.nextToken());
        for (int i = 0; i < 3; i++) {
            dp[0][3 + i] = dp[0][i] = input[i];
        }

        for (int k = 1; k < N; k++) {
            st = new StringTokenizer(bf.readLine());
            for (int j = 0; j < 3; j++)
                input[j] = Integer.parseInt(st.nextToken());
            int i = k-1;
            dp[k][0] = Integer.min(dp[i][0], dp[i][1]) + input[0];
            dp[k][1] = Integer.min(dp[i][0], Integer.min(dp[i][1], dp[i][2])) + input[1];
            dp[k][2] = Integer.min(dp[i][1], dp[i][2]) + input[2];

            dp[k][3] = Integer.max(dp[i][3], dp[i][4]) + input[0];
            dp[k][4] = Integer.max(dp[i][3], Integer.max(dp[i][4], dp[i][5])) + input[1];
            dp[k][5] = Integer.max(dp[i][4], dp[i][5]) + input[2];
        }

        Arrays.sort(dp[N-1]);
        System.out.printf("%d %d",dp[N-1][5],dp[N-1][0]);

    }
}
```
## 2560 짚신벌레
```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {

        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf.readLine());
        int start = Integer.parseInt(st.nextToken());
        int end = Integer.parseInt(st.nextToken());
        int death = Integer.parseInt(st.nextToken());
        int N = Integer.parseInt(st.nextToken());

        int[] dp = new int[N+1];
        dp[0] = 1;

        for (int i = 1; i <= N; i++) {
            if (i<start) // 시작날 전까지 유지됨.
                dp[i] = dp[i-1]%1000;
            else if(i<end) // 단순하게 증가함! 전날 + 새로 태어남
                dp[i] = (dp[i-1] + dp[i-start])%1000;
            else
                dp[i] = (dp[i-1]+dp[i-start]-dp[i-end]+1000)%1000;
        }

        if(N-death>=0)
            System.out.println((dp[N]-dp[N-death]+1000)%1000);
        else System.out.println(dp[N]%1000);

    }
}
```