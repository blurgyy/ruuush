///前面一直T...
///当我把set<int> ans 改成了 int ans[maxn]后。。。就A了
///扶额
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 400010;

char name[maxn];
int Next[maxn];
int ans[maxn], p;

void GetNext(){
	int i = 0, j = -1;
	memset(Next, 0, sizeof(Next));
	Next[0] = -1;
	int len = strlen(name);
	while(i < len-1){
		if(j == -1 || name[i] == name[j])
			Next[++i] = ++j;
		else j = Next[j];
	}
}

int main(){
	while(~scanf("%s", name)){
		GetNext();
		memset(ans, 0, sizeof(ans));
		p = 0;
		int len = strlen(name);
		ans[p++] = len;
		if(name[0] == name[len-1])ans[p++] = (1);
		int i = len-1;
		while(true){
			if(Next[i] == 0)break;
			if(name[i] == name[Next[i]]){
				ans[p++] = Next[i] + 1;
				i = Next[i];
			}
			else break;
		}
		sort(ans, ans + p);
		printf("%d", ans[0]);
		for(int i = 1; i < p; ++ i)
			if(ans[i] != ans[i-1])printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}

/**

ababcababababcabab
aaaaa
anvdanvand

*/