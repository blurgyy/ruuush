#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n, in[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", in + i);
        }
        if(n == 1){
            if(in[0] == 15)
                printf("DOWN\n");
            else if(in[0] == 0)printf("UP\n");
            else printf("-1\n");
            continue;
        }
        if(in[n-1] - in[n-2] > 0){
            if(in[n-1] == 15)printf("DOWN\n");
            else printf("UP\n");
        }
        else{
            if(in[n-1] == 0)printf("UP\n");
            else printf("DOWN\n");
        }
    }
    return 0;
}