#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	char ma[5];
	int level;
	int star;
	int li[100] = {10001000, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2};
	int mark;

	level = 25;
	star = 0;
	mark = 0;

	while(scanf("%s", ma) == 1){
		if(ma[0] == '0'){
			break;
		}
		if(ma[0] == 'W'){
			mark ++;
			if(level >= 6 && level <= 25){
				if(mark >= 3){
					star += 2;
				}
			}
			else{
				star ++;
			}
			if(star > li[level]){
				star = 1;
				level ++;
			}
		}
		if(ma[0] == 'L'){
			mark = 0;
			if(level > 20){
				continue;
			}
			else{
				star --;
				if(star < 0){
					if(level == 20 || level == 0){
						star = 0;
					}
					else{
						level ++;
						star = li[level] - 1;
					}
				}
			}
		}
	}
	if(level == 0){
		printf("Legend\n");
	}
	else{
		printf("%d\n", level);
	}


	return 0;
}