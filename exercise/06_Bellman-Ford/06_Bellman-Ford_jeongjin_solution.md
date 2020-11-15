## 웜홀
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    static int INF = 1000000000;
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int TC = Integer.parseInt(bf.readLine());

        for (int i = 0; i < TC; i++) {
            StringTokenizer st = new StringTokenizer(bf.readLine());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int W = Integer.parseInt(st.nextToken());
            Edge[] edges = new Edge[2*M + W];
            int[] dist = new int[N+1];

            int idx =0;
            for (int j = 0; j < M + W; j++) {
                st = new StringTokenizer(bf.readLine());
                int s =Integer.parseInt(st.nextToken());
                int e = Integer.parseInt(st.nextToken());
                int w = Integer.parseInt(st.nextToken());
                if(j<M) {
                    edges[idx++] = new Edge(s,e,w);
                    edges[idx++] = new Edge(e,s,w);
                }else
                    edges[idx++]=new Edge(s, e, w*-1);
            }
            if(Bellman(edges,dist,N))
                System.out.println("YES");
            else
                System.out.println("NO");
        }


    }
    static boolean Bellman(Edge[] edges, int[] Distance, int N){
        Arrays.fill(Distance, INF);
        Distance[1] = 0;

        for (int i = 1; i < N; i++) {
            for (Edge edge : edges) {
                if ( Distance[edge.startV] + edge.weight < Distance[edge.endV])
                    Distance[edge.endV] = Distance[edge.startV] + edge.weight;
            }
        }

        for (int i = 0; i < edges.length; i++) {
            Edge edge = edges[i];
            if((Distance[edge.startV]+edge.weight) < Distance[edge.endV])
                return true;
        }
        return false;
    }
}
class Edge{
    int startV,endV,weight;
    public Edge(int startV, int endV, int weight){
        this.startV = startV;
        this.endV = endV;
        this.weight = weight;
    }

}
```