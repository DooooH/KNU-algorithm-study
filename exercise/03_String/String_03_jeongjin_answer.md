# BOJ-5052
## TRIE로 풀이
```java
public class BOJ5052 {

    static public void solution() throws IOException {

        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(bf.readLine());

        for (int i = 0; i < t; i++) {
            String yes = "YES";
            Trie ROOT = new Trie();
            int n = Integer.parseInt(bf.readLine());
            String[] list = new String[n];
            for (int j = 0; j < n; j++) {
                list[j] = bf.readLine();
            }
           Arrays.sort(list, new Comparator<String>() {
               @Override
               public int compare(String o1, String o2) {
                   if(o1.length() < o2.length())
                       return -1;
                   else if (o1.length() == o2.length()) return 0;
                   else return 1;
               }
           });


            for (int j = 0; j < n; j++) {
                Trie ptr = ROOT;
                String temp = list[j];
                int k;
                for ( k = 0; k < temp.length()-1; k++) {
                    if(ptr.isfinal == true){
                        yes = "NO";
                        break;
                    }
                    if(ptr.trie[temp.charAt(k) -'0'] == null){
                        ptr.trie[temp.charAt(k) -'0'] = new Trie();
                        ptr = ptr.trie[temp.charAt(k) -'0'];
                    }
                    else
                        ptr =ptr.trie[temp.charAt(k)-'0'];
                }
                if(ptr.isfinal == true){
                    yes = "NO";
                    break;
                }
                if(ptr.trie[temp.charAt(k)-'0'] == null){
                    ptr.trie[temp.charAt(k)-'0'] = new Trie();
                    ptr.trie[temp.charAt(k)-'0'].isfinal = true;
                }
            }
            System.out.println(yes);
        }
    }

}

class Trie {
    boolean isfinal = false;
    Trie[] trie = new Trie[10];
}
```

## hashmap 사용
```java
public class Main {
    static int T;
    public static void main(String[] args) throws IOException {
   // write your code here
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for (int i = 0; i < T; i++) {
            int N = Integer.parseInt(br.readLine());
            ArrayList<String> list = new ArrayList<>();
            String result = "YES";
            for (int j = 0; j < N; j++) {
                list.add(br.readLine());
            }
            Collections.sort(list, new Comparator<String>() {
                @Override
                public int compare(String o1, String o2) {
                    if(o1.length() < o2.length())
                        return -1;
                    else if(o1.length() == o2.length())
                        return 0;
                    else return 1;
                }
            });
            HashMap<Integer, Set<String>> hashMap = new HashMap<>();
            for (int j = 1; j <= 10; j++) {
                hashMap.put(j, new HashSet<>());
            }
            for (int j = 0; j < N; j++) {
                String tmp = list.get(j);
                int k;
                for (k = 1; k < tmp.length(); k++) {
                    String sub = tmp.substring(0, k);
                    if(hashMap.get(k).contains(sub)){
                        result = "NO";
                        break;
                    }
                }
                if(result.equals("NO"))
                    break;
                else
                    hashMap.get(k).add(tmp);
            }
            System.out.println(result);
        }
    }
}
```