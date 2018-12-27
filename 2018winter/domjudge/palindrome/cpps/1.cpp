#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const char* _max = "4500000000";

void orand(){
	printf("%c", '0' + rand() % 10);
}

bool check(char *s){
	for(int i = 0; i < 10; ++ i){
		if(s[i] < _max[i]) return true;
	}
	return false;
}

void BCprint(){
	char o[20] = {0};
	int len = rand() % 10 + 1;
	if(len < 10){
		printf("-%c", rand() % 9 + 1 + '0');
		for(int i = 1; i < len; ++ i)
			orand();
		printf("\n");
		return;
	}
	while(true){
		o[1] = rand() % 4 + 1 +'0';
		for(int i = 2; i <= 10; ++ i){
			o[i] = rand()%10+'0';
		}
		if(check(o+1)) break;
	}
	o[0] = '-';
	puts(o);
}

void ACprint(){
	int len = rand() % 10000 + 1;
	while(len --){
		orand();
	}
	printf("\n");
}

int main(){
	srand(time(NULL));
	freopen("data.in", "w", stdout);
	int T = 10000;
	while(T --){
		if(rand()%10){
			ACprint();
		}
		else {
			BCprint();
		}
	}
	fclose(stdout);
	system("mv data.in ../testdata/");

	return 0;
}
