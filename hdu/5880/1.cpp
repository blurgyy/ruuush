//很奇怪，有字典树的代码一用g++编译就会MLE
//C++又不能用bits头文件...
//AC自动机...水题吧
//不算g++的MLE和C++的bits编译错误的话，可以说是1A了
//...
//HDU 5880

//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<queue>
using namespace std;
const int maxn = 1000010;

struct Trie
{
	Trie *nxt[26], *fail;
	//bool finish;
	int len;
	void init(){
		for(int i = 0; i < 26; ++ i)
			nxt[i] = NULL;
		fail = NULL;
		//finish = false;
		len = 0;
	}
}root;
int T, n;
char word[maxn], text[maxn];
vector<int> recover;

void Insert(char *s){
	Trie *now = &root, *tmp;
	int index, len = strlen(s);
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
	//now->finish = true;
	now->len = len;
}

void Get_fail(){
	queue<Trie*> Q;
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

void AC_Automation(char *s){
	Get_fail();
	Trie *now = &root, *match;
	int index;
	while(*s){
		if(*s < 'a' || *s > 'z'){
			now = &root;
			++ s;
			continue;
		}
		index = *s - 'a';
		while(!now->nxt[index] && now != &root)
			now = now->fail;
		now = now->nxt[index];
		if(!now)now = &root;
		match = now;
		while(match){
			if(match->len){
				for(char *i = s - match->len + 1; i <= s; ++ i)
					*i = '*';
			}
			match = match->fail;
		}
		++ s;
	}
}

void Del(Trie *now = &root){
	for(int i = 0; i < 26; ++ i)
		if(now->nxt[i]){
			Del(now->nxt[i]);
			free(now->nxt[i]);
		}
}

int main(){
	scanf("%d", &T);
	while(T--){
		root.init();
		recover.clear();
		scanf("%d", &n);
		while(n--){
			scanf("%s", word);
			Insert(word);
		}
		getchar();
		gets(text);
		char *p = text;
		int pos = 0;
		while(*p){
			if(*p >= 'A' && *p <= 'Z'){
				*p += 32;
				recover.push_back(pos);
			}
			++ p;
			++ pos;
		}
		AC_Automation(text);
		int len = recover.size();
		for(int i = 0; i < len; ++ i)
			if(text[recover[i]] != '*')
				text[recover[i]] -= 32;
		printf("%s\n", text);
		Del();
	}
	return 0;
}