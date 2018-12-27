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
    int T = 100000;
    printf("%d\n", T);
    while(T --){
        gen();
    }
    return 0;
}