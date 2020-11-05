## 타겟넘버
``` java
import java.util.LinkedList;
import java.util.Queue;
class Solution {
    public int solution(int[] numbers, int target) {
        int answer = 0;

        Queue<Pair> queue = new LinkedList<>();
        queue.offer(new Pair(numbers[0],0));
        queue.offer(new Pair(-numbers[0],0));

        while (!queue.isEmpty()){
            Pair pair = queue.poll();
            if(pair.idx == numbers.length-1) {
                if(pair.value == target)
                    answer++;
                continue;
            }
            queue.add(new Pair(pair.value + numbers[pair.idx+1],pair.idx+1));
            queue.add(new Pair(pair.value - numbers[pair.idx+1],pair.idx+1));

        }
        return  answer;
    }
}
class Pair{
    int value;
    int idx;
    public Pair(int value, int idx){
        this.value = value;
        this.idx = idx;
    }
}
```

## 달이 차오른다, 가자

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
class Position{
    int i,j;
    int cnt, key;
    public Position(int i, int j, int cnt, int key){
        this.i = i;
        this.j = j;
        this.cnt = cnt;
        this.key = key;
    }
}
public class BJ1194 {
    public static void main(String[] args) throws IOException {
        int M,N;
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer stringTokenizer = new StringTokenizer(bf.readLine());
        M = Integer.parseInt(stringTokenizer.nextToken());
        N = Integer.parseInt(stringTokenizer.nextToken());
        char[][] maze = new char[M][N];
        boolean[][][] visited = new boolean[64][M][N];
        boolean flag = false;
        for (int i = 0; i < M; i++)
            maze[i] = bf.readLine().toCharArray();

        Queue<Position> queue = new LinkedList<>();

        int[] di = {-1, 0, 1, 0};
        int[] dj = {0, 1, 0, -1};

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if(maze[i][j] == '0'){
                    queue.offer(new Position(i,j,0,0));
                    visited[0][i][j] = true;
                }
            }
        }

        while (!queue.isEmpty()) {
            Position tmp = queue.poll();
            if (maze[tmp.i][tmp.j] == '1') {
                System.out.println(tmp.cnt);
                flag = true;
                break;
            }
            for (int i = 0; i < 4; i++) {
                int nx = tmp.i + di[i];
                int ny = tmp.j + dj[i];
                int key = tmp.key;
                if (nx >= 0 && ny >= 0 && nx < M && ny < N && maze[nx][ny] != '#' &&  !visited[key][nx][ny]) {
                    if (maze[nx][ny] == '.' || maze[nx][ny] == '0' || maze[nx][ny] == '1'){
                        visited[key][nx][ny] = true;
                        queue.offer(new Position(nx, ny, tmp.cnt + 1, key));

                    }
                    else if (maze[nx][ny] >= 'a' && maze[nx][ny] <= 'f') {
                        int bkey = key;
                        key = (key | (1 << (maze[nx][ny] - 'a')));
                        if (!visited[key][nx][ny]) {
                            visited[bkey][nx][ny] = true;
                            visited[key][nx][ny] = true;
                            queue.offer(new Position(nx, ny, tmp.cnt + 1, key));
                        }
                    } else if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'F') {
                        if ((key &(1 << (maze[nx][ny] - 'A'))) != 0) {
                            visited[key][nx][ny] = true;
                            queue.offer(new Position(nx, ny, tmp.cnt + 1, key));
                        }
                    }
                }

            }
        }
        if(!flag)
            System.out.println("-1");
    }

}


