#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int T, n, x, y;
char d[maxn], a[maxn];

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d", &n, &x, &y);
        scanf("%s%s", d, a);
        int cntx = 0, cnty = 0;
        for(int i = 0; i < n; ++ i){
            if(x == 0 || y == 0)break;
            x -= d[i] == a[i];
            y -= d[i] == a[i];
        }
        for(int i = 0; i < n; ++ i){
            if(d[i] == a[i]){
                continue;
            }
            else{
                if(cntx < x){
                    cntx ++;
                }
                else if(cnty < y){
                    cnty ++;
                }
            }
            if(cntx == x && cnty == y)break;
        }
        if(cntx == x && cnty == y)printf("Not lying\n");
        else printf("Lying\n");
    }
    return 0;
}
