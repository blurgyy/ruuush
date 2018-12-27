///我认为有必要把这个T的版本记录下来。。。
///STL各种奇妙TLE...我一开始还以为是我死循环
///其实是我在遍历我的的set<int> ans时给T了。。。
///WTFFF

#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 400010;

char name[maxn];
int Next[maxn];
set<int> ans;

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
		ans.clear();
		int len = strlen(name);
		ans.insert(len);
		if(name[0] == name[len-1])ans.insert(1);
		int i = len-1;
		while(true){
			if(Next[i] == 0)break;
			if(name[i] == name[Next[i]]){
				ans.insert(Next[i]+1);
				i = Next[i];
			}
			else break;
		}
		set<int>::iterator iter;
		for(iter = ans.begin(); iter != ans.end(); ++iter)
			if(iter == ans.begin())printf("%d", (*iter));
			else printf(" %d", (*iter));
		printf("\n");
	}
	return 0;
}

/**

ababcababababcabab
aaaaa
anvdanvand

*/