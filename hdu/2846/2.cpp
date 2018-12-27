#include<cstdio>
#include<cstring>
#include<malloc.h>

struct Trie
{
	Trie* nxt[26];
	int last_word;
	int cnt;
	void init(){
		for(int i = 0; i < 26; ++ i)
			nxt[i] = NULL;
		cnt = 0;
		last_word = -1;
	}
}root;
int P, Q;
char name[25];

void Insert(char* s, int hash){
	Trie* p = &root;
	while(*s != 0){
		int index = *s - 'a';
		if(p->nxt[index] == NULL){
			Trie* tmp = (Trie*)malloc(sizeof(Trie));
			tmp->init();
			p->nxt[index] = tmp;
		}
		p = p->nxt[index];
		if(p->last_word != hash){
			p->cnt++;
			p->last_word = hash;
		}
		++ s;
	}
}

int Find(char* s){
	Trie* p = &root;
	while(*s != 0){
		int index = *s - 'a';
		if(p->nxt[index] == NULL)return 0;
		p = p->nxt[index];
		++ s;
	}
	return p->cnt;
}

int main(){
	root.init();
	scanf("%d", &P);
	while(P--){
		scanf("%s", name);
		int len = strlen(name);
		for(int i = 0; i < len; ++ i)
			Insert(name + i, P);
	}
	scanf("%d", &Q);
	while(Q--){
		scanf("%s", name);
		printf("%d\n", Find(name));
	}
	return 0;
}

/*

20
ad
ae
af
ag
ah
ai
aj
ak
al
ads
add
ade
adf
adg
adh
adi
adj
adk
adl
aes
5
b
a
d
ad
s


*/