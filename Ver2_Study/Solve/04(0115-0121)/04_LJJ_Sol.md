## 1256 사전
```java
import java.io.*;
import java.util.StringTokenizer;

public class Main {

    static double[][] dp;
    static BufferedWriter answer = new BufferedWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf.readLine());

        int N,M,K;
	    N = Integer.parseInt(st.nextToken());
	    M = Integer.parseInt(st.nextToken());
	    K = Integer.parseInt(st.nextToken());
        dp = new double[N + 1][M + 1];


        if(K>numWord(N,M)) {
            System.out.println("-1");
        }else {
            getWord(N,M,K-1);
        }
        answer.write("\n");
    answer.close();
    }
    static double numWord(int A, int Z){
        if(A==0||Z==0)
            return 1;
        if(dp[A][Z]!=0)
            return dp[A][Z];
        return dp[A][Z]= Double.min(numWord(A-1,Z)+numWord(A,Z-1), 1000000001);
    }

    static void getWord(int A, int Z, double before) throws IOException {
        if(A==0) {
            for (int i = 0; i < Z; i++)
                answer.write("z");
            return;
        }
        if(Z==0){
            for (int i = 0; i < A; i++) 
                answer.write("a");
            return;
            
        }
        double tmp = numWord(A-1, Z);

        if(before < tmp){
            answer.write("a");
            getWord(A-1,Z,before);
        }else {
            answer.write("z");
            getWord(A,Z-1,before-tmp);
        }
    }
}
```

## BJ16287 Parcel
```java
public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf.readLine());

        int w,n;
        w = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());

        int[] weight = new int[n];
        int[] dp = new int[799994 + 1];
        st = new StringTokenizer(bf.readLine());
        for (int i = 0; i < n; i++)
            weight[i] = Integer.parseInt(st.nextToken());

        Arrays.sort(weight);

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n ; j++) {
                int tmp = weight[i]+weight[j];
                if(tmp > w)
                    continue;
                dp[tmp] = j;
                if(dp[w-tmp]!= 0 && dp[w-tmp] > j){
                    System.out.println("YES");
                    return;
                }
            }
        }
        System.out.println("NO");
    }
}
```

## BJ7579 앱

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
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        int[] run,memory,dp;
        run = new int[N];
        memory = new int[N];


        st = new StringTokenizer(bf.readLine());
        int sum = 0;
        StringTokenizer st2 = new StringTokenizer(bf.readLine());
        for (int i = 0; i < N; i++) {
            run[i] = Integer.parseInt(st.nextToken());
            memory[i] = Integer.parseInt(st2.nextToken());
            sum += memory[i];
        }

        dp = new int[sum+1];
        for (int i = 0; i < N; i++) {
            for (int j = sum; j >= memory[i]; j--)
                dp[j] = Math.max(dp[j], dp[j-memory[i]]+run[i]);
        }

        for (int i = 0; i <= sum; i++) {
            if(dp[i] >= M) {
                System.out.println(i);
                break;
            }
        }
    }
}
```
## 책 페이지 1019

``` java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

    static int[] arr = new int[10];
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(bf.readLine());
        int pow =1 , start = 1;
        while(start <= n){
            while(n%10 != 9 && start <= n)
                check(n--,pow);

            if(n < start)
                break;

            while(start % 10 != 0 && start <= n)
                check(start++,pow);

            start/=10;
            n/=10;

            for (int i = 0; i < 10; i++)
                arr[i] += (n-start+1)*pow;

            pow *=10;
        }
        for (int i = 0; i < 10; i++) {
            System.out.printf("%d ",arr[i]);
        }
    }
    public static void check(int num, int point){
        while(num != 0){
            arr[num%10]+=point;
            num/=10;
        }
    }
}

```

