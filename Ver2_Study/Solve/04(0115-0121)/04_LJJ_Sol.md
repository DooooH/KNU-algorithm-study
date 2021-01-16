## 1256 사전
```java
import java.io.*;
import java.util.StringTokenizer;

public class Main {

    static double[][] dp;
    static BufferedWriter answer = new BufferedWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(bf.readLine());

        int N,M,K;
	    N = Integer.parseInt(st.nextToken());
	    M = Integer.parseInt(st.nextToken());
	    K = Integer.parseInt(st.nextToken());
        dp = new double[N + 1][M + 1];


        if(K>numWord(N,M)) {
            System.out.println("-1");
        }else {
            getWord(N,M,K-1);
        }
        answer.write("\n");
    answer.close();
    }
    static double numWord(int A, int Z){
        if(A==0||Z==0)
            return 1;
        if(dp[A][Z]!=0)
            return dp[A][Z];
        return dp[A][Z]= Double.min(numWord(A-1,Z)+numWord(A,Z-1), 1000000001);
    }

    static void getWord(int A, int Z, double before) throws IOException {
        if(A==0) {
            for (int i = 0; i < Z; i++)
                answer.write("z");
            return;
        }
        if(Z==0){
            for (int i = 0; i < A; i++) 
                answer.write("a");
            return;
            
        }
        double tmp = numWord(A-1, Z);

        if(before < tmp){
            answer.write("a");
            getWord(A-1,Z,before);
        }else {
            answer.write("z");
            getWord(A,Z-1,before-tmp);
        }
    }
}
```