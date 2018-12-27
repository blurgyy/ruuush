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
        //printf("%d %d\n", x, y);
        for(int i = 0; i < n; ++ i){
            if(x == 0 || y == 0)break;
            x -= (d[i] == a[i]);
            y -= (d[i] == a[i]);
        }
        //printf("x = %d, y = %d\n", x, y);
        int cntx = 0, cnty = 0;
        for(int i = 0; i < n; ++ i){
            if(d[i] != a[i]){
                if(cntx < x)
                    cntx ++;
                else if(cnty < y)
                    cnty ++;
            }
            else if(cntx < x && cnty < y){
                cntx ++;
                cnty ++;
            }
            if(cntx == x && cnty == y)break;
        }
        printf("nx = %d, ny = %d\n", cntx, cnty);
        if(cntx == x && cnty == y){
            printf("Not lying\n");
        }
        else printf("Lying\n");
    }
    return 0;
}