## 달빛 여우

``` java
// https://www.acmicpc.net/problem/16118
// 20.11.11. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

class stump implements Comparable<stump> {
    int pos;
    int dist;
    boolean run;

    public stump(int pos, int dist) {
        this.pos = pos;
        this.dist = dist;
        this.run = true;
    }

    public stump(int pos, int dist, boolean run) {
        this.pos = pos;
        this.dist = dist;
        this.run = run;
    }

    public int compareTo(stump o) {
        return Integer.compare(this.dist, o.dist);
    }
}

public class BOJ16118 {
    public static void solution() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        ArrayList<stump>[] al = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++)
            al[i] = new ArrayList<>();

        while(m-- > 0) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int d = Integer.parseInt(st.nextToken())*2;
            al[a].add(new stump(b, d));
            al[b].add(new stump(a, d));
        }

        int[] fox = new int[n+1];
        int[][] wolf = new int[2][n+1];
        Arrays.fill(fox, Integer.MAX_VALUE);
        Arrays.fill(wolf[0], Integer.MAX_VALUE);
        Arrays.fill(wolf[1], Integer.MAX_VALUE);
        fox[1] = 0;
        wolf[0][1] = 0;

        PriorityQueue<stump> fpq = new PriorityQueue<>();
        fpq.offer(new stump(1, 0));
        while(!fpq.isEmpty()) {
            stump cur = fpq.poll();
            for (stump i : al[cur.pos]) {
                int newDist = cur.dist+i.dist;
                if (fox[i.pos] > newDist) {
                    fox[i.pos] = newDist;
                    fpq.offer(new stump(i.pos, newDist));
                }
            }
        }
        PriorityQueue<stump> wpq = new PriorityQueue<>();
        wpq.offer(new stump(1, 0));
        while(!wpq.isEmpty()) {
            stump cur = wpq.poll();
            for (stump i : al[cur.pos]) {
                int newDist = cur.dist;
                if (cur.run) {
                    newDist += i.dist / 2;
                    if (wolf[1][i.pos] > newDist) {
                        wolf[1][i.pos] = newDist;
                        wpq.offer(new stump(i.pos, newDist, false));
                    }
                } else {
                    newDist += i.dist * 2;
                    if (wolf[0][i.pos] > newDist) {
                        wolf[0][i.pos] = newDist;
                        wpq.offer(new stump(i.pos, newDist, true));
                    }
                }
            }
        }
        int answer = 0;
        for (int i = 2; i <= n; i++) {
            if (fox[i] < Math.min(wolf[0][i], wolf[1][i]))
                answer++;
        }
        System.out.println(answer);
    }
}
```



## 해킹

``` java
// https://www.acmicpc.net/problem/10282
// 20.11.11. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

class dep implements Comparable<dep> {
    int comp;
    int time;

    public dep(int comp, int time) {
        this.comp = comp;
        this.time = time;
    }

    public int compareTo(dep o) {
        return Integer.compare(this.time, o.time);
    }
}

public class BOJ10282 {
    public static void solution() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();
        while(t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int d = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            ArrayList<dep>[] al = new ArrayList[n + 1];
            for (int i = 1; i <= n; i++)
                al[i] = new ArrayList<>();

            while(d-- > 0) {
                st = new StringTokenizer(br.readLine());
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());
                int s = Integer.parseInt(st.nextToken());
                al[b].add(new dep(a, s));
            }

            int[] infected = new int[n + 1];
            Arrays.fill(infected, Integer.MAX_VALUE);
            infected[c] = 0;
            PriorityQueue<dep> pq = new PriorityQueue<>();
            pq.offer(new dep(c, 0));
            while(!pq.isEmpty()) {
                dep cur = pq.poll();
                for (dep i : al[cur.comp]) {
                    int newTime = cur.time + i.time;
                    if (infected[i.comp] > newTime) {
                        infected[i.comp] = newTime;
                        pq.offer(new dep(i.comp, newTime));
                    }
                }
            }

            int cnt = 0;
            int max = 0;
            for (int i : infected) {
                if (i == Integer.MAX_VALUE) continue;
                cnt++;
                max = Math.max(max, i);
            }
            sb.append(cnt).append(' ').append(max).append('\n');
        }
        System.out.print(sb);
    }
}
```



