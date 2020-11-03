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


```