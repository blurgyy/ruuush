#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

struct node{
    int x, y;
}ans;
int n;
int maxx;

int main(){
    while(~scanf("%d", &n)){
        maxx = -1;
        int x, y;
        for(int i = 0; i < n; ++ i){
            scanf("%d%d", &x, &y);
            int cur = x + y;
            if(maxx < cur){
                ans.x = x;
                ans.y = y;
                maxx = cur;
            }
        }
        printf("%d\n", maxx);
    }
    return 0;
}