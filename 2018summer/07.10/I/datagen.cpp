#include <bits/stdc++.h>
using namespace std;

int main(){
    //freopen("data.dat", "w", stdout);
    int t = 100;
    srand(time(NULL));
    printf("100\n");
    while(t --){
        printf("%d\n", rand() % 999999998 + 3);
    }
    return 0;
}