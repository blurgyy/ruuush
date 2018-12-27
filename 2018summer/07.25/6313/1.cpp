#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int n = 19;
    printf("%d\n", n);
    for(int i = 0; i < n; ++ i){
        for(int j = 0; j < n; ++ j){
            printf("%c", "01"[rand()&1]);
        }
        printf("\n");
    }
    return 0;
}