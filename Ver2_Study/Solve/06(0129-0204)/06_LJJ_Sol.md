## 카카오 1번 신규 아이디 추천
정규식이 뭔지 몰라서 구현을 함.
```java
package com.company;

public class Main {

    public static void main(String[] args) {
        String s1,s2,s3,s4,s5;
        s1 = "...!@BaT#*..y.abcdefghijklm";
        s2 ="z-+.^.";
        s3 = "=.=";
        s4 = "123_.def";
        s5 = "abcdefghijklmn.p";
        System.out.println(Solution.solution(s5));
    }
}
class Solution{
    static StringBuilder answer;
    public static String solution(String new_id){
        answer = new StringBuilder();
        answer.append(new_id.toLowerCase());
        version2();
        v3();v4();v5();v6();v7();
        return answer.toString();
    }
    public static void version2(){
        //System.out.println(answer.toString().replaceAll("[^-._a-z0-9]",""));
        for (int i = 0; i < answer.length(); i++) {
            char tmp = answer.charAt(i);
            if((tmp <'0' || tmp >'9') && (tmp <'a'|| tmp >'z')){
                if (tmp != '-' && tmp !='_' && tmp !='.'){
                    answer.deleteCharAt(i--);
                }
            }

        }
    }
    public static void v3(){
        //System.out.println(answer.toString().replaceAll("[.]{2,}","."));
        while(answer.indexOf("..")!=-1){
            int start = answer.indexOf("..");
                answer.replace(start,start+2,".");
        }

    }
    public static void v4(){
       // System.out.println(answer.toString().replaceAll("[^.]|[.]$",""));
        if(answer.charAt(0) == '.')
            answer.deleteCharAt(0);
        if(answer.length()>0 && answer.charAt(answer.length()-1)== '.')
            answer.deleteCharAt(answer.length()-1);
    }
    public static void v5(){
        if(answer.length() == 0)
            answer.append("a");
    }
    public static void v6(){
        if (answer.length() >= 16)
            answer.delete(15,answer.length());
        v4();
    }
    public static void v7(){
        while(answer.length() < 3){
            answer.append(answer.charAt(answer.length()-1));
        }
    }
}
```

## 카카오 2번 메뉴 리뉴얼
브루트포스로 답이 됨.
```java
HashMap<String, Integer> hashMap = new HashMap<>();

    public String[] solution(String[] orders, int[] course) {

        ArrayList<String> before = new ArrayList<>(); // 초기화
        StringBuilder sb = new StringBuilder();

        for (String menu : orders) {
            char[] tmp = menu.toCharArray();
            Arrays.sort(tmp);
            for (int i : course) {
                Comb(tmp, sb, 0, 0, i);
            }
         } // 각각의 조합을 만들어 둠.

        for (int i : course) {
            Set<Map.Entry<String, Integer>> entry2 = hashMap.entrySet();
            int max = 0;
            for (Map.Entry<String, Integer> entry : entry2) {
                if (entry.getKey().length() == i) {
                    max = Math.max(max, entry.getValue());
                }
            }
            for (Map.Entry<String, Integer> entry : entry2) {
                if (max > 1 && entry.getValue() == max && entry.getKey().length() == i)
                    before.add(entry.getKey());
            }
        }

        Collections.sort(before);
        String[] answer = new String[before.size()];

        for (int i = 0; i < before.size(); i++) {
            answer[i] = before.get(i);
        }

        return answer;
    }

    public void Comb(char[] order, StringBuilder sb, int start, int n, int r) {
        if (n == r) {
            hashMap.put(sb.toString(), hashMap.getOrDefault(sb.toString(), 0) + 1);
            return;
        }
        for (int i = start; i < order.length; i++) {
            sb.append(order[i]);
            Comb(order, sb, i + 1, n + 1, r);
            sb.delete(n, n + 1);
        }
    }
    ```


## 개미굴 

```java
package com.company;

import java.io.*;
import java.util.*;

public class Main {
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int N = Integer.parseInt(bf.readLine());
        Trie root = new Trie("",0);

        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(bf.readLine());
            int k = Integer.parseInt(st.nextToken());
            Trie prev = root;

            for (int j = 0; j < k; j++) {
                String tmp = st.nextToken();
                boolean flag = false;
                for (int l = 0; l < prev.tries.size(); l++) {
                    if(prev.tries.get(l).word.equals(tmp)){
                        prev = prev.tries.get(l);
                        flag = true;
                        break;
                    }
                }
                if(!flag){
                    prev.tries.add(new Trie(tmp,prev.depth+1));
                    prev = prev.tries.get(prev.tries.size()-1);
                }
            }
        }
        print(root.tries);
        bw.close();
    }
    public static void print(List<Trie> trie) throws IOException {
        Collections.sort(trie);
        for (Trie trie1 : trie){
            for (int i = 0; i < trie1.depth-1; i++) {
                bw.write("--");
            }
            bw.write(trie1.word+"\n");
            print(trie1.tries);
        }
    }
}
class Trie implements Comparable<Trie>{
    String word;
    int depth;
    List<Trie> tries = new ArrayList<>();

    public Trie(String word, int depth) {
        this.word = word;
        this.depth = depth;
    }
    @Override
    public int compareTo(Trie o) {
        return this.word.compareTo(o.word);
    }
}
```