#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int ncase;
	int a, b, c, d;

	ncase = 630;
	printf("%d\n", ncase);
	while(ncase --){
		// a = rand() % 100 + 1;
		// b = rand() % 100 + 1;
		a = b = 100;
		c = rand() % 100 + 1;
		d = rand() % 10 + 1;
		printf("%d %d %d %d\n", a, b, c, d);
		for(int i = 0; i < b; i ++){
			for(int i = 0; i < a; i ++){
				if(rand() % 10 < 5){
					printf("1 ");
				}
				else{
					printf("0 ");
				}
			}
			printf("\n");
		}
		printf("\n");
	}

	return 0;
}
