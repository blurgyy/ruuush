#include <windows.h>
using namespace std;

int main(){
    while(true){
        system("datagen > data.dat");
        system("3 < data.dat > tle.out");
        system("std < data.dat > std.out");
        if(system("fc tle.out std.out"))break;
    }
    return 0;
}