#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

int main(){
	srand(time(NULL));
	for(int ii = 0; ii < 20; ii++){
		int repeat = rand() % 100 + 1;
		int len = rand() % 9 + 1;
		char s[40] = {0};
		for(int i = 0; i < len; i++)
			s[i] = 'a' + rand() % 26;
		while(repeat--)
			printf("%s", s);
		printf("\n");
	}
	printf(".\n");
	return 0;
}