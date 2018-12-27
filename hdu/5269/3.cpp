#include<bits/stdc++.h>
using namespace std;
const int manx = 50010;

struct Trie
{
	int cnt;
	Trie* nxt[2];
	void init(){
		cnt = 0;
		nxt[0] = nxt[1] = NULL;
	}
}root;

int T, n;
int num, ans;

int two(int k){
	int ans = 1;
	while(k--)
		ans *= 2;
	return ans;
}

void Insert(int num, int notFirst){
	Trie* p = &root;
	int len = 30;
	while(len--){
		int index = num&1;
		if(p->nxt[index] == NULL){
			Trie* tmp = (Trie*)malloc(sizeof(Trie));
			tmp->init();
			p->nxt[index] = tmp;
		}
		p = p->nxt[index];
		p->cnt ++;
		num >>= 1;
		if(notFirst)ans += p->cnt * two(30-len);
	}
}

void init(){
	root.init();
	ans = 0;
}

int main(){
	scanf("%d", &T);
	while(T--){
		init();
		scanf("%d", &n);
		for(int i = 0; i < n; ++ i){
			scanf("%d", &num);
			Insert(num, i);
		}
		printf("%d\n", ans);
	}
	return 0;
}