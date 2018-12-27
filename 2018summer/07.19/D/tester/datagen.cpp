#include <cstdio>
#include <cstring>
#include <time.h>
#include <windows.h>

int main(){
    srand(time(NULL));
    int n = rand() % 1000000 + 1;
    printf("%d\n", n);
    while(n --){
        printf("%d ", rand() % 100000000 + 1);
    }
    printf("\n");
    return 0;
}