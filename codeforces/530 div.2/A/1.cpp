#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int w, h;
int u1, d1;
int u2, d2;

int main(){
    while(~scanf("%d%d%d%d%d%d", &w, &h, &u1, &d1, &u2, &d2)){
        for(int i = h; i; -- i){
            w += i;
            if(d1 == i){
                w -= u1;
                w = max(0, w);
            }
            if(d2 == i){
                w -= u2;
                w = max(0, w);
            }
        }
        printf("%d\n", w);
    }
    return 0;
}