## 타임머신

``` java
// https://www.acmicpc.net/problem/11657
// 20.11.12. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class BOJ11657 {
    static int n, m;
    static int[][] pArr;
    static BufferedReader br;
    static StringTokenizer st;
    static StringBuilder sb = new StringBuilder();
    static long[] dist;

    public static void solution() throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        st = new StringTokenizer(br.readLine());

        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        pArr = new int[m][3];

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            pArr[i][0] = Integer.parseInt(st.nextToken());
            pArr[i][1] = Integer.parseInt(st.nextToken());
            pArr[i][2] = Integer.parseInt(st.nextToken());
        }

        dist = new long[n+1];
        final int INF = Integer.MAX_VALUE;
        Arrays.fill(dist, INF);
        dist[1] = 0;

        boolean updated = false;
        for (int i = 0; i < n; i++) {
            updated = false;
            for (int j = 0; j < m; j++) {
                if (dist[pArr[j][0]] == INF) continue;
                if (dist[pArr[j][1]] > dist[pArr[j][0]] + pArr[j][2]) {
                    updated = true;
                    dist[pArr[j][1]] = dist[pArr[j][0]] + pArr[j][2];
                }
            }
            if (!updated) break;
        }

        if (updated)
            System.out.println(-1);
        else {
            for (int i = 2; i <= n; i++) {
                if (dist[i] == INF)
                    sb.append("-1\n");
                else
                    sb.append(dist[i]).append('\n');
            }
            System.out.print(sb);
        }
    }
}
```

