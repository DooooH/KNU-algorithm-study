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

## 웜홀
``` java
// https://www.acmicpc.net/problem/1865
// 20.11.18. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class BOJ1865 {
	static long[] cost = new long[501];
	public static void solution() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		while (t-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int w = Integer.parseInt(st.nextToken());
			int[][] route = new int[m*2+w][3];
			for (int i = 0; i < m; i++) {
				st = new StringTokenizer(br.readLine());
				route[i][0] = Integer.parseInt(st.nextToken());
				route[i][1] = Integer.parseInt(st.nextToken());
				route[i][2] = Integer.parseInt(st.nextToken());
				route[i+m+w][0] = route[i][1];
				route[i+m+w][1] = route[i][0];
				route[i+m+w][2] = route[i][2];
			}
			for (int i = m; i < m+w; i++) {
				st = new StringTokenizer(br.readLine());
				route[i][0] = Integer.parseInt(st.nextToken());
				route[i][1] = Integer.parseInt(st.nextToken());
				route[i][2] = -Integer.parseInt(st.nextToken());
			}

			long INF = Integer.MAX_VALUE;


			boolean updated = false;
			boolean p = false;
			for (int k = 1; k <= n; k++) {
				Arrays.fill(cost, INF);
				cost[k] = 0;
				for (int i = 0; i < n; i++) {
					updated = false;
					for (int j = 0; j < m*2+w; j++) {
						if (cost[route[j][0]] == INF) continue;
						if (cost[route[j][1]] > cost[route[j][0]] + route[j][2]) {
							updated = true;
							cost[route[j][1]] = cost[route[j][0]] + route[j][2];
						}
					}
					if (!updated) break;
				}
				if (updated) {
					System.out.println("YES");
					p = true;
					break;
				}
			}
			if (!p)
				System.out.println("NO");
		}
	}
}
```

## 골목길
``` java
// https://www.acmicpc.net/problem/1738
// 20.11.18. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class BOJ1738 {
	static int[][] arr = new int[20000][3];
	static long[] cost = new long[101];
	static int[] p = new int[101];
	public static void solution() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());

		for (int i = 0; i < m; i++) {
			st = new StringTokenizer(br.readLine());
			arr[i][1] = Integer.parseInt(st.nextToken());
			arr[i][0] = Integer.parseInt(st.nextToken());
			arr[i][2] = Integer.parseInt(st.nextToken());
		}

		int NINF = Integer.MIN_VALUE;
		Arrays.fill(cost, NINF);
		Arrays.fill(p, -1);
		cost[n] = 0;
		p[n] = n;

		boolean updated = false;
		for (int i = 0; i < n; i++) {
			updated = false;
			for (int j = 0; j < m; j++) {
				if (cost[arr[j][0]] == NINF) continue;
				if (cost[arr[j][1]] < cost[arr[j][0]] + arr[j][2]) {
					updated = true;
					cost[arr[j][1]] = cost[arr[j][0]] + arr[j][2];
					p[arr[j][1]] = arr[j][0];
				}
			}
			if (!updated) break;
		}

		if (updated || cost[1] == NINF)
			System.out.println(-1);
		else {
			StringBuilder sb = new StringBuilder();
			int idx = 1;
			while(idx != n) {
				sb.append(idx).append(' ');
				idx = p[idx];
			}
			sb.append(n);
			System.out.println(sb);
		}
	}
}
```

## 할로윈묘지
``` java
// https://www.acmicpc.net/problem/3860
// 20.11.18. ventania1680
package BOJ;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class BOJ3860 {
	static int[][] pos = {{0, 1},{1, 0}, {0, -1}, {-1, 0}};
	public static void solution() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while(true) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int w = Integer.parseInt(st.nextToken());
			int h = Integer.parseInt(st.nextToken());
			if (w == 0) break;

			int g = Integer.parseInt(br.readLine());
			boolean[][] grave = new boolean[w][h];
			for (int i = 0; i < g; i++) {
				st = new StringTokenizer(br.readLine());
				grave[Integer.parseInt(st.nextToken())][Integer.parseInt(st.nextToken())] = true;
			}

			ArrayList<int[]> list = new ArrayList<>();

			int e = Integer.parseInt(br.readLine());
			boolean[][] portal = new boolean[w][h];
			for (int i = 0; i < e; i++) {
				st = new StringTokenizer(br.readLine());
				int[] ghost = new int[5];
				ghost[0] = Integer.parseInt(st.nextToken());
				ghost[1] = Integer.parseInt(st.nextToken());
				ghost[2] = Integer.parseInt(st.nextToken());
				ghost[3] = Integer.parseInt(st.nextToken());
				ghost[4] = Integer.parseInt(st.nextToken());
				portal[ghost[0]][ghost[1]] = true;
				list.add(ghost);
			}

			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					if (grave[x][y] || portal[x][y]) continue;
					if (x == w-1 && y == h-1) break;
					for (int j = 0; j < 4; j++) {
						int newx = x+pos[j][0];
						int newy = y+pos[j][1];
						if (newx < 0 || newx >= w || newy < 0 || newy >= h || grave[newx][newy]) continue;
						list.add(new int[] {x, y, newx, newy, 1});
					}
				}
			}


			long[][] cost = new long[w][h];
			int INF = Integer.MAX_VALUE;
			for (int i = 0; i < w; i++)
				Arrays.fill(cost[i], INF);
			cost[0][0] = 0;

			boolean updated = false;
			for (int i = 0; i < w*h; i++) {
				updated = false;
				for (int j = 0; j < list.size(); j++) {
					if (cost[list.get(j)[0]][list.get(j)[1]] == INF) continue;
					if (cost[list.get(j)[2]][list.get(j)[3]] > cost[list.get(j)[0]][list.get(j)[1]] + list.get(j)[4]) {
						updated = true;
						cost[list.get(j)[2]][list.get(j)[3]] = cost[list.get(j)[0]][list.get(j)[1]] + list.get(j)[4];
					}
				}
				if (!updated) break;
			}

			if (updated)
				System.out.println("Never");
			else if (cost[w-1][h-1] == INF)
				System.out.println("Impossible");
			else
				System.out.println(cost[w-1][h-1]);
		}
	}
}
```
