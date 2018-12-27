#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
	while(true){
		system("./gen > in.in");
		printf("[data generated]\n");
		system("./my < in.in");
		printf("[my finished]\n");
		system("./tutorial < in.in");
		printf("[tutorial finished]\n");
		sleep(1);
		system("clear");
	}
	return 0;
}