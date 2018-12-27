#include <windows.h>

int main(){
    while(true){
        system("datagen > data.dat");
        system("3 < data.dat > my.out");
        system("key < data.dat > ans.out");
        if(system("fc my.out ans.out"))break;
    }
}