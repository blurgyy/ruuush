#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    freopen("in.in", "w", stdout);
    int T = 20;
    printf("20 100\n");
    while(T --){
        printf("40000\n");
        for(int i = 0; i < 40000; ++ i)
            printf("%d ", rand() % 88 + 1);
        printf("\n");
    }
    return 0;
}