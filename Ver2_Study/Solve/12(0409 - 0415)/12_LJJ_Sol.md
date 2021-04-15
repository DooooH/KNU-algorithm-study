## [최소 스패닝 트리(BJ1197)](https://www.acmicpc.net/problem/1197)
```java
//kruskal
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int[] parent;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        int V = Integer.parseInt(st.nextToken());
        int E = Integer.parseInt(st.nextToken());
        parent = new int[V+1];
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }
        for (int i = 0; i < E; i++) {
            st = new StringTokenizer(br.readLine());
            pq.add(new Edge(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())));
        }
        int result = 0;
        for (int i = 0; i < E; i++) {
            Edge edge = pq.poll();
            int a = find(edge.start);
            int b = find(edge.end);

            if(a==b) continue;
            union(a, b);
            result += edge.weight;
        }
        System.out.println(result);

    }
    static int find(int a){
        if (a == parent[a])
            return a;
        return parent[a]=find(parent[a]);
    }
    static void union(int a, int b){
        int aRoot = find(a);
        int bRoot = find(b);

        if (aRoot != bRoot) {
            parent[aRoot]=b;
        }
    }
}
class Edge implements Comparable<Edge>{
    int start, end, weight;

    public Edge(int start, int end, int weight) {
        this.start = start;
        this.end = end;
        this.weight = weight;
    }

    @Override
    public int compareTo(Edge o) {
        return Integer.compare(this.weight, o.weight);
    }
}
```

```java
//prim
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Test {
    static int[] p;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        boolean[] visited = new boolean[N+1];
        PriorityQueue<Pair> pq = new PriorityQueue<>();
        ArrayList<Pair>[] adjlist = new ArrayList[N+1];
        for (int i = 1; i <=N ; i++) {
            adjlist[i] = new ArrayList<>();
        }
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            int w = Integer.parseInt(st.nextToken());
            adjlist[x].add(new Pair(y, w));
            adjlist[y].add(new Pair(x, w));
        }

        int ans = 0;
        int cnt = 0;
        pq.offer(new Pair(1, 0));

        while (!pq.isEmpty()){
            Pair p = pq.poll();
            if (!visited[p.x]) {
                visited[p.x] = true;
                ans += p.w;
                for (Pair pair : adjlist[p.x]) {
                    if (!visited[pair.x])
                        pq.offer(pair);
                }
                if (++cnt == N)
                    break;
            }
        }
        System.out.println(ans);
    }
    
}
class Pair implements Comparable<Pair>{
    int x,w;

    public Pair(int x, int w) {
        this.x = x;
        this.w = w;
    }

    @Override
    public int compareTo(Pair o) {
        return Integer.compare(this.w, o.w);
    }
}
```

## [이차원 배열과 연산(BJ17140)](https://www.acmicpc.net/problem/17140)
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    static int R, C, K;
    static short[][][] map, check, times;
    static boolean[][][] num;

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        map = new short[101][101][101];
        check = new short[101][101][101];
        times = new short[101][101][101];
        num = new boolean[101][101][101];
        for (int i = 1; i <= 3; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 1; j <= 3; j++) {
                map[0][i][j] = Short.parseShort(st.nextToken());
            }
        }
        int time = -1;
        int row, col;
        row = col = 3;
        while(++time <= 100){
            if(map[time][R][C] == K){
                System.out.println(time);
                return;
            }
            if(time == 100)
                break;
            if(row - col >= 0 )//R연산
            {
                for (int i = 1; i <= row; i++) {
                    for (int j = 1; j <= col; j++) {
                        check[time][i][map[time][i][j]]++;
                    }
                    for (int j = 1; j <= 100; j++) {
                        num[time][i][check[time][i][j]] = true;
                        times[time][i][check[time][i][j]]++;
                    }
                }
                int idx;
                int max = col;
                for (int i = 1; i <= row ; i++) {
                    idx = 1;
                    for (short j = 1; j < 100 && idx< 100; j++) {
                        if(num[time][i][j]){
                            int tmp = times[time][i][j];
                            for (short k = 1; k <= 100 && idx < 100; k++) {
                                if(check[time][i][k] == j)
                                {
                                    map[time+1][i][idx++] = k;
                                    map[time+1][i][idx++] = j;
                                    tmp--;
                                    if(tmp == 0 || idx > 100)
                                        break;
                                }
                            }
                        }
                    }
                    max = Math.max(max,idx-1);
                }
                col = max;
            }else
            {
                for (int i = 1; i <= col; i++) {
                    for (int j = 1; j <= row; j++) {
                        check[time][i][map[time][j][i]]++;
                    }
                    for (int j = 1; j <= 100; j++) {
                        num[time][i][check[time][i][j]] = true;
                        times[time][i][check[time][i][j]]++;
                    }
                }
                int idx;
                int max = row;
                for (int i = 1; i <= col ; i++) {
                    idx = 1;
                    for (short j = 1; j < 100 && idx < 100; j++) {
                        if(num[time][i][j]){
                            int tmp = times[time][i][j];
                            for (short k = 1; k <= 100&& idx < 100; k++) {
                                if(check[time][i][k] == j)
                                {
                                    map[time+1][idx++][i] = k;
                                    map[time+1][idx++][i] = j;
                                    tmp--;
                                    if(tmp == 0 || idx > 100)
                                        break;
                                }
                            }
                        }
                    }
                    max = Math.max(max,idx-1);
                }
                row = max;
            }
        }
        System.out.println("-1");
    }
}

