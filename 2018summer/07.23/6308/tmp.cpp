#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("in.in", "w", stdout);
    int cnt = 0;
    int toph = 24, topm = 60;
    int xtop = 14, ytop = 10;
    for(int hh = 0; hh < toph; ++ hh){
        for(int mm = 0; mm < topm; ++ mm){
            for(int x = 0; x < xtop; ++ x){
                for(int y = 0; y < ytop; ++ y){
                    printf("%d %d UTC+%d", hh, mm, x);
                    if(y){
                        printf(".%d", y);
                    }
                    printf("\n");
                    cnt ++;
                }
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}