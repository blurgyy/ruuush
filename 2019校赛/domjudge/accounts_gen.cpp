#include <bits/stdc++.h>
using namespace std;
const int len = 6;

char orand(){
	if(rand() % 36 < 26){
		return rand() % 26 + 'a' - (rand()&1) * 32;
	}
	return rand() % 10 + '0';
}

int main(){
	srand(time(NULL));
	printf("accounts\t1\n");
	for(int id = 1; id <= 80; ++ id){
		// printf("team\tt%d\tteam%03d\t", id+6, id);
		printf("team\tteam%03d\tteam%03d\t", id, id);
		// printf("team%03d", id);
		for(int i = 0; i < len; ++ i){
			printf("%c", orand());
		}
		printf("\n");
	}
	return 0;
}