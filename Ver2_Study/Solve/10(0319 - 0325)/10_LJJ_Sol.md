# BJ16719 ZOAC

```java
import java.io.*;

public class Main {
    static char[] str;
    static boolean[] visited;
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        str = br.readLine().toCharArray();
        visited = new boolean[str.length];
        go(0,str.length-1);
        bw.close();
    }
    public static void go(int left, int right) throws IOException {
        int i = left;
        if(left > right)
            return;
        for (int j = left; j <= right ; j++) {
            if(!visited[j] && str[i] > str[j])
                i = j;
        }
        visited[i] = true;
        for (int j = 0; j < str.length; j++)
            if(visited[j])
                bw.append(str[j]);
        bw.append("\n");
        go(i+1,right);
        go(left,i-1);
    }
}
```

# 17822 원판돌리기
```java

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    static int[][] circle;
    static Queue<pair> queue = new LinkedList<>();
    static int N, M, T;
    static boolean first;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());

        circle = new int[N][M];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < M; j++) {
                circle[i][j] = Integer.parseInt(st.nextToken());
            }
        }
        for (int i = 0; i < T; i++) {
            int x, d, k;
            st = new StringTokenizer(br.readLine());
            x = Integer.parseInt(st.nextToken());
            d = Integer.parseInt(st.nextToken());
            k = Integer.parseInt(st.nextToken());
            for (int j = x; j <= N; j += x)
                for (int l = 0; l < k; l++)
                    rotate(j - 1, d);

            for (int j = x; j <= N; j += x)
                search(j - 1);
            if (queue.isEmpty())
                some();
            else
                remove();
        }
        int sum = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                sum += circle[i][j];
        System.out.println(sum);
    }

    static void some() {
        double sum = 0;
        int tmp = 0;
        first = false;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (circle[i][j] != 0) {
                    sum += circle[i][j];
                    tmp++;
                }
            }
        }
        sum /= tmp;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (circle[i][j] != 0) {
                    if (circle[i][j] > sum)
                        circle[i][j]--;
                    else if (circle[i][j] < sum)
                        circle[i][j]++;
                }
            }
        }
    }
    
    static public void search(int x) {
        if (!first) {
            for (int j = 0; j < N; j++) {
                for (int i = 0; i < M; i++) {
                    if (circle[j][(i + 1)%M] == circle[j][i] && circle[j][i]!= 0 ) {
                        queue.offer(new pair(j, (i + 1)%M));
                        queue.offer(new pair(j, i));
                    }
                }
            }
            for (x = 1; x < N ; x++) {
                for (int j = 0; j < M; j++) {
                    if (x > 0 && circle[x - 1][j] == circle[x][j] && circle[x][j] != 0) {
                        queue.offer(new pair((x - 1), j));
                        queue.offer(new pair(x, j));
                    }
                    if (x < N - 1 && circle[x + 1][j] == circle[x][j] && circle[x][j] != 0) {
                        queue.offer(new pair((x + 1), j));
                        queue.offer(new pair(x, j));
                    }
                }
            }
            first = true;
        } else {
            for (int i = 0; i < M; i++) {
                if (circle[x][(i + 1)%M] == circle[x][i] && circle[x][i] != 0) {
                    queue.offer(new pair(x, (i + 1)%M));
                    queue.offer(new pair(x, i));
                }
            }
            for (int j = 0; j < M; j++) {
                if (x > 0 && circle[x - 1][j] == circle[x][j] && circle[x][j] != 0) {
                    queue.offer(new pair((x - 1), j));
                    queue.offer(new pair(x, j));
                }
                if (x < N - 1 && circle[x + 1][j] == circle[x][j] && circle[x][j] != 0) {
                    queue.offer(new pair((x + 1), j));
                    queue.offer(new pair(x, j));
                }
            }
        }
    }

    static public void remove() {
        while (!queue.isEmpty()) {
            pair p = queue.poll();
            circle[p.x][p.y] = 0;
        }
    }

    static public void rotate(int x, int d) {
        int[] tmp = new int[M];
        if (d == 0) { // nonClock
            for (int i = 0; i < M; i++) {
                tmp[(i + 1) % M] = circle[x][i % M];
            }
        } else {
            for (int i = 0; i < M; i++) {
                tmp[(i - 1 + M) % M] = circle[x][i % M];
            }
        }
        circle[x] = tmp;
    }
}

class pair {
    int x, y;

    public pair(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
```

