#include <bits/stdc++.h>
using namespace std;

int x;

int main(){
    while(~scanf("%d", &x)){
        x %= 4;
        if(x == 1){
            printf("0 A\n");
        }
        else if(x == 3){
            printf("2 A\n");
        }
        else if(x == 2){
            printf("1 B\n");
        }
        else if(x == 0){
            printf("1 A\n");
        }
    }
    return 0;
}
