# 두 용액(BJ2470)
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {

        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(bf.readLine());
        StringTokenizer st = new StringTokenizer(bf.readLine());
        int start=0,end=N-1,sum=0,L=0,R=N-1,least;
        int[] arr = new int[N];
        for (int i = 0; i < N; i++)
            arr[i] = Integer.parseInt(st.nextToken());

        Arrays.sort(arr);
        sum = arr[start]+arr[end];
        least = sum;
        while(start!=end){
            if(Math.abs(least)>Math.abs(sum)){
                least = sum;
                L = start; R = end;
            }
            if(sum>0){
                sum =sum - arr[end--] + arr[end];
            }
            else {
                sum = sum - arr[start++] + arr[start];
            }

        }

        System.out.println(arr[L]+" "+arr[R]);
    }
}
```
이 문제는 **Two Poninter**  관련 문제로 빈출 문제라고 함.
유사문제 백준 [세용액](https://www.acmicpc.net/problem/2473), 프로그래머스 [보석 쇼핑](https://programmers.co.kr/learn/courses/30/lessons/67258) 풀어보는 것 추천

---



# 진법변환(BJ1112)
``` java

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {

        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf.readLine());
        int N = Integer.parseInt(st.nextToken());
        int b = Integer.parseInt(st.nextToken());
        int i =0;

        boolean flag = false;
        int[] invert = new int[999];
        Arrays.fill(invert, Integer.MAX_VALUE);
        if(N ==0) {
            System.out.println(0);
        return;
        }
        if(b>0){ // 양수 진법일때 그냥 진법 변환 함.
            if(N<0){
                N*=-1;
                flag =true;
            }
            while (N!=0){
                invert[i++] = N%b;
                N/=b;
            }
        }else {//음수 진법
            int ab = Math.abs(b);
            while (N != 0) {
                int p = N % b;
                if(p>=0){
                    invert[i++] = p;
                    N/=b;
                }else {
                    invert[i++] = (p + ab)%ab;
                    N/=b;
                    N++;
                }
            }
        }
        StringBuilder sb = new StringBuilder();
        if(flag)
            sb.append("-");
        for (int j = --i; j >= 0; j--) {
            sb.append(invert[j]);
        }
        System.out.println(sb);
    }
}
```