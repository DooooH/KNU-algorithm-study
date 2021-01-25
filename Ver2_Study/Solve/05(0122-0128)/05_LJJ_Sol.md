## BJ1111 IQ 테스트
예외가 생각보다 많았던 문제.
n이 1인 경우, 수열이 같은 경우, 0으로 나눌 수 없는 경우 등등이 있음
```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int N = Integer.parseInt(bf.readLine());
        if(N==1)
        {
            System.out.println("A");
            return;
        }
        int[] list = new int[N+1];
        Queue<Pair> queue = new LinkedList<>();

        st = new StringTokenizer(bf.readLine());
        for (int i = 0; i < N; i++) {
            list[i] = Integer.parseInt(st.nextToken());
        }
        for (int i = -1000; i < 1000; i++) {
                queue.offer(new Pair(i,list[1] - (list[0]*i)));
        }
        for (int i = 1; i < N-1; i++) {
            int size = queue.size();
            for (int j = 0; j < size; j++) {
                Pair pair = queue.poll();
                if((list[i]*pair.a + pair.b) == list[i+1])
                    queue.offer(pair);
            }
        }
        if(queue.isEmpty())
            System.out.println("B");
        else {
            Pair pair = queue.poll();
            int answer = list[N-1]*pair.a + pair.b;
            while(!queue.isEmpty()) {
                Pair tmp = queue.poll();
                int value = list[N-1]*tmp.a + tmp.b;
                if(value != answer){
                    System.out.println("A");
                    return;
                }
            }
            System.out.println(answer);
        }

    }
}
class Pair{
    int a, b;

    public Pair(int a, int b) {
        this.a = a;
        this.b = b;
    }
}
```
## SNS 

내가 얼리어답터가 아니면 모두가 얼리어답터이다.
```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
    static ArrayList<Integer>[] list;
    static boolean[] earlyAdapter,visited;
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(bf.readLine());
        StringTokenizer st;
        list = new ArrayList[N+1];
        earlyAdapter = new boolean[N+1];
        visited = new boolean[N+1];

        for (int i = 0; i <= N; i++) {
            list[i] = new ArrayList<>();
        }

        for (int i = 0; i < N-1; i++) {
            st = new StringTokenizer(bf.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            list[u].add(v);
            list[v].add(u);
        }
        visited[1] = true;
        DFS(1);
        int cnt = 0;
        for (int i = 1; i <= N; i++) {
            if(earlyAdapter[i])
                cnt++;
        }
        System.out.println(cnt);
    }
    static boolean DFS(int node) {
        for (int i = 0; i < list[node].size(); i++) {
            int next = list[node].get(i);
            if(!visited[next]){
                visited[next] = true;
                boolean tmp = DFS(next);
                if(earlyAdapter[node] == tmp)
                    earlyAdapter[node]=true;
            }
        }
        return earlyAdapter[node];
    }
}

```

## 칵테일

```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    static LinkedList<Pair>[] adjlist;
    static long[] answer;
    static boolean[] visited;
    static int N;

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        N = Integer.parseInt(bf.readLine());
        adjlist = new LinkedList[N];
        answer = new long[N];
        visited = new boolean[N];
        if (N==1) {
            System.out.println(1);
            return;
        }
        for (int i = 0; i < N; i++) {
            adjlist[i] = new LinkedList<>();
        }
        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(bf.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int p = Integer.parseInt(st.nextToken());
            int q = Integer.parseInt(st.nextToken());
            
            adjlist[a].add(new Pair(b, p, q));
            adjlist[b].add(new Pair(a, q, p));
        }
        for (int i = 0; i < N; i++) {
            update(i);
        }

        long gcd = answer[0];
        for (int i = 1; i < N; i++) {
            gcd = GCD(Math.max(gcd, answer[i]), Math.min(gcd, answer[i]));
        }
        for (long i : answer)
            System.out.printf("%d ", i / gcd);
    }

    public static long GCD(long a, long b) {
        return a % b == 0 ? b : GCD(b, a % b);
    }

    public static long LCM(long a, long b) {
        return a * b / (GCD(Math.max(a, b), Math.min(a, b)));
    }

    public static void update(int start) {
        Queue<Pair> queue = new LinkedList<>();
        long lcm = answer[start] == 0 ? 1 : answer[start];
        for (Pair pair : adjlist[start]) {
            lcm = LCM(lcm, pair.p);
            queue.offer(pair);
        }

        if (answer[start] != 0 && answer[start] < lcm) { // 다 곱해줘야함.
            long pow = lcm / answer[start];
            for (int i = 0; i < N; i++) {
                if (answer[i] != 0)
                    answer[i] *= pow;
            }
        }
        while (!queue.isEmpty()) {
            Pair tmp = queue.poll();
            if (visited[tmp.b])
                continue;

            if (answer[start] == 0)
                answer[start] = lcm;

            answer[tmp.b] = (answer[start] * tmp.q) / tmp.p;
            visited[start] = true;
            update(tmp.b);
        }
    }
}

class Pair {
    int p, q, b;
    public Pair(int b, int p, int q) {
        this.p = p;
        this.q = q;
        this.b = b;
    }
}
```