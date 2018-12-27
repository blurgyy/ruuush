#include <bits/stdc++.h>
using namespace std;

int n;

int main(){
    while(~scanf("%d", &n)){
        bool ans = false;
        while(n --){
            int x;
            scanf("%d", &x);
            ans = ans || x;
        }
        if(ans){
            printf("HARD\n");
        }
        else {
            printf("EASY\n");
        }
    }
    return 0;
}