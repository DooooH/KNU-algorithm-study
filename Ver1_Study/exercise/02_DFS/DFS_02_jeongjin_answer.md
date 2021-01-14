
    class Solution {
        int[][] visited;
        int[][] board2; 
        public int solution(int[][] board) {
            int N = board.length;
            visited = new int[N][N];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    visited[i][j] = 99999999;
                }
            }
            visited[0][0]=0;
            board2 = board;
            if(board2[0][1] != 1)
                board2[0][0] = 2;
            visit(0,1,board2[0][0]);

            if(board2[1][0] !=1)
                board2[0][0] = 3;
            visit(1,0, board2[0][0]);

        //System.out.println(visited[0][0]);
            return visited[N-1][N-1];
        }
        
        int visit(int i, int j, int dir)   {
            // RIGHT : 2, DOWN : 3, LEFT : 4, UP : 5
            int tmp = 0;

            if(i < 0 || j < 0 || i == board2.length || j == board2.length)
                return 0;
            if(board2[i][j] == 1)
                return 0;

            if(dir == 2) {
                if (board2[i][j - 1] == dir)
                    tmp = visited[i][j - 1] + 100;
                else
                    tmp = visited[i][j - 1] + 600;

                if(visited[i][j] >= tmp && tmp <= visited[board2.length-1][board2.length-1]) {
                    visited[i][j] = tmp;
                    board2[i][j] = dir;
                }
                else
                    return 0;
                visit(i,j+1,2);
                visit(i+1,j,3);
                visit(i-1,j,5);
            }
            if(dir == 3) {
                if (board2[i - 1][j] == dir)
                    tmp = visited[i - 1][j] + 100;
                else
                    tmp = visited[i - 1][j] + 600;
                if(visited[i][j] >= tmp && tmp <= visited[board2.length-1][board2.length-1]) {
                    visited[i][j] = tmp;
                    board2[i][j] = dir;
                }
                else
                    return 0;
                visit(i,j+1,2);
                visit(i+1,j,3);
                visit(i,j-1,4);
            }
            if(dir == 4) {
                if (board2[i][j + 1] == dir)
                    tmp = visited[i][j + 1] + 100;
                else
                    tmp = visited[i][j + 1] + 600;
                if(visited[i][j] >= tmp && tmp <= visited[board2.length-1][board2.length-1]) {
                    visited[i][j] = tmp;
                    board2[i][j] = dir;
                }
                else
                    return 0;
                visit(i+1,j,3);
                visit(i,j-1,4);
                visit(i-1,j,5);
            }
            if(dir == 5) {
                if (board2[i + 1][j] == dir)
                    tmp = visited[i + 1][j] + 100;
                else
                    tmp = visited[i + 1][j] + 600;
                if(visited[i][j] >= tmp && tmp <= visited[board2.length-1][board2.length-1]) {
                    visited[i][j] = tmp;
                    board2[i][j] = dir;
                }
                else
                    return 0;
                visit(i,j+1,2);
                visit(i,j-1,4);
                visit(i-1,j,5);

            }

            return 0;
        }
    }