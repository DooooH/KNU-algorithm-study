## DLSR

``` java
// https://www.acmicpc.net/problem/9019
// 20.8.12. ventania1680
// BFS

package BOJ;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class BOJ9019 {
    static boolean[] visited = new boolean[10001];
    static String[] path = new String[10001];

    static int f(int num, char c) {
        switch (c) {
            case 'D':
                return (num * 2) % 10000;
            case 'S':
                return (num == 0) ? 9999 : --num;
            case 'L':
                return (num % 1000) * 10 + num / 1000;
            case 'R':
                return num / 10 + num % 10 * 1000;
        }
        return 0;
    }

    public static void solution() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();
        Queue<Integer> q = new LinkedList<>();
        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            Arrays.fill(path, "");
            Arrays.fill(visited, false);
            q.clear();

            q.add(a);
            visited[a] = true;
            int parent = 0, cur = 0;
            while (!q.isEmpty() && q.peek() != b) {
                parent = q.peek();
                cur = f(parent, 'D');
                if (!visited[cur]) {
                    visited[cur] = true;
                    path[cur] = path[parent] + "D";
                    q.add(cur);
                }

                cur = f(parent, 'S');
                if (!visited[cur]) {
                    visited[cur] = true;
                    path[cur] = path[parent] + "S";
                    q.add(cur);
                }

                cur = f(parent, 'L');
                if (!visited[cur]) {
                    visited[cur] = true;
                    path[cur] = path[parent] + "L";
                    q.add(cur);
                }

                cur = f(parent, 'R');
                if (!visited[cur]) {
                    visited[cur] = true;
                    path[cur] = path[parent] + "R";
                    q.add(cur);
                }
                q.poll();
            }
            sb.append(path[q.peek()] + "\n");
        }
        System.out.print(sb.toString());
    }
}
```

## 달이 차오른다, 가자.

``` java
package BOJ;

import java.io.*;
import java.util.*;

public class BOJ1194 {
    public static void solution() throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        int[][][] visited = new int[64][n][m];
        char[][] maze = new char[n][m];
        for (int i = 0; i < 64; i++)
            for (int j = 0; j < n; j++)
                Arrays.fill(visited[i][j], Integer.MAX_VALUE);

        for (int i = 0; i < n; i++) {
            maze[i] = br.readLine().toCharArray();
        }

        Queue<int[]> queue = new LinkedList<>();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == '0') {
                    queue.offer(new int[] {i, j, 0, 0});
                    visited[0][i][j] = 0;
                    i = n;
                    break;
                }
            }
        }

        int answer = -1;
        int[][] pos = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
        while(!queue.isEmpty()) {
            int[] cur = queue.poll();
            if (maze[cur[0]][cur[1]] == '1') {
                answer = visited[cur[3]][cur[0]][cur[1]];
                break;
            }
            for (int i = 0; i < 4; i++) {
                int y = cur[0] + pos[i][0];
                int x = cur[1] + pos[i][1];
                int cost = cur[2]+1;
                int keys = cur[3];
                if (y >= n || y < 0 || x >= m || x < 0)
                    continue;
                if (visited[keys][y][x] <= cost)
                    continue;
                if (maze[y][x] == '#')
                    continue;
                if (maze[y][x] >= 'A' && maze[y][x] <= 'F') {
                    if ((keys&(1<<maze[y][x]-'A'))==0)
                        continue;
                }
                if (maze[y][x] >= 'a' && maze[y][x] <= 'f') {
                    keys |= (1<<maze[y][x]-'a');
                }

                visited[keys][y][x] = cost;
                queue.offer(new int[] {y, x, cost, keys});
            }
        }
        System.out.println(answer);
    }
}
```



## 타겟 넘버

``` java
package Programmers;

import java.util.Queue;
import java.util.LinkedList;

public class P43165 {
    public static int solution(int[] numbers, int target) {
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[] {0, 0});

        int answer = 0;
        int n = numbers.length;
        while(!queue.isEmpty()) {
            int[] cur = queue.poll();
            if (cur[0] == n) {
                if (cur[1] == target) {
                    answer++;
                }
                continue;
            }
            queue.offer(new int[] {cur[0]+1, cur[1]+numbers[cur[0]]});
            queue.offer(new int[] {cur[0]+1, cur[1]-numbers[cur[0]]});
        }

        return answer;
    }
}
```

