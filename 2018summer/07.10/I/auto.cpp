#include <cstdio>
#include <windows.h>

int main(){
    while(true){
        system("datagen > data.dat");
        system("1 < data.dat > out.out");
        system("judge < out.out");
    }
    return 0;
}