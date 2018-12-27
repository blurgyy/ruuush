#include <cstdio>
#include <cstring>
#include <windows.h>

int pow10(int lev){
	int base = 1;
	while(lev --)
		base *= 10;
	return base;
}

int main(){
	char s[1010];
	while(~scanf("%s", s)){
		int len = strlen(s);
		int pos = 0, acc = 0, cnt = 0;
		bool valid = true;
		for(int i = 0; i < len; ++ i){
			if(s[i] != '.' && (s[i] < '0' || s[i] > '9')){
				valid = false;
				break;
			}
			if(s[i] == '.'){
				if(acc == 0){
					valid = false;
					break;
				}
				pos = 0;
				acc = 0;
				cnt ++;
				continue;
			}
			acc *= 10;
			acc += s[i] - '0';
			if(acc > 999){
				valid = false;
				break;
			}
		}
		if(cnt != 3){
			valid = false;
		}
		if(valid)break;
		printf("Invalid IP address.\n");
	}
	char op[1010] = {"ping "};
	strcat(op, s);
	strcat(op, " -t");
	system(op);
	return 0;
}