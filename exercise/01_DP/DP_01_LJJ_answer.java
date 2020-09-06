class Solution {
    public int solution(int[] money) {
        int answer = 0;
        int last = money.length;
        int[] DP = new int[last+1];
        DP[0] = 0;
        DP[1] = money[1];
        for(int j=0;j<2;j++){ 
            for(int i=2;i<last;i++){
                if((money[i]+DP[i-2])>DP[i-1])
                    DP[i] = money[i]+DP[i-2];
                else
                    DP[i]=DP[i-1];
                }
            DP[0]=money[0];
            DP[1]=DP[0];
            last--;
        }
        if(DP[last]>DP[last+1])
            answer = DP[last];
        else answer = DP[last+1];
        return answer;
    }
}