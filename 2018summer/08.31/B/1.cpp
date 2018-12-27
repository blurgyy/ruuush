#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
const int dx = -1;
const int dy = 1;
const int adx[] = {0, 1, 0, -1};
const int ady[] = {1, 0, -1, 0};

int N;
char s[maxn][maxn];
char ans[maxn][maxn];

bool oor(int x, int y){
    return !(x >= 1 && x <= N && y >= 1 && y <= N) || ans[x][y] != 0;
}

void init(){
    memset(ans, 0, sizeof(ans));
}

int main(){
    while(~scanf("%d", &N)){
        init();
        for(int i = 1; i <= N; ++ i){
            scanf("%s", s[i] + 1);
        }
        if(N == 1){
            printf("%c\n", s[1][1]);
            continue;
        }
        ans[1][1] = s[1][1];
        int x = 1, y = 1;
        int d = 1, ad = 0;
        int ax = 1, ay = 1;
        while(true){
            //printf("in loop\n");
            //printf("%c", s[x][y]);
            //printf("(%d, %d), %d\n", x, y, d);
            int nx = x + d * dx;
            int ny = y + d * dy;
            //printf("(%d, %d), %d\n", nx, ny, d);
            bool flag = false;
            if(nx < 1 || ny < 1){
                flag = true;
                d *= -1;
                nx = max(1, nx);
                ny = max(1, ny);
            }
            if(nx == N + 1 || ny == N + 1){
                if(!flag)d *= -1;
                //printf("%d, %d, d = %d\n", nx, ny, d);
                if(nx < ny){
                    nx = x + 1;
                    ny = y;
                }
                else {
                    nx = x;
                    ny = y + 1;
                }
            }
            int nax = ax + adx[ad];
            int nay = ay + ady[ad];
            if(oor(nax, nay)){
                ad = (ad + 1) % 4;
                nax = ax + adx[ad];
                nay = ay + ady[ad];
            }
            ans[nax][nay] = s[nx][ny];
            x = nx;
            y = ny;
            ax = nax;
            ay = nay;
            if(x == N && y == N)break;
            //printf("x = %d, y = %d\n", x, y);
        }
        for(int i = 1; i <= N; ++ i){
            //for(int j = 1; j <= N; ++ j){
            //    printf("%c", ans[i][j]);
            //}
            //printf("\n");
            printf("%s\n", ans[i] + 1);
        }
    }
    return 0;
}