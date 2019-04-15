#include <bits/stdc++.h>
using namespace std;

char randch(){
	return 'a' + rand() % 26;
}

int main(){
	int T = 1000;
	srand(time(NULL));
	while(T --){
		printf("%c", randch());
	}
	return 0;
}