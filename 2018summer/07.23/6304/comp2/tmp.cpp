#include <cstdio>
#include <algorithm>
#include <time.h>
using namespace std;

void gen(){
    int len = rand() % 18 + 1;
    printf("%d", rand() % 9 + 1);
    len --;
    while(len --){
        printf("%c", '0' + rand() % 10);
    }
    printf("\n");
}

int main(){
    freopen("data.dat", "w", stdout);
    printf("1000000\n");
    for(int i = 1; i <= 100000; ++ i){
        printf("1000000000000000000\n");
    }
    return 0;
}