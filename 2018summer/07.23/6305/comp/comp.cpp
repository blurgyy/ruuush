//#include <bits/stdc++.h>
#include <windows.h>

int main(){
	while(true){
		system("datagen > data.dat");
		system("wa < data.dat > wa.out");
		system("std < data.dat > std.out");
		if(system("fc wa.out std.out"))break;
	}
	system("pause");
	return 0;
}