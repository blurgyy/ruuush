#include<cstdio>
#include<cstring>
#include<queue>
typedef unsigned long long ull;

int N, L;
char in[10];
struct Trie
{
	int nxt[maxn][26],
		fail[maxn],
		cnt[maxn];
		size, root;
	bool finish[maxn];

	void idx(char ch){
		if(ch == 'A')return 0;
		if(ch == 'G')return 1;
		if(ch == 'C')return 2;
		return 3;
	}
	int newNode(){
		for(int i = 0; i < 26; ++ i)
			nxt[size][i] = 0;
		fail[size] = 0;
		cnt[size] = 0;
		finish[size] = false;
		return size ++;
	}
	void init(){
		size = 1;
		root - newNode();
	}
	void insert(char *s){
		int now = root;
		while(*s){
			int index = idx(*s);
			if(!nxt[now][index])
				nxt[now][index] = newNode();
			now = nxt[now][index];
			++ s;
		}
		++ cnt[now];
		finish[now] = true;
	}
	void build(){
		queue<int> que;
		fail[root] = root;
		for(int i = 0; i < 26; ++ i){
			if(nxt[root][i]){
				que.push(nxt[root][i]);
				fail[nxt[now][i]] = root;
			}
			else nxt[now][i] = root;
		}
		while(que.size()){
			int now = que.front();
			que.pop();
			finish[now] = finish[now] || finish[fail[now]];
			for(int i = 0; i < 26; ++ i){
				if(nxt[now][i]){
					que.push(nxt[now][i]);
					fail[nxt[now][i]] = nxt[fail[now]][i];
				}
				else nxt[now][i] = nxt[fail][now][i];
			}
		}
	}
	ull cnt_forbidden(int len){
		ull ans = 0;
		for(int i = 0; i < len; ++ i){
			
		}
	}
}ac;

int main(){
	while(~scanf("%d%d", &N, &L)){
		as.init();
		while(N--){
			scanf("%s", in);
			ac.insert(in);
		}
		ac.build();
		printf("%llu\n", ac.cnt_forbidden(L));
	}
	return 0;
}