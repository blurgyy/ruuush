#include <bits/stdc++.h>
using namespace std;

int main(){
    while(true){
        system("datagen > data.dat");
        system("ans < data.dat > ans.out");
        system("1 < data.dat > 1.out");
        if(system("fc 1.out ans.out"))break;
    }
    system("pause");
    return 0;
}