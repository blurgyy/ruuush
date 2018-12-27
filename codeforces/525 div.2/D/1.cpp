#include <bits/stdc++.h>
using namespace std;
const int maxl = 40;

int verdict;
int origverd;
bool diff[maxl];

int getc(int pos){
	int ret = 1 << pos;
	if(origverd == 1){
		for(int i = 0; i < maxn; ++ i){
			if(diff[i]){
				ret |= (1<<i);
			}
		}
	}
	return ret;
}

int getd(int pos){
	int ret = 1 << pos;
	if(origverd == -1){
		for(int i = 0; i < maxn; ++ i){
			if(diff[i]){
				ret |= (1<<i);
			}
		}
	}
	return ret;
}

int samec(int pos){
	int ret = 0;
	for(int i = 0; i < maxn; ++ i){
		if(diff[i]){
			ret |= 1;
		}
	}
}

int main(){
	memset(diff, false, sizeof(diff));

	for(int i = 1; i <= 62; ++ i){
		if(i == 1){
			printf("? 0 0\n");
			scanf("%d", &verdict);
			origverd = verdict;
		}
		else {
			for(int j = 30; j >= 0; -- j){
				printf("? %d %d\n", getc(j), getd(j));
				scanf("%d", &verdict);
				if(verdict != origverd){
					diff[j] = true;
				}
			}
			for(int j = 30; j >= 0; -- j){
				if(diff[j] == false)continue;
				printf("? %d %d\n", samec(j), samed(j));
				scanf("%d", &verdict);

			}
		}
	}
	return 0;
}