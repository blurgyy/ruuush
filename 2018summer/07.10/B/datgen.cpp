#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("in.in", "w", stdout);
	srand(time(NULL));
	printf("100\n");
	int sgn[2] = {1, -1};

	int t = 100;
	while(t --){
		int n = rand() % 16 + 1;
		printf("%d %d\n", n, rand() % 3601);
		n --;
		printf("%d ", rand() % 3601);
		while(n --){
			printf("%d ", sgn[(rand() % 3)&1] * (rand() % 3601));
		}
		printf("\n");
	}

	fclose(stdout);
	return 0;
}