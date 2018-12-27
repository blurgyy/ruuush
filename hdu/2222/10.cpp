#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<algorithm>
#include<queue>
const int maxn = 1000010;

struct Trie
{
	int finish;
	Trie *nxt[26], *fail;
	void init(){
		for(int i = 0; i < 26; ++ i)
			nxt[i] = NULL;
		fail = NULL;
		finish = 0;
	}
}root;
int T, N;
char word[55], text[maxn];

void Insert(char *s){
	Trie *now = &root, *tmp;
	int index;
	while(*s){
		index = *s - 'a';
		if(!now->nxt[index]){
			tmp = (Trie*) malloc(sizeof(Trie));
			tmp->init();
			now->nxt[index] = tmp;
		}
		now = now->nxt[index];
		++ s;
	}
	now->finish ++;
}

void Get_fail(){
	std::queue<Trie*> Q;
	Q.push(&root);
	Trie *now, *ancestor;
	while(!Q.empty()){
		now = Q.front();
		Q.pop();
		for(int i = 0; i < 26; ++ i){
			if(now->nxt[i]){
				Q.push(now->nxt[i]);
				if(now == &root){
					now->nxt[i]->fail = now;
					continue;
				}
				ancestor = now->fail;
				while(ancestor){
					if(ancestor->nxt[i]){
						now->nxt[i]->fail = ancestor->nxt[i];
						break;
					}
					ancestor = ancestor->fail;
				}
				if(!ancestor)
					now->nxt[i]->fail = &root;
			}
		}
	}
}

int AC_Automation(char *s){
	Get_fail();
	Trie *now = &root, *match;
	int index, ans = 0;
	while(*s){
		index = *s - 'a';
		while(!now->nxt[index] && now != &root)
			now = now->fail;
		now = now->nxt[index];
		if(!now)now = &root;
		match = now;
		while(match && match->finish >= 0){
			ans += match->finish;
			match->finish = -1;
			match = match->fail;
		}
		++ s;
	}
	return ans;
}

void Del(Trie *now = &root){
	for(int i = 0; i < 26; ++ i)
		if(now->nxt[i]){
			Del(now->nxt[i]);
			free(now->nxt[i]);
		}
	now->fail = NULL;
}

int main(){
	scanf("%d", &T);
	while(T--){
		root.init();
		scanf("%d", &N);
		while(N--){
			scanf("%s", word);
			Insert(word);
		}
		scanf("%s", text);
		printf("%d\n", AC_Automation(text));
		Del();
	}
	return 0;
}