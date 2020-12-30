## 두 용액(BJ2470)
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
이 문제는 **Two Poninter**  관련 문제로 빈출 유형이라고 함.
유사문제 백준 [세용액](https://www.acmicpc.net/problem/2473), 프로그래머스 [보석 쇼핑](https://programmers.co.kr/learn/courses/30/lessons/67258) 풀어보는 것 추천

---



## 진법변환(BJ1112)
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
## 러버덕을 사랑하는 모임 (BJ18223)
```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {

    static int N,P,E;
    static ArrayList<member> list;
    static boolean flag = false;
    static boolean[] visited;
    public static void main(String[] args) throws IOException {

        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf.readLine());
        N = Integer.parseInt(st.nextToken());
        P = Integer.parseInt(st.nextToken());
        E = Integer.parseInt(st.nextToken());
        list = new ArrayList<>(N);
        visited = new boolean[N];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(bf.readLine());
            list.add(new member(Integer.parseInt(st.nextToken()),Integer.parseInt(st.nextToken())));
        }
        combination(new ArrayList<Integer>(),0);

        if(!flag)
            System.out.println("-1");

    }
    public static void find(ArrayList<Integer> picked, int min){
        int tmp = E;
        int[] sol = new int[N];
        for (int i = 0; i < P; i++)
            sol[picked.get(i)] = list.get(picked.get(i)).min;

        tmp -= min;

        for (int i = 0; i < P; i++) {
            int term = list.get(picked.get(i)).max - list.get(picked.get(i)).min;
            if (term <= tmp){
                sol[picked.get(i)] += term;
                tmp -=term;
            }
            else{
                sol[picked.get(i)]+=tmp;
                tmp = 0;
            }
        }
        StringBuilder st = new StringBuilder();
        for (int i = 0; i < N; i++) {
            st.append(sol[i]+" ");
        }
        System.out.println(st);
    }
    public static void combination(ArrayList<Integer> picked,int start){
        if(flag)
            return;
        if(picked.size() == P) {// 조합 완료 -> 체크 해야함.
            int min=0,max=0;
            for (int i = 0; i < P; i++) {
                min += list.get(picked.get(i)).min;
                max += list.get(picked.get(i)).max;
            }
            if(min<=E && max>=E) {
                flag = true;
                find(picked, min);
            }
            return;
        }
        for (int i = start; i <N ; i++) {//조합 만들기.
            picked.add(i);
            combination(new ArrayList<Integer>(picked),i+1);
            picked.remove(picked.size()-1);
        }
    }
}

class member{
    int min, max;
    public member(int min, int max){
        this.max = max;
        this.min = min;
    }
}
```

## 부분평균 BJ14922
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(bf.readLine());
        StringTokenizer st = new StringTokenizer(bf.readLine());
        double[] list = new double[N];
        double avg ;
        int idx = 0;

        list[0] =  Integer.parseInt(st.nextToken());
        list[1] =  Integer.parseInt(st.nextToken());
        avg = list[0] + list[1];
        for (int i = 2; i < N; i++) {
            list[i] =  Integer.parseInt(st.nextToken());
            if(avg>list[i] && avg > (list[i-1]+list[i])){
                avg = list[i-1]+list[i];
                idx = i-1;
            }
        }
        avg/=2;

        if(N!=2){
            for (int i = 2; i < N ; i++) { // 구간 3
                double tmp = (list[i-2] + list[i-1] + list[i])/3;
                if(tmp <= avg){
                    avg = tmp;
                    if(idx >= i-2)
                        idx = i-2;
                }
            }
        }
        System.out.println(idx);
    }
}
```