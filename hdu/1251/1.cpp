///All MLE

#include <cstdio>
#include <cstring>
#include <malloc.h>

struct Trie
{
	Trie* Next[26];
	int cnt;
}root;
char str[10];

void Insert(char* s){
	Trie* p = &root;
	while(*s != 0){
		if(p->Next[*s-'a'] == NULL){
			Trie* tmp = (Trie*) malloc(sizeof(Trie));
			tmp->cnt = 0;
			memset(tmp->Next, 0, sizeof(tmp->Next));
			p->Next[*s-'a'] = tmp;
		}
		p = p->Next[*s-'a'];
		++ s;
		++ (p->cnt);
	}
}

int Find(char* s){
	Trie* p = &root;
	while(*s != 0){
		if(p->Next[*s-'a'] == NULL)return 0;
		p = p->Next[*s-'a'];
		++ s;
	}
	return p->cnt;
}

int main(){
	memset(root.Next, 0, sizeof(root.Next));
	root.cnt = 0;
	while(gets(str) && str[0] != 0){
		Insert(str);
	}
	while(~scanf("%s", str)){
		printf("%d\n", Find(str));
	}
	return 0;
}