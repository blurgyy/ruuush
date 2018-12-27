#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
const int inf = 0x3f3f3f3f;

int n;
int a[maxn];
bool vis[maxn];
int cntneg, cntzro, cntall;
int negpos[maxn];
int zropos[maxn];

int main(){
    //while(~scanf("%d", &n)){
    scanf("%d", &n);{
        cntzro = 0;
        cntneg = 0;
        cntall = 0;
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            if(a[i] < 0){
                negpos[cntneg ++] = i;
            }
            if(a[i] == 0){
                zropos[cntzro ++] = i;
            }
        }
        if(cntzro){
            int posz = 0;   ///the only zero's position
            if(cntzro > 1){
                for(posz = 1; posz < cntzro; ++ posz){
                    if(cntall == n-1)return 0;
                    printf("1 %d %d\n", zropos[posz-1], zropos[posz]);
                    vis[zropos[posz-1]] = true;
                    cntall ++;
                }
                posz --;
            }
            if(cntneg & 1){

                int posn = -1, minabs = inf;
                for(int i = 0; i < cntneg; ++ i){
                    if(abs(a[negpos[i]]) < minabs){
                        minabs = abs(a[negpos[i]]);
                        posn = i;
                    }
                }
                
                if(cntall == n-1)return 0;
                printf("1 %d %d\n", zropos[posz], negpos[posn]);
                vis[zropos[posz]] = true;
                cntall ++;
                if(cntall == n-1)return 0;
                printf("2 %d\n", negpos[posn]);
                vis[negpos[posn]] = true;
                cntall ++;
            }
            else {
                if(cntall == n-1)return 0;
                printf("2 %d\n", zropos[posz]);
                vis[zropos[posz]] = true;
                cntall ++;
            }
        }
        else {
            if(cntneg){

                int posn = -1, minabs = inf;
                for(int i = 0; i < cntneg; ++ i){
                    if(abs(a[negpos[i]]) < minabs){
                        minabs = abs(a[negpos[i]]);
                        posn = i;
                    }
                }
                
                if(cntneg & 1){
                    if(cntall == n-1)return 0;
                    printf("2 %d\n", negpos[posn]);
                    vis[negpos[posn]] = true;
                    cntall ++;
                }
            }
        }
        int tot = 0;
        for(int i = 1; i <= n; ++ i){
            if(!vis[i]){
                a[tot++] = i;
            }
        }
        for(int i = 1; i < tot; ++ i){
            if(cntall == n-1)return 0;
            printf("1 %d %d\n", a[i-1], a[i]);
            vis[a[i-1]] = true;
            cntall ++;
        }
    }
    return 0;
}