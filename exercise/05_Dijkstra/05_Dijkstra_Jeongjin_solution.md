# 해킹
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int testcase = Integer.parseInt(bf.readLine());
        for (int i = 0; i < testcase; i++) {
            StringTokenizer st = new StringTokenizer(bf.readLine());
            int n = Integer.parseInt(st.nextToken());
            int d = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            ArrayList<Pair>[] adjlist = new ArrayList[n+1];
            for (int k = 1; k <= n; k++) {
                adjlist[k] = new ArrayList<>();
            }
            int[] distance = new int[n+1];
            Arrays.fill(distance, Integer.MAX_VALUE);
            PriorityQueue<Pair> pq = new PriorityQueue<>();

            for (int j = 0; j < d; j++) {
                st = new StringTokenizer(bf.readLine());
                int a= Integer.parseInt(st.nextToken());
                adjlist[Integer.parseInt(st.nextToken())].add(new Pair(a, Integer.parseInt(st.nextToken())));
            }
            
            pq.offer(new Pair(c,0));
            distance[c] = 0;
            while(!pq.isEmpty()){
                Pair tmp = pq.poll();
                for (int j = 0 ; j < adjlist[tmp.a].size(); j++) {
                    Pair newpair = adjlist[tmp.a].get(j);
                    if((newpair.s+ tmp.s) < distance[newpair.a]){
                        distance[newpair.a]= newpair.s + tmp.s;
                        pq.offer(new Pair(newpair.a,newpair.s+ tmp.s));
                    }
                }
            }
            int ret = -1;
            int cnt = 0;
            for (int j = 1; j < distance.length; j++) {
                if(distance[j] != Integer.MAX_VALUE){
                    ret = Math.max(ret, distance[j]);
                    cnt++;
                }
            }
            System.out.println(cnt + " " + ret );
        }
    }
}
class Pair implements Comparable<Pair>{
    int a, s;
    public Pair(int a, int s){
        this.a = a;
        this.s = s;
    }

    @Override
    public int compareTo(Pair o) {
        if(this.s < o.s)
            return -1;
        else if(this.s == o.s)
            return 0;
        else return 1;
    }
}
```

# BJ1753
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf. readLine());
        PriorityQueue<Pair> pq = new PriorityQueue<>();
        int v = Integer.parseInt(st.nextToken());
        int e = Integer.parseInt(st.nextToken());
        int start = Integer.parseInt(bf.readLine());
       // int[] parent = new int[v+1];
        int[] distance = new int[v+1];

      //  Arrays.fill(parent, -1);
        Arrays.fill(distance, Integer.MAX_VALUE);
        ArrayList<Pair>[] adjlist = new ArrayList[v+1];

        for (int i = 1; i <= v; i++)
            adjlist[i] = new ArrayList<>();

        for (int i = 0; i < e; i++) {
            st = new StringTokenizer(bf.readLine());
            adjlist[Integer.parseInt(st.nextToken())].add(new Pair(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())));
        }
        pq.offer(new Pair(start,0));
        distance[start] = 0;

        while (!pq.isEmpty()){
            Pair tmp = pq.poll();
            for (int i = 0; i < adjlist[tmp.v].size(); i++) {
                Pair listv = adjlist[tmp.v].get(i);
                if((tmp.w + listv.w) < distance[listv.v]){
                    distance[listv.v] = tmp.w + listv.w;
                    pq.offer(new Pair(listv.v, tmp.w+listv.w));
                  //  parent[listv.v]= tmp.v;
                }
            }
        }
        for (int i = 1; i < distance.length; i++) {
            if(distance[i] == Integer.MAX_VALUE)
                System.out.println("INF");
            else
                System.out.println(distance[i]);
        }
    }
}
class Pair implements Comparable<Pair>{
    int v,w;
    public Pair(int v, int w){
        this.v = v;
        this.w = w;
    }
    @Override
    public int compareTo(Pair o) {
    if(this.w < o.w)
        return -1;
    else if(this.w == o.w)
        return 0;
    else return 1;
    }
}
```
#16118
```java
package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        ArrayList<Pair>[] foxadjlist = new ArrayList[N+1];
        ArrayList<Pair>[] wolfadjlist = new ArrayList[2*N + 1];

        for (int i = 1; i <= N; i++) {
            foxadjlist[i] = new ArrayList<>();
        }
        for (int i = 1; i <= 2*N ; i++) {
            wolfadjlist[i] = new ArrayList<>();
        }
        int[] foxdistance = new int[N + 1];
        int[] wolfdistance = new int[2*N + 1];
        Arrays.fill(foxdistance, Integer.MAX_VALUE);
        Arrays.fill(wolfdistance,Integer.MAX_VALUE);

        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(bf.readLine());
            int a =Integer.parseInt(st.nextToken());
            int b =Integer.parseInt(st.nextToken());
            int d =Integer.parseInt(st.nextToken());
            foxadjlist[a].add(new Pair(b,d*2));
            foxadjlist[b].add(new Pair(a,d*2));
            wolfadjlist[a].add(new Pair(b+N,d));
            wolfadjlist[a+N].add(new Pair(b,d*4));
            wolfadjlist[b].add(new Pair(a+N,d));
            wolfadjlist[b+N].add(new Pair(a,d*4));
        }
        dijkstra(1,foxadjlist,foxdistance);
        dijkstra(1,wolfadjlist,wolfdistance);

        int cnt = 0;
        for (int i = 2; i <= N ; i++) {
            if(foxdistance[i] < Math.min(wolfdistance[i],wolfdistance[i+N]))
                cnt++;
        }
        System.out.println(cnt);


    }

    public static void dijkstra(int start, ArrayList<Pair>[] adjlist, int[] distance ){

        PriorityQueue<Pair> pq = new PriorityQueue<>();

        distance[start]= 0;
        pq.offer(new Pair(start,0));

        while (!pq.isEmpty()){
            Pair tmp = pq.poll();
            if (tmp.w > distance[tmp.v])
                continue;
            for (int i = 0; i < adjlist[tmp.v].size(); i++) {
                Pair newtmp = adjlist[tmp.v].get(i);

                if((newtmp.w+tmp.w)<distance[newtmp.v]){
                    distance[newtmp.v] = newtmp.w + tmp.w;
                    pq.offer(new Pair(newtmp.v, newtmp.w + tmp.w));
                }
            }
        }

    }
}
    class Pair implements Comparable<Pair>{
        int v;
        int w;
        public Pair(int v, int w){
            this.v = v;
            this.w = w;
        }
        @Override
        public int compareTo(Pair o) {
            if(this.w<o.w)
                return  -1;
            else if(this.w == o.w)
                return 0;
            else return 1;
        }
    }
```