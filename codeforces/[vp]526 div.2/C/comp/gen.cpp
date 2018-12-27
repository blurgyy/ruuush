#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

char randch(){
	if(rand() % 15){
		return 'a' + (rand()&1);
	}
	return 'a' + rand() % 26;
}

int main(){
	srand(time(NULL));
	int len = 4;
	while(len < 100000) len = rand() % 1000000;
	for(int i = 0; i < len; ++ i)
		printf("%c", randch());
	return 0;
}