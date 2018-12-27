#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

int main(){
	srand(time(NULL));
	int time = 10;
	while(time--){
		int n = rand()%10 + 1;
		printf("%d %d\n", n, n);
		for(int i = 0; i < n; i++)
			printf("%d ", rand() % 1000000 + 1);
		printf("\n");
		for(int i = 0; i < n; i++)
			printf("%d ", rand() % n + 1);
	}
	return 0;
}