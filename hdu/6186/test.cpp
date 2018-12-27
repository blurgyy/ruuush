#include <cstdio>
const int maxn = 100010;
const int FULLBITS = 0x7fffffff;

int n, q, query;
int num[maxn];

int main(){

	printf("%d\n", 684&489465&6487&165);

	while(~scanf("%d%d", &n, &q)){
		for(int i = 0; i < n; i++)
			scanf("%d", num + i);
		while(q--){
			scanf("%d", &query);
			int And = FULLBITS, Or = 0, Xor = 0;
			for(int i = 0; i < n; i++){
				if(i == query-1)continue;
				And &= num[i];
				Or |= num[i];
				Xor ^= num[i];
			}
			printf("%d %d %d\n", And, Or, Xor);
		}
	}
	return 0;
}

/**

5 5
684 489465 48 6487 165
1 2 3 4 5

0 491519 486971
0 7167 7022
0 491519 486567
32 489469 488896
0 491519 486450

*/