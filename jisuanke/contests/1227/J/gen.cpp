#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("in.in", "w", stdout);
    srand(time(NULL));
    printf("1\n41\n");
    for(int i = 0; i < 41; ++ i){
        for(int j = 0; j < 41; ++ j)
            printf("%d", rand()&1);
        printf("\n");
    }
}
