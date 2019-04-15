#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 200010;

char ma[N];
char mb[N];

int main(int argc, char const *argv[])
{
	int ncase;
	int ans;
	int len;
	int cnt;
	int mark;
	int li;
	vector<int> V;

	scanf("%d", &ncase);
	while(ncase --){
		V.clear();
		cnt = 0;
		mark = 0;
		ans = 0;
		scanf("%s", ma);
		scanf("%s", mb);
		len = strlen(ma);
		li = len - 1;
		for(int i = 0; i < len; i ++){
            if(ma[i] >= 'a' && ma[i] <= 'z' && ma[i] != mb[0]){
                mark = 1;
                break;
            }
		}
		while(cnt < len){
			int num;

            if(mark){
                break;
            }
			num = 0;
			while(ma[cnt] == mb[0] && cnt < len){
				cnt ++;
			}
			if(cnt == len){
                break;
			}
	        if(ma[cnt] == '0' && ma[cnt + 1] >= '0' && ma[cnt + 1] <= '9'){
	            mark = 1;
	            break;
			}
			while(ma[cnt] != mb[0] && cnt < len){
				num = num * 10 + ma[cnt] - '0';
				if(num < 0){
                    break;
				}
				cnt ++;
			}
			if(num < 0){
                mark = 1;
                break;
			}
			V.pb(num);
		}
		if(mark){
            printf("bad qiangqiang\n");
		}
		else{
            ans = V.size();
            printf("%d\n", ans);
            for(int i = 0; i < ans; i ++){
                printf("%d\n", V[i]);
            }
		}
	}

	return 0;
}