## DSLR
```java

package com.company;

import java.io.*;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(System.out));
        int N = Integer.parseInt(bf.readLine());
        for (int i = 0; i < N; i++) {
            StringTokenizer stringTokenizer = new StringTokenizer(bf.readLine());
            String A = stringTokenizer.nextToken();
            int B = Integer.parseInt(stringTokenizer.nextToken());
            boolean[] visited= new boolean[10001];
            Queue<Pair> queue = new LinkedList<>();

            queue.offer(new Pair("",Integer.parseInt(A)));
            visited[Integer.parseInt(A)] = true;

            while(!queue.isEmpty()){
                Pair tmp = queue.poll();


                if(!visited[(tmp.resister * 2) % 10000]) {
                    if((tmp.resister * 2) % 10000==B)
                    {
                        bufferedWriter.write(tmp.dslr + "D\n");
                        break;
                    }
                    queue.offer(new Pair(tmp.dslr + "D", (tmp.resister * 2) % 10000));
                    visited[(tmp.resister * 2) % 10000] = true;

                    }

                if (tmp.resister == 0) { // S
                    if(!visited[9999]){
                        if(B == 9999)
                        {
                            bufferedWriter.write(tmp.dslr + "S\n");
                            break;
                        }
                        queue.offer(new Pair(tmp.dslr + "S", 9999));
                        visited[9999] = true;
                    }
                } else {
                    if (!visited[tmp.resister - 1]) {
                        if((tmp.resister - 1) ==B)
                        {
                            bufferedWriter.write(tmp.dslr + "S\n");
                            break;
                        }
                        queue.offer(new Pair((tmp.dslr + "S"), tmp.resister - 1));
                        visited[tmp.resister -1] =true;
                    }
                }
                // L left 1 bit
                int afterLint = tmp.d2 * 1000 + tmp.d3 * 100 + tmp.d4 * 10 + tmp.d1;
                if(!visited[afterLint]){
                    if(B == afterLint)
                    {
                        bufferedWriter.write(tmp.dslr + "L\n");
                        break;
                    }
                    queue.offer(new Pair(tmp.dslr+"L", tmp.d2, tmp.d3, tmp.d4, tmp.d1, afterLint));
                    visited[afterLint]= true;
                }
                int afterRint =tmp.d2 * 10 + tmp.d3  + tmp.d4 * 1000 + tmp.d1 * 100;
                if(!visited[afterRint]){
                    if(B == afterRint)
                    {
                        bufferedWriter.write(tmp.dslr + "R\n");
                        break;
                    }
                    queue.offer(new Pair(tmp.dslr+"R", tmp.d4, tmp.d1, tmp.d2, tmp.d3,afterRint));
                    visited[afterRint]= true;
                }
            }
        }
        bufferedWriter.close();
    }
}
class Pair{
    String dslr;
    int resister;
    int d1,d2,d3,d4;
    public Pair(String dslr, int resister){
        this.dslr = dslr;
        this.resister = resister;
        this.d4 = (resister%10);
        this.d3 = (resister/10)%10;
        this.d2 = (resister/100)%10;
        this.d1 = resister/1000;
    }
    public Pair(String dslr, int d1, int d2, int d3, int d4, int resister) {
        this.dslr = dslr;
        this.d1 = d1;
        this.d2 = d2;
        this.d3 = d3;
        this.d4 = d4;
        this.resister =resister;
    }

}
```

## 엘리베이터 틀림
``` java
package com.company;

import java.io.*;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(bf.readLine());
        int N = Integer.parseInt(st.nextToken()); // 최대 층수
        int M = Integer.parseInt(st.nextToken()); // 엘리베이터 수
        int[][] elevator = new int[M+1][N+1];
        boolean[] visited = new boolean[M+1];
        for (int i = 1; i <= M; i++) {
            st = new StringTokenizer(bf.readLine());
            int start = Integer.parseInt(st.nextToken());
            int term = Integer.parseInt(st.nextToken());
            for (int j = start; j <= N; j+=term) {
                elevator[i][j] = 1;
            }
        }

        Queue<Pair> queue = new LinkedList<>();

        st = new StringTokenizer(bf.readLine());
        int A = Integer.parseInt(st.nextToken());
        int B = Integer.parseInt(st.nextToken());

        for (int i = 1; i <= M; i++) { // i는 엘리베이터 번호
            if(elevator[i][A] == 1) {
                queue.offer(new Pair(i,Integer.toString(i)));
                visited[i]=true;
            }
        }
        while (!queue.isEmpty()){
            Pair pair = queue.poll();
            for (int i = 1; i <= N; i++) { // 엘리베이터 층수
                if(elevator[pair.elevator][i] == 1){ //  엘리베이터에서 갈수 있는 층 찾기
                    if(i == B){ // 가고자 하는 층이면,
                        bw.write(pair.visited.length() + "\n");
                        for (int j = 0; j < pair.visited.length() ; j++) {
                            bw.write(""+ pair.visited.charAt(j)+"\n");
                        }
                        bw.close();
                        return;
                    }
                    for (int j = 1; j <= M; j++) { // 엘리베이터 수
                        if(elevator[j][i]==1){
                            if(!visited[j]){
                                queue.offer(new Pair(j,pair.visited + ""+ j));
                                visited[j] = true;
                            }
                        }
                    }
                }
            }

        }
        bw.write("-1\n");
        bw.close();

    }
}
class Pair{
    int elevator;
    String visited;
    public Pair(int elevator, String visited){
        this.elevator = elevator;
        this.visited = visited;

    }
}
```