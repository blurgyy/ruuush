#include <bits/stdc++.h>
using namespace std;

int main(){
    while(true){
        system("gen > data.dat");
        system("3 < data.dat > 3.out");
        system("ans < data.dat > ans.out");
        if(system("fc 3.out ans.out"))break;
    }
    return 0;
}