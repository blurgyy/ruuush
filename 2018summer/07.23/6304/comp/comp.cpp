#include <bits/stdc++.h>
using namespace std;

int main(){
	while(true){
		system("datagen > data.dat");
		system("2 < data.dat > wa.out");
		system("std < data.dat > std.out");
		if(system("fc wa.out std.out"))break;
	}
	return 0;
}