#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
    int Case = 0;
    while(true){
        printf("case %d...\n", ++ Case);
        usleep(100000);
        system("./gen > in.in");
        system("./dp < in.in > dp.out");
        system("./stk < in.in > stk.out");
        if(system("diff dp.out stk.out"))break;
    }
    return 0;
}