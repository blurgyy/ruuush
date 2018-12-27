#include<bits/stdc++.h>
using namespace std;

double prob[6][6], ans;
int ob, Prev;
char c;

void init(){
	memset(prob, 0, sizeof(prob));
	Prev = 0;
	ans = 1;
}

int main(){
	for(int i = 1; i <= 4; ++ i)
		for(int j = 1; j <= 4; ++ j)
			scanf("%lf", prob[i] + j);
	ans = 1;
	Prev = 0;
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
	ans = 1;
	Prev = 0;
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
	int state;
	scanf("%d", &state);
	printf("%.8f\n", (double)1 / (1-prob[state][state]));
	scanf("%d", &state);
	printf("%.8f\n", (double)1 / (1-prob[state][state]));
	return 0;
}