# BJ19237 어른상어
```java

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    static int grid_size, sharks, trace;
    static Map<Integer, Shark> map = new HashMap<>();
    static Trace[][] traces;
    static int time;

    static int[] dx = {0, -1, 1, 0, 0};
    static int[] dy = {0, 0, 0, -1, 1};

    public static void main(String[] args) throws IOException {
        st = new StringTokenizer(br.readLine());
        grid_size = Integer.parseInt(st.nextToken());
        sharks = Integer.parseInt(st.nextToken());
        trace = Integer.parseInt(st.nextToken());
        traces = new Trace[grid_size+1][grid_size+1];
        for (int i = 0; i < grid_size; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < grid_size; j++) {
                int num = Integer.parseInt(st.nextToken());
                if (num != 0) {
                    map.put(num, new Shark(i + 1, j + 1));
                    traces[i + 1][j + 1] = new Trace(num, trace);
                }
            }
        }
        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= sharks; i++)
            map.get(i).setHead(Integer.parseInt(st.nextToken()));
        for (int i = 1; i <= sharks; i++) {
            int[][] tmp = new int[5][5];
            for (int j = 1; j <= 4; j++) {
                st = new StringTokenizer(br.readLine());
                for (int k = 1; k <= 4; k++) {
                    tmp[j][k] = Integer.parseInt(st.nextToken());
                }
            }
            map.get(i).setPriority(tmp);
        }

        move();


    }
    static public void remove(){
        for (int i = 1; i <= grid_size; i++) {
            for (int j = 1; j <= grid_size; j++) {
                if(traces[i][j] != null) {
                    if (traces[i][j].left > 0)
                        traces[i][j].left--;
                    if (traces[i][j].left == 0)
                        traces[i][j] = null;
                }
            }
        }
    }
    static public void move() {
        Queue<Shark> queue = new LinkedList<>();
        while (time <= 1000) {
            for (int i = 1; i <= sharks; i++) {
                if (map.containsKey(i)) {
                    Shark tmp = map.get(i);
                    int mine_x = 0, mine_y = 0;
                    int mine_haed = 0;
                    boolean flag = false;
                    for (int j = 1; j <= 4; j++) {
                        int nx = tmp.x + dx[tmp.priority[tmp.head][j]];
                        int ny = tmp.y + dy[tmp.priority[tmp.head][j]];
                        if (nx > 0 && ny > 0 && nx <= grid_size && ny <= grid_size && traces[nx][ny] == null) {
                            queue.offer(new Shark(tmp.priority[tmp.head][j],i,nx,ny));
                            flag = true;
                            break;
                        } else if (nx > 0 && ny > 0 && nx <= grid_size && ny <= grid_size && mine_x == 0 && traces[nx][ny].shark == i) {
                            mine_x = nx;
                            mine_y = ny;
                            mine_haed = tmp.priority[tmp.head][j];
                        }
                    }
                    if (!flag) {
                        queue.offer(new Shark(mine_haed,i,mine_x,mine_y));
                    }
                }
            }
            change(queue);
            remove();
            time++;
        }
        System.out.println(-1);
    }
    static public void change(Queue<Shark> queue){
        while (!queue.isEmpty()){
            Shark shark = queue.poll();
            int origin = 0;
            int bye = 0;
            int left = shark.num;
            if(traces[shark.x][shark.y]!= null && traces[shark.x][shark.y].left == trace+1){
                origin =traces[shark.x][shark.y].shark;
                bye = Math.max( origin, shark.num);
                left = Math.min( origin, shark.num);
                map.remove(bye);
                if(map.size() == 1) {
                    System.out.println(time + 1);
                    System.exit(0);
                }
            }
            traces[shark.x][shark.y] = new Trace(left, trace+1);
            map.get(left).setXY(shark.x,shark.y);
            if(left == shark.num)
                map.get(left).setHead(shark.head);

        }
    }
}

class Shark {

    int head, num;
    int x, y;
    int[][] priority = new int[5][5];

    public Shark(int head, int num, int x, int y) {
        this.head = head;
        this.num = num;
        this.x = x;
        this.y = y;
    }

    public Shark(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public void setXY(int x, int y){
        this.x = x;
        this.y = y;
    }
    public void setHead(int head) {
        this.head = head;
    }

    public void setPriority(int[][] priority) {
        this.priority = priority;
    }
}

class Trace {
    int shark;
    int left;

    public Trace(int shark, int left) {
        this.shark = shark;
        this.left = left;
    }


}
```

# 길찾기 게임
```java
package com.company;

import java.util.Arrays;

public class Solution {
    static int[][] answer;
    int idx = 0;
    public int[][] solution(int[][] nodeinfo) {
        int [][] setinfo = new int[nodeinfo.length][3];
        answer = new int[2][nodeinfo.length];
        for (int i = 0; i < nodeinfo.length; i++) {
            setinfo[i] = new int[]{nodeinfo[i][0],nodeinfo[i][1],i+1};
        }
        Arrays.sort(setinfo, (o1, o2) -> Integer.compare(o2[1], o1[1]));
        Node root = new Node(setinfo[0]);
        for (int i = 1; i < setinfo.length; i++) {
            Node parent = root.findParent(setinfo[i]);
            if(setinfo[i][0] < parent.x)
                parent.left = new Node(setinfo[i]);
            else
                parent.right = new Node(setinfo[i]);
        }
        preOrder(root);
        idx = 0;
        postOrder(root);
        return answer;
    }
    public void preOrder(Node root){
        answer[0][idx++] = root.idx;
        if(root.left != null)
            preOrder(root.left);
        if(root.right != null)
            preOrder(root.right);
    }
    public void postOrder(Node root){
        if(root.left != null)
            postOrder(root.left);
        if(root.right != null)
            postOrder(root.right);
        answer[1][idx++] = root.idx;

    }
}
class Node{
    int idx;
    int x,y;
    Node left, right;

    public Node(int[] setinfo) {
        this.idx = setinfo[2];
        this.x = setinfo[0];
        this.y = setinfo[1];
    }

    public Node findParent(int[] setinfo){
        int x = setinfo[0];
        int y = setinfo[1];

        Node tmp = x < this.x ? left : right;
        if(tmp == null)
            return this;
        while(tmp.y > y){
            Node child = x < tmp.x ? tmp.left : tmp.right;
            if(child == null)
                break;
            else
                tmp = child;
        }
        return tmp;
    }
}
```
