#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 400010;

char name[maxn];
int Next[maxn];
int p;
set<int> ans;

void Get_Next(){
	int i = 0, j = -1;
	int len = strlen(name);
	memset(Next, 0, sizeof(Next));
	Next[0] = -1;
	while(i < len-1){
		if(j == -1 || name[i] == name[j])
			Next[++i] = ++j;
		else j = Next[j];
	}
}

void init(){
	memset(name, 0, sizeof(name));
	memset(Next, 0, sizeof(Next));
	p = 0;
}

void out(){
	int len = strlen(name);
	printf("len = %d\n", len);
	for(int i = 0; i < len; ++ i)
		printf("%d ", Next[i]);
	printf("\n");
}

int main(){
	while(~scanf("%s", name)){
		Get_Next();
		ans.clear();
		int len = strlen(name);
		ans.insert(len);
		int nxt;
		if(Next[len-1] > 0){
			nxt = Next[len-1];
			while(nxt > 0){
				if(Next[nxt] > 0)ans.insert(nxt+1);
				else break;
				char tmp = name[nxt];
				nxt = Next[nxt];
				if(name[nxt] != tmp)break;
			}
		}
		if(name[0] == name[len-1])ans.insert(1);
		if(len > 1 && name[0] == name[len-2] && name[1] == name[len-1])ans.insert(2);
		for(set<int>::iterator i = ans.begin(); i != ans.end(); ++ i)
			if(i == ans.begin())printf("%d", (*i));
			else printf(" %d", (*i));
		printf("\n");
	}
	return 0;
}

/**

anvdanvand
and Sample input...

*/