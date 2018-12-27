#include <bits/stdc++.h>
using namespace std;
const int maxn = 40;

int verd, lastv;
int c, d;
bool defed[maxn];

int main(){
	int ca = 0;
	c = d = 0;
	memset(defed, false, sizeof(defed));
	while(true){
		if(ca == 0){
			printf("? 0 0\n");
			fflush(stdout);
			scanf("%d", &verd);
			lastv = verd;
		}
		else {
			for(int i = 29; i >= 0; -- i){
				printf("? %d %d\n", c|(1<<i), d|(1<<i));
				fflush(stdout);
				scanf("%d", &verd);
				if(lastv != verd){
					defed[i] = true;
					if(lastv == 1){
						c |= 1<<i;
					}
					else if(lastv == -1){
						d |= 1<<i;
					}
					else {
						printf("wtf\n");
					}
					printf("? %d %d\n", c, d);
					fflush(stdout);
					scanf("%d", &verd);
					if(verd == 0){
						break;
					}
					lastv = verd;
				}
			}
			for(int i = 0; i < 30; ++ i){
				if(defed[i])continue;
				printf("? %d %d\n", c|(1<<i), d);
				fflush(stdout);
				scanf("%d", &verd);
				if(verd == -1){
					c |= 1<<i;
					d |= 1<<i;
				}
			}
			break;
		}
		ca ++;
	}
	// fflush(stdout);
	printf("! %d %d\n", c, d);
	return 0;
}