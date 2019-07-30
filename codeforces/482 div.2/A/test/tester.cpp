#include <bits/stdc++.h>
using namespace std;

int main(){
    while(true){
        system("dg > data.dat");
        system("1 < data.dat > 1.out");
        system("2 < data.dat > 2.out");
        if(system("fc 1.out 2.out"))break;
    }
    return 0;
}