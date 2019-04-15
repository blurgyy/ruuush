#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;
const int dx[] = {0, 1, 1, 1, 0};
const int dy[] = {-1, -1, 0, 1, 1};
const char *ans[] = {"No", "Yes"};

int T, m, n, h, w0;
int brick[maxn][maxn];
int vis[maxn][maxn];
struct A{
    A(int _row = 1, int _col = 1, int _w = w0):
        col(_col), row(_row), w(_w){}
    int row;
    int col;
    int w;
};

bool inrange(int x, int y){return x >= 1 && x <= m+h+1 && y >= 1 && y <= n;}

void out(int x = -1, int y = -1){
    printf("##############################################\n");
    for(int i = 1; i <= h+m; ++ i){
        for(int j = 1; j <= n; ++ j){
            if(i == x && j == y) printf("* ");
            else printf("%d ", brick[i][j]);
        }
        printf("\n");
    }
}

bool bfs(){
    memset(vis, -1, sizeof(vis));
    queue<A> que;
    vis[1][1] = w0;
    que.push(A(1, 1, w0));
    while(!que.empty()){
        A now = que.front();
        int row = now.row;
        int col = now.col;
        int w = now.w;
        que.pop();
        if(brick[row][col-1] == 1 && brick[row][col+1] == 1 && brick[row+1][col] == 1){
            continue;
        }
        if(row == m + h + 1){
            return true;
        }
        for(int d = 0; d < 5; ++ d){
            int nrow = row + dx[d];
            int ncol = col + dy[d];
            if(d >= 1 && d <= 3){
                if(inrange(nrow, ncol) && brick[nrow][ncol] == 0){
                    if(d == 1 && brick[row][col-1] == 1) continue;
                    if(d == 3 && brick[row][col+1] == 1) continue;
                    if(vis[nrow][ncol] < w){
                        vis[nrow][ncol] = w;
                        que.push(A(nrow, ncol, w));
                    }
                }
            }
            else if(w > 0){
                if(inrange(nrow, ncol) && brick[nrow][ncol] == 0){
                    if(vis[nrow][ncol] < w-1){
                        vis[nrow][ncol] = w - 1;
                        que.push(A(nrow, ncol, w-1));
                    }
                }
            }
        }
    }
    return false;
}

int main(){
    scanf("%d", &T);
    while(T --){
        memset(brick, 0, sizeof(brick));
        scanf("%d%d%d%d", &n, &m, &h, &w0);
        n ++;
        for(int i = h+m; i >= h+1; -- i){
            for(int j = 1; j <= n; ++ j){
                scanf("%d", brick[i] + j);
            }
        }
        printf("%s\n", ans[bfs()]);
    }
    return 0;
}
