#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, p, query;
int num[maxn];
int And, Or, Xor;
int ans1, ans2, ans3;

bool Find1(int index, int bit){
	for(int i = 1; i <= n; ++i){
		if(i == index)continue;
		if(num[i]&(1<<bit))return true;
	}
	return false;
}

bool Find0(int index, int bit){
	for(int i = 1; i <= n; ++i){
		if(i == index)continue;
		if(!(num[i]&(1<<bit)))return true;
	}
	return false;
}

int main(){
	while(~scanf("%d%d", &n, &p)){
		for(int i = 1; i <= n; i++){
			scanf("%d", num + i);
			if(i > 1){
				And = And&num[i];
				Or = Or|num[i];
				Xor = Xor^num[i];
			}
			else{
				And = Or = Xor = num[1];
			}
		}
		ans1 = And;
		ans2 = Or;
		ans3 = Xor;
		while(p--){
			scanf("%d", &query);
			And = ans1;
			Or = ans2;
			Xor = ans3;
			for(int i = 0; i < 32; ++ i){
				if(!(num[query]&(i<<i))){///If current bit is "0"
					if(!Find0(query, i))And |= (1<<i);
				}
				if(num[query]&(1<<i)){///If current bit is "1"
					if(!Find1(query, i))Or &= ~(1<<i);
				}
			}
			Xor ^= num[query];
			printf("%d %d %d\n", And, Or, Xor);
		}
	}
	return 0;
}

/**

Sample Input:
5 5
684 489465 48 6487 165
1 2 3 4 5

Sample Output:
0 491519 486971
0 7167 7022
0 491519 486567
32 489469 488896
0 491519 486450

*/