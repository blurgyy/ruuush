#include<bits/stdc++.h>
using namespace std;

double prob[6][6], ans;
int ob, Prev, state;
char c = 0;

void init(){
	Prev = 0;
	ans = 1;
}

void input(){
	for(int i = 1; i <= 4; ++ i)
		for(int j = 1; j <= 4; ++ j)
			scanf("%lf", prob[i] + j);
}

int main(){
	input();
	for(int i = 0; i < 2; ++ i){
		init();
		while(1){
			scanf("%d", &ob);
			c = getchar();
			if(Prev){
				ans *= prob[Prev][ob];
			}
			Prev = ob;
			if(c == 10)break;
		}
		printf("%.8f\n", ans);
	}
	for(int i = 0; i < 2; ++ i){
		scanf("%d", &state);
		printf("%.8f\n", (double)1 / (1-prob[state][state]));
	}
	return 0;
}