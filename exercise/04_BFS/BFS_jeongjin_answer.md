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