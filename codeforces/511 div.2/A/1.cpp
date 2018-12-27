#include <bits/stdc++.h>
using namespace std;

int n;

int main(){
    while(~scanf("%d", &n)){
        if(n % 3 == 0){
            printf("1 1 %d\n", n - 2);
        }
        else if(n % 3 == 1){
            printf("1 1 %d\n", n - 2);
        }
        else if(n % 3 == 2){
            printf("1 2 %d\n", n - 3);
        }
    }
    return 0;
}