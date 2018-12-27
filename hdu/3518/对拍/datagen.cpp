#include<bits/stdc++.h>
using namespace std;

int main(){
	srand(time(NULL));
	int t = rand() % 1000 + 1;
	while(t --){
		int len = rand() % 1000 + 1;
		while(len --)
			printf("%c", 'a' + rand() % 26);
		printf("\n");
	}
	printf("#\n");
	return 0;
}