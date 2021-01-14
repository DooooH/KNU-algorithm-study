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



```java
// BOJ8913 문자열 뽑기
// https://www.acmicpc.net/problem/8913
// 20.9.21. ventania1680
package BOJ;

import java.io.*;
import java.util.*;

public class BOJ8913 {
    static boolean extract(String str) {
        if (str.length() == 1)
            return false;
        int i = 0;
        String newStr;
        for (int j = 1; j < str.length(); j++) {
            if (str.charAt(i) != str.charAt(j)) {
                if(j-i > 1) {
                    if (i == 0)
                        newStr = str.substring(j);
                    else
                        newStr = str.substring(0, i) + str.substring(j);
                    if (extract(newStr))
                        return true;
                }
                i = j;
            }
        }
        if (i == 0)
            return true;
        else
            return false;
    }
    public static void solution() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();
        while(t-- > 0) {
            ArrayList<String> list = new ArrayList<>();
            String str = br.readLine();
            if(extract(str)) {
                sb.append("1\n");
            } else {
                sb.append("0\n");
            }
        }
        System.out.println(sb);
    }
}
```



```java
// BOJ5052 전화번호 목록
// https://www.acmicpc.net/problem/5052
// 20.9.21. ventania1680

package BOJ;

import java.io.*;
import java.util.*;

class trieNode {
    Map<Character, trieNode> childNodes = new HashMap<>();
    boolean isLastChar;

    void setIsLastChar(boolean isLastChar) {
        this.isLastChar = isLastChar;
    }
}

class trie {
    trieNode rootNode;
    trie() {
        rootNode = new trieNode();
    }
    void insert(String str) {
        trieNode thisNode = this.rootNode;
        for (int i = 0; i < str.length(); i++) {
            thisNode = thisNode.childNodes.computeIfAbsent(str.charAt(i), c->new trieNode());
        }
        thisNode.setIsLastChar(true);
    }
    boolean contains(String str) {
        trieNode thisNode = this.rootNode;
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            trieNode node = thisNode.childNodes.get(c);

            if (node == null)
                return false;

            thisNode = node;
        }
        return true;
    }
}

public class BOJ5052 {
    public static void solution() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();
        while(t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            String[] strArr = new String[n];
            for (int i = 0; i < n; i++)
                strArr[i] = br.readLine();
            Arrays.sort(strArr, Comparator.reverseOrder());
            trie root = new trie();
            for (int i = 0; i < n; i++) {
                if (root.contains(strArr[i])) {
                    sb.append("NO\n");
                    break;
                }
                if (i == n-1) {
                    sb.append("YES\n");
                    break;
                }
                root.insert(strArr[i]);
            }
        }
        System.out.println(sb.toString());
    }
}
```

```java
// https://www.acmicpc.net/problem/16229
// 20.9.23. ventania1680
package BOJ;

import java.util.*;
import java.io.*;

public class BOJ16229 {
    static int[] getPi(String str) {
        int len = str.length();
        int[] pi = new int[len];
        int j = 0;
        for (int i = 1; i < len; i++) {
            while (j > 0 && str.charAt(i) != str.charAt(j)) {
                j = pi[j - 1];
            }
            if (str.charAt(i) == str.charAt(j))
                pi[i] = ++j;
        }
        return pi;
    }

    public static void solution() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());
        String str = br.readLine();

        int answer = 0;
        if (n <= k) {
            answer = n;
        } else {
            int pLen = 0, pCnt;
            int[] pi = getPi(str);
            int cur = n-1;
            while(true) {
                pLen = n - pi[cur];
                pCnt = (n + k) / pLen;
                if(pCnt >= 2 && pLen*pCnt >= n)
                    answer = Math.max(answer, pLen);
                if (2*pi[cur] <= cur+1) break;
                cur = pi[cur]-1;
            }
        }
        System.out.println(answer);
    }
}
```
