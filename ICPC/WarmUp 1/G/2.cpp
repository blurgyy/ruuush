#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;

char seq[maxn];
int Stars[30] = {0};
int wl[maxn], cur_star, cswin, level;

int main(){
	for(int i = 25; i >= 1; -- i)
		if(i <= 10)Stars[i] = Stars[i+1] + 5;
		else if(i <= 15)Stars[i] = Stars[i+1] + 4;
		else if(i <= 20)Stars[i] = Stars[i+1] + 3;
		else if(i <= 25)Stars[i] = Stars[i+1] + 2;
	/*for(int i = 0; i < 26; ++ i)
		printf("a[%d] = %d\n", i, Stars[i]);*/
	while(~scanf("%s", seq)){
		memset(wl, 0, sizeof(wl));
		Stars[0] = maxn;
		cur_star = cswin = 0;
		level = 25;
		int len = strlen(seq);
		for(int i = 0; i < len; ++ i){
			if(cur_star > 95)break;
			if(seq[i] == 'W'){
				++ cur_star;
				++ cswin;
				if(cswin >= 3){
					if(cur_star <= Stars[6]){
						++ cur_star;
					}
				}
			}
			else{
				cswin = 0;
				if(cur_star <= Stars[21])continue;
				//if(cur_star == Stars[21])continue;
				-- cur_star;
			}
			//printf("cur_star = %d\n", cur_star);
		}
		if(cur_star > 95)
			printf("Legend\n");
		else{
			int pos;
			for(int i = 25; i >= 1; -- i)
				if(cur_star <= Stars[i]){
					if(cur_star <= Stars[21]){
						if(cur_star == Stars[21]){
							if(seq[len-1] == 'L')
								pos = 20;
							else pos = 21;
						}
						else pos = i;
						break;
					}
					if(cur_star == Stars[i]){
						if(seq[len-1] == 'L')
							pos = i - 1;
						else pos = i;
					}
					else pos = i;
					break;
				}
			printf("cur_star = %d\n", cur_star);
			printf("%d\n", pos);
		}
	}
	return 0;
}

/**

a[1] = 95
a[2] = 90
a[3] = 85
a[4] = 80
a[5] = 75
a[6] = 70
a[7] = 65
a[8] = 60
a[9] = 55
a[10] = 50
a[11] = 45
a[12] = 41
a[13] = 37
a[14] = 33
a[15] = 29
a[16] = 25
a[17] = 22
a[18] = 19
a[19] = 16
a[20] = 13
a[21] = 10
a[22] = 8
a[23] = 6
a[24] = 4
a[25] = 2

*/