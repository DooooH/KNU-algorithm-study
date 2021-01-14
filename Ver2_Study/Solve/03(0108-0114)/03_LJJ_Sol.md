BJ13334 철로
```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(bf.readLine());
        Pair[] pairs = new Pair[n];
        StringTokenizer st;
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(bf.readLine());
            pairs[i] = new Pair(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
        }
        int d = Integer.parseInt(bf.readLine());
        int max = 0;
        Arrays.sort(pairs);

        for (int i = 0; i < n; i++) {
            pq.offer(pairs[i].h);
            while(!pq.isEmpty() && (pq.peek()<(pairs[i].o-d))) {
                pq.poll();
            }
            max = Math.max(max, pq.size());
        }
        System.out.println(max);
    }
}

class Pair implements Comparable<Pair> {
    int h, o;
    public Pair(int h, int o) {
        if(h>o){
            this.o = h;
            this.h = o;
        }
        else {
            this.h = h;
            this.o = o;
        }
    }
    @Override
    public int compareTo(Pair o) {
        if (this. o< o.o)
            return -1;
        else if (this.o == o.o)
            if (this.h > o.h)
                return -1;
            else if (this.h == o.h)
                    return 0;
        return 1;
    }
}


```

## 9376번 탈옥
```java
package com.company;

import java.io.*;
import java.util.*;

public class Main {
    static int h,w;
    static int[] dx = {1,0,-1,0};// 우,상,좌,하
    static int[] dy = {0,1,0,-1};
    static char[][] prison;

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        int n = Integer.parseInt(bf.readLine());
        int[][] p1,p2,p3;

        for (int i = 0; i < n; i++) {
            int admin = 0;
            int min =Integer.MAX_VALUE;
            st = new StringTokenizer(bf.readLine());
            h = Integer.parseInt(st.nextToken())+2;
            w = Integer.parseInt(st.nextToken())+2;
            prison = new char[h][w];
            Queue<Pair> member = new LinkedList<>();
            Arrays.fill(prison[0],'.');
            Arrays.fill(prison[h-1],'.');

            for (int j = 1; j < h-1; j++) {
                prison[j][0] = prison[j][w-1] = '.';
                char[] tmp = bf.readLine().toCharArray();
                for (int k = 1; k < w-1; k++) {
                    prison[j][k] = tmp[k - 1];
                    if(prison[j][k] == '$') {
                        member.offer(new Pair(j, k, 0));
                    }
                }
            }
            p1 = BFS(new Pair(0, 0, 0));
            p2 = BFS(member.poll());
            p3 = BFS(member.poll());

            for (int j = 0; j < h; j++) {
                for (int k = 0; k < w; k++) {
                    if (prison[j][k] == '*' || p1[j][k] == -1)
                        continue;
                    int sum = p1[j][k] + p2[j][k] + p3[j][k];
                    if(prison[j][k] == '#')
                        sum-=2;
                    min = Integer.min(min, sum);
                }
            }
            bw.write(min+"\n");
        }
        bw.close();
    }
    static int[][] BFS(Pair pair){
        int[][] visited = new int[h][w];
        for (int i = 0; i < h; i++) {
            Arrays.fill(visited[i], -1);

        }

        PriorityQueue<Pair> pq = new PriorityQueue<>();
        pq.offer(pair);
        visited[pair.x][pair.y] = 0;
        while (!pq.isEmpty()){
            Pair tmp = pq.poll();

            for (int j = 0; j < 4; j++) {
                int nx = tmp.x + dx[j];
                int ny = tmp.y + dy[j];
                int cost = tmp.cost;
                if(nx >= 0 && ny >= 0 && nx < h && ny < w && prison[nx][ny] != '*' ){
                      if (prison[nx][ny] == '#')
                          cost++;
                      if(visited[nx][ny] == -1 || visited[nx][ny]>cost) {
                          visited[nx][ny] = cost;
                          pq.offer(new Pair(nx, ny, cost));
                      }
                }
            }
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                System.out.printf("%3d",visited[i][j]);
            }
            System.out.println(" ");
        }
        System.out.println(" ");
        return visited;
    }
}

class Pair implements Comparable<Pair>{

    int x,y;
    int cost = 0;

    public Pair(int x, int y, int cost) {
        this.x = x;
        this.y = y;
        this.cost = cost;

    }

    @Override
    public int compareTo(Pair o) {
        return Integer.compare(this.cost, o.cost);
    }
}
```

## 보석쇼핑
```java
int[] answer = new int[2];
        HashMap<String, Integer> map = new HashMap<>();
        for (String tmp : gems) {
                map.put(tmp,0);
        }
        int size = map.size();
        int cnt = 0;
        int start, end;
        int min_length, min_start, min_end;
        min_length = min_end = min_start = Integer.MAX_VALUE;
        start = end = 0;
        while (start<gems.length || end < gems.length) {

            if(cnt >= size && start <= end){
                map.replace(gems[start], map.get(gems[start]) - 1);
                if (map.get(gems[start]) == 0) {
                    cnt--;
                }

                start++;
            }else if(cnt < size && end < gems.length){
                map.replace(gems[end], map.get(gems[end]) + 1);
                if(map.get(gems[end])==1)
                    cnt++;
                end++;
            }
            if(cnt == size){
                if(min_length > end - start -1){
                    min_length = end - start -1;
                    min_start = start;
                    min_end = end-1;
                }
                else if(min_length == end -start -1){
                    if(start<min_start){
                        min_start = start;
                        min_end = end-1;
                    }
                }
            }
            if(end == gems.length && cnt < size)
            break;
        }
        answer[0] = min_start + 1;
        answer[1] = min_end + 1;


     return answer;
```