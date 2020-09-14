```java
// BOJ1325 해킹
import java.util.*;
import java.io.*;

public class Main {
    static ArrayList<Integer>[] list = (ArrayList<Integer>[]) new ArrayList[10001];
    static int[]visited = new int[10001];
    static int[]answer = new int[10001];
    static int n, m, ans = 0;

    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        for(int i = 1; i <= n; i++)
            list[i] = new ArrayList<>();

        while(m-- > 0) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            list[x].add(y);
        }


        for(int i = 1; i <= n; i++) {
            init();
            dfs(i);
        }

        for(int i = 1; i <= n; i++)
            ans = Math.max(ans, answer[i]);

        for(int i = 1; i <= n; i++) {
            if(answer[i] == ans)
                System.out.print(i + " ");
        }
    }

    static void dfs(int num) {
        visited[num] = 1;
        for(int next : list[num]) {
            if(visited[next] == 1) continue;
            answer[next]++;
            dfs(next);
        }
    }

    static void init() {
        for(int i = 1; i <= n; i++)
            visited[i] = 0;
    }
}
```



```java
// BOJ2573 빙산
// https://www.acmicpc.net/problem/2573
// 20.9.14. ventania1680
package BOJ;

import java.util.*;
import java.io.*;

public class BOJ2573 {
    static int[][] iceberg = new int[300][300];
    static int min_row, max_row, min_col, max_col;
    static int n, m;
    static Stack<int[]> stack = new Stack<>();
    static boolean[][] visited = new boolean[300][300];

    public static void dfs(int x, int y) {
        if (visited[y][x]) {
            return;
        }
        visited[y][x] = true;
        int zero = 4;
        if (iceberg[y-1][x] != 0) {
            dfs(x, y-1);
            zero--;
        }
        if (iceberg[y+1][x] != 0) {
            dfs(x, y+1);
            zero--;
        }
        if (iceberg[y][x-1] != 0) {
            dfs(x-1, y);
            zero--;
        }
        if (iceberg[y][x+1] != 0) {
            dfs(x+1, y);
            zero--;
        }
        stack.push(new int[] {x,y,iceberg[y][x]-zero});
    }

    public static void updateIceberg() {
        while(!stack.isEmpty()) {
            int x = stack.peek()[0];
            int y = stack.peek()[1];
            int val = stack.pop()[2];
            if (val < 0) val = 0;
            iceberg[y][x] = val;
            visited[y][x] = false;
        }
    }

    public static void solution() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        min_row = min_col = 300;
        max_row = max_col = 0;
        for(int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < m; j++) {
                int tmp  = Integer.parseInt(st.nextToken());
                if (tmp > 0) {
                    if (min_row > i) min_row = i;
                    if (max_row < i) max_row = i;
                    if (min_col > j) min_col = j;
                    if (max_col < j) max_col = j;
                    iceberg[i][j] = tmp;
                }
            }
        }

        int year = 0;
        int cnt = 0;
        while(true) {
            cnt = 0;
            for (int i = min_row; i <= max_row; i++) {
                for (int j = min_col; j <= max_col; j++) {
                    if (iceberg[i][j] > 0 && !visited[i][j]) {
                        cnt++;
                        dfs(j, i);
                    }
                }
            }
            updateIceberg();
            if (cnt != 1) break;
            year++;
        }
        if (cnt == 0) System.out.print(0);
        else System.out.print(year);
    }
}
```



```java
// 경주로
import java.util.Arrays;

class Solution {
    static int[][] visited = new int[25][25];
    static int[][] newBoard = new int[25][25];
    static int n;

    public static void dfs(int x, int y, int cost, int dir) {
        if (visited[y][x] < cost)
            return;
        visited[y][x] = cost;

        if (x < n - 1 && newBoard[y][x+1] == 0 && dir != 4) {
            if (dir == 6 || dir == 0)
                dfs(x+1, y, cost+100, 6);
            else
                dfs(x+1, y, cost+600, 6);
        }
        if (y < n - 1 && newBoard[y+1][x] == 0 && dir != 8) {
            if (dir == 2 || dir == 0)
                dfs(x, y+1, cost+100, 2);
            else
                dfs(x, y+1, cost+600, 2);
        }
        if (x > 0 && newBoard[y][x-1] == 0 && dir != 6) {
            if (dir == 4 || dir == 0)
                dfs(x-1, y, cost+100, 4);
            else
                dfs(x-1, y, cost+600, 4);
        }
        if (y > 0 && newBoard[y-1][x] == 0 && dir != 2) {
            if (dir == 8 || dir == 0)
                dfs(x, y-1, cost+100, 8);
            else
                dfs(x, y-1, cost+600, 8);
        }
    }

    public int solution(int[][] board) {
        n = board.length;
        for (int i = 0; i < n; i++)
            Arrays.fill(visited[i], 10000000);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                newBoard[i][j] = board[i][j];
            }
        }
        dfs(0, 0, 0, 0);
        return visited[n-1][n-1];
    }
}

```



```java
// BOJ16437 양 구출 작전
import java.util.*;
import java.io.*;

public class Main {
    static long[] sheep = new long[123457];
    static ArrayList<Integer>[] al = new ArrayList[123457];
    static void dfs(int pos, int prev) {
        for (int i = 0; i < al[pos].size(); i++)
            dfs(al[pos].get(i), pos);
        if (sheep[pos] > 0)
            sheep[prev] += sheep[pos];
    }
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        StringTokenizer st;
        for (int i = 1; i <= n; i++)
            al[i] = new ArrayList<Integer>();
        for (int i = 2; i <= n; i++) {
            st = new StringTokenizer(br.readLine());
            if (st.nextToken().compareTo("S") == 0)
                sheep[i] = Long.parseLong(st.nextToken());
            else
                sheep[i] = -Long.parseLong(st.nextToken());
            int p = Integer.parseInt(st.nextToken());
            al[p].add(i);
        }
        dfs(1, 0);
        System.out.print(sheep[1]);
    }
}

```

