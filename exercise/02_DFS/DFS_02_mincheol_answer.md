```java
// BOJ1325
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

