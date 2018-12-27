#include <bits/stdc++.h>
#define bug(a) printf("(%d)\n", (a))
using namespace std;

int idx[300];
int ans;
char s[110];

struct Trie
{
	bool isStr;
	Trie* Next[62];
}root;

void insert(char* s){
	bool NEW = false;
	Trie* p = &root;
	while(*s != 0){
		if(NULL == p->Next[idx[*s]]){
			if(!NEW)
				NEW = true;
			Trie* tmp = (Trie*) malloc(sizeof(Trie));
			memset(tmp->Next, 0, sizeof(tmp->Next));
			tmp->isStr = false;
			p->Next[idx[*s]] = tmp;
		}
		p = p->Next[idx[*s]];
		++ s;
	}
	p->isStr = true;
	if(NEW)++ ans;
}

void init(){
	int p = -1;
	for(int i = 'a'; i <= 'z'; ++ i)
		idx[i] = ++ p;
	for(int i = 'A'; i <= 'Z'; ++ i)
		idx[i] = ++ p;
	for(int i = '0'; i <= '9'; ++ i)
		idx[i] = ++ p;
	root.isStr = false;
	memset(root.Next, 0, sizeof(root.Next));
	ans = 0;
}

int main(){
	init();
	int time = 20001;
	while(--time){
		scanf("%s", s);
		insert(s);
	}
	printf("%d\n", ans);
	return 0;
}