```

## [여러 직사각형의 전체 면적 구하기(BJ2672)](https://www.acmicpc.net/problem/2672)
```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PriorityQueue<Square> pq = new PriorityQueue<>();
        StringTokenizer st;

        int N = Integer.parseInt(br.readLine());
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            int x = (int)(Double.parseDouble(st.nextToken())*10);
            int y = (int)(Double.parseDouble(st.nextToken())*10);
            int w = (int)(Double.parseDouble(st.nextToken())*10);
            int h = (int)(Double.parseDouble(st.nextToken())*10);
            pq.offer(new Square(x, y, y + h, 1));
            pq.offer(new Square(x+w, y, y + h, -1));
        }

        long ans = 0;
        int lx = 0;
        cnt = 0;
        int[] A = new int[10001];
        while (!pq.isEmpty()) {
            Square s = pq.poll();
            cnt = 0;
            for (int i = 0; i <= 10000; i++) {
                if(A[i]>0)
                    cnt++;
            }
            ans += cnt*(s.x - lx);
            for (int i = s.y1+1; i <= s.y2 ; i++) {
                if(s.check == 1) A[i]++;
                else A[i]--;
            }
            lx = s.x;
        }
        if(ans%100 == 0)
            System.out.println(ans / 100);
        else
            System.out.printf("%.2f", (double)ans/100);

    }
}
class Square implements Comparable<Square>{
    int x,y1,y2,check;

    public Square(int x, int y1, int y2, int check) {
        this.x = x;
        this.y1 = y1;
        this.y2 = y2;
        this.check = check;
    }

    @Override
    public int compareTo(Square o) {
        return Integer.compare(this.x, o.x);
    }
}
```

## 블록 이동하기
너무 로우하게 접근해서 시간이 더 오래 걸린 문제,
``` java
package com.company;

import java.util.LinkedList;
import java.util.Queue;

class Solution {
    static int[][] map;
    static boolean[][][] visited;
    static int[] dx = {1,-1,0,0};
    static int[] dy = {0,0,1,-1};
    static int size;
    public int solution(int[][] board) {

        size = board.length + 1;
        map = new int[size][size];
        visited = new boolean[2][size][size];
        Queue<Robot> queue = new LinkedList<>();
        for (int i = 1; i < size; i++) {
            for (int j = 1; j <size; j++) {
                map[i][j] = board[i - 1][j - 1];
            }
        }

        queue.offer(new Robot(1, 1, 1, 2, 0, 0));
        visited[0][1][1] = true;
        visited[0][1][2] = true;
        int answer = 0;
        while (!queue.isEmpty()) {
            Robot robot = queue.poll();
            if((robot.s1_x == size-1 && robot.s1_y == size-1) || (robot.s2_x == size-1 && robot.s2_y == size-1))
            {
                   answer = robot.time;
                   break;
            }
                //line
                for (int i = 0; i < 4; i++) { // 아래 위 우 좌
                    int nx1 = robot.s1_x + dx[i];
                    int ny1 = robot.s1_y + dy[i];
                    int nx2 = robot.s2_x + dx[i];
                    int ny2 = robot.s2_y + dy[i];

                    if(bcheck(nx1,ny1,nx2,ny2)){ // boundary Okay
                        if(!visited[robot.tilt][nx1][ny1]  || !visited[robot.tilt][nx2][ny2] ){
                            visited[robot.tilt][nx1][ny1] = true;
                            visited[robot.tilt][nx2][ny2] = true;
                            queue.offer(new Robot(nx1, ny1, nx2, ny2, robot.tilt, robot.time + 1));
                        }
                    }
                }
                //rotate
            for (int i = -1; i <2 ; i+=2) {
                int nx1 = robot.s1_x;
                int ny1 = robot.s1_y;
                int nx2 = robot.s2_x;
                int ny2 = robot.s2_y;
                if(robot.tilt == 0) // 가로
                {
                    nx1 += i;
                    nx2 += i;
                }
                else {
                    ny1 += i;
                    ny2 += i;
                }
                if(bcheck(nx1,ny1,nx2,ny2)){
                    if (!visited[Math.abs(robot.tilt-1)][nx1][ny1] || !visited[Math.abs(robot.tilt-1)][robot.s1_x][robot.s1_y]) {
                        visited[Math.abs(robot.tilt-1)][nx1][ny1] = true;
                        visited[Math.abs(robot.tilt-1)][robot.s1_x][robot.s1_y] = true;
                        queue.offer(new Robot(nx1, ny1, robot.s1_x, robot.s1_y,  Math.abs(robot.tilt-1),robot.time+1 ));
                    }
                    if(!visited[Math.abs(robot.tilt-1)][nx2][ny2] || !visited[Math.abs(robot.tilt-1)][robot.s2_x][robot.s2_y]){
                        visited[Math.abs(robot.tilt-1)][nx2][ny2] = true;
                        visited[Math.abs(robot.tilt-1)][robot.s2_x][robot.s2_y] = true;
                        queue.offer(new Robot(nx2, ny2, robot.s2_x, robot.s2_y, Math.abs(robot.tilt-1), robot.time + 1));
                    }
                }

            }

        }

        return answer;
    }
    static boolean bcheck(int nx1, int ny1, int nx2, int ny2){
        if (nx1 > 0 && ny1 > 0 && nx2 > 0 && ny2 > 0 && nx1 < size && nx2 < size && ny1 < size && ny2 < size && map[nx1][ny1] == 0 && map[nx2][ny2]==0)
            return true;
        return false;

    }
}
class Robot {
    int s1_x, s1_y, s2_x, s2_y, tilt, time;

    public Robot(int s1_x, int s1_y, int s2_x, int s2_y, int tilt, int time) {
        this.s1_x = s1_x;
        this.s1_y = s1_y;
        this.s2_x = s2_x;
        this.s2_y = s2_y;
        this.tilt = tilt;
        this.time = time;
    }
}

```