```java
// BOJ1701 Cubeditor
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        char[] s = br.readLine().toCharArray();
        int len = s.length;
        int answer = 0;
        int[] pi = new int[len];
        for (int i = 0; i < len; i++) {
            Arrays.fill(pi, 0);
            int k = i;
            for (int j = i+1; j < len; j++) {
                while(k > i && s[k] != s[j])
                    k = pi[k-1] + i;
                if (s[k] == s[j]) {
                    pi[j] = ++k - i;
                    answer = answer > pi[j] ? answer : pi[j];
                }
            }
        }
        System.out.println(answer);
    }
}

```

