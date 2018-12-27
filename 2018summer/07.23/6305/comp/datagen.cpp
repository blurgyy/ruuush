#include <cstdio>
#include <time.h>
#include <algorithm>
using namespace std;

int main(){
	srand(time(NULL));
	int T = rand() % 110 + 1;
	printf("%d\n", T);
	while(T --){
		int n = rand() % 9900 + 10;
		printf("%d\n", n);
		int tmp = n;
		while(n --){
			printf("%d ", rand() % (tmp - 1) + 1);
		}
		printf("\n");
	}
	return 0;
}