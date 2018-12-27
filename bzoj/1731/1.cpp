#include <bits/stdc++.h>
using namespace std;
const int maxn = 40010;
const int inf = 0x3f3f3f3f;

int n, ml, md;
struct Node{
	int to, w, ne;
}node[maxn];
int head[maxn];
int top;
int dis[maxn];

void add(int from, int to, int w){
	node[top].to = to;
	node[top].w = w;
	node[top].ne = head[from];
	head[from] = top;
	top ++;
}

bool spfa(int from){
	queue<int> que;
	bool inq[maxn];
	int cnt[maxn];

	memset(dis, 0x3f, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	memset(inq, 0, sizeof(inq));
	dis[from] = 0;
	cnt[from] ++;
	inq[from] = 1;
	que.push(from);
	while(!que.empty()){
		int now;
		now = que.front();
		inq[now] = 0;
		que.pop();
		for(int i = head[now]; i != -1; i = node[i].ne){
			int nxt = node[i].to;
			if(dis[nxt] > dis[now] + node[i].w){
				dis[nxt] = dis[now] + node[i].w;
				if(!inq[nxt]){
					inq[nxt] = 1;
					que.push(nxt);
					cnt[nxt] ++;
					if(cnt[nxt] > n + 1){
						return false;
					}
				}
			}
		}
	}
	return true;
}

void ini(){
	top = 0;
	memset(head, -1, sizeof(head));
}

int main(){
	while(~scanf("%d%d%d", &n, &ml, &md)){
		ini();
		for(int i = 1; i < n; ++ i){
			add(i+1, i, 0);
		}
		while(ml --){
			int i, j, L;
			scanf("%d%d%d", &i, &j, &L);
			add(i, j, L);
		}
		while(md --){
			int i, j, D;
			scanf("%d%d%d", &i, &j, &D);
			add(j, i, -D);
		}
		bool x = spfa(1);
		if(x){
			if(dis[n] == inf){
				printf("-2\n");
			}
			else {
				printf("%d\n", dis[n]);
			}
		}
		else {
			printf("-1\n");
		}
	}
	return 0;
}