## 최단경로

``` java
// https://www.acmicpc.net/problem/1753
// 20.11.11. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

class path implements Comparable<path> {
    int pos;
    int dist;

    public path(int pos, int dist) {
        this.pos = pos;
        this.dist = dist;
    }

    public int compareTo(path o) {
        return Integer.compare(this.dist, o.dist);
    }
}

public class BOJ1753 {
    public static void solution() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int V = Integer.parseInt(st.nextToken());
        int E = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(br.readLine());


        ArrayList<path>[] al = new ArrayList[V+1];
        for (int i = 1; i <= V; i++) {
            al[i] = new ArrayList<>();
        }

        while(E-- > 0) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            int w = Integer.parseInt(st.nextToken());

            path p = new path(v, w);
            al[u].add(p);
        }

        int[] dist = new int[V+1];
        int INF = Integer.MAX_VALUE;
        Arrays.fill(dist, INF);
        dist[K] = 0;

        PriorityQueue<path> pq = new PriorityQueue<>();
        pq.offer(new path(K, 0));
        while(!pq.isEmpty()) {
            path cur = pq.poll();
            for (path p : al[cur.pos]) {
                int newDist = p.dist + cur.dist;
                if (dist[p.pos] > newDist) {
                    dist[p.pos] = newDist;
                    pq.offer(new path(p.pos, newDist));
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 1; i <= V; i++) {
            if (dist[i] == INF) {
                sb.append("INF\n");
            } else {
                sb.append(dist[i]).append('\n');
            }
        }
        System.out.print(sb);
    }
}
```



## 주유소

``` java
// https://www.acmicpc.net/problem/13308
// 20.11.11. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

class way implements Comparable<way> {
    int pos;
    long cost;
    int oil;

    public way(int pos, long cost) {
        this.pos = pos;
        this.cost = cost;
    }

    public way(int pos, long cost, int oil) {
        this.pos = pos;
        this.cost = cost;
        this.oil = oil;
    }

    public int compareTo(way o) {
        return -Long.compare(this.cost, o.cost);
    }
}

public class BOJ13308 {
    public static void solution() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        // 기름 가격
        int[] oil = new int[n+1];
        st = new StringTokenizer(br.readLine());
        for(int i = 1; st.hasMoreTokens(); i++) {
            oil[i] = Integer.parseInt(st.nextToken());
        }
        // 도로 정보 입력
        ArrayList<way>[] al = new ArrayList[n+1];
        for (int i = 1; i <= n; i++)
            al[i] = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());
            al[a].add(new way(b, c));
            al[b].add(new way(a, c));
        }

        long[][] dp = new long[n+1][2501];
        for (int i = 1; i <= n; i++)
            Arrays.fill(dp[i], -1);
        PriorityQueue<way> pq = new PriorityQueue<>();
        pq.offer(new way(1, 0, oil[1]));
        long answer = 0;
        while(!pq.isEmpty()) {
            int pos = pq.peek().pos;
            long cost = -pq.peek().cost;
            int minO = pq.poll().oil;
            if (dp[pos][minO] != -1) continue;
            dp[pos][minO] = cost;
            if (pos == n) {
                answer = cost;
                break;
            }
            for (way i : al[pos]) {
                if (dp[i.pos][Math.min(minO, oil[i.pos])] != -1) continue;
                pq.offer(new way(i.pos, -cost-i.cost*minO, Math.min(minO, oil[i.pos])));
            }
        }
        System.out.println(answer);
    }
} 
```

