#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 500050;

struct Node
{
	int to;
	int ne;
};

Node node[N];
int head[N];
int vis[N];
int st[N];
int n;
int mark;
int top;
int be, en;
int be1, en1;
int be2, en2;
int ans1, ans2;

void Ini()
{
	memset(head, -1, sizeof(head));
	top = 0;
}

void Add_chrome(int from, int to)
{
	node[top].to = to;
	node[top].ne = head[from];
	head[from] = top;
	top ++;
}

int Bfs(int u)
{
	int be;
	queue<int> Q;

	Q.push(u);
	vis[u] = 1;
	while(!Q.empty()){
		int now;

		now = Q.front();
		Q.pop();
		be = now;
		for(int i = head[now]; i != -1; i = node[i].ne){
			int v;

			v = node[i].to;
			if(!vis[v]){
				vis[v] = 1;
				Q.push(v);
			}
		}
	}

	return be;
}

void Dfs(int s, int t, int dep)
{
	if(mark){
		return ;
	}
	st[dep] = s;
	if(s == t){
		mark = dep;

		return ;
	}
	for(int i = head[s]; i != -1; i = node[i].ne){
		int v;

		v = node[i].to;
		if(!vis[v]){
			vis[v] = 1;
			Dfs(v, t, dep + 1);
		}
	}
}

int main(int argc, char const *argv[])
{
	int ncase;

	scanf("%d", &ncase);
	while(ncase --){
		mark = 0;
		Ini();
		scanf("%d", &n);
		for(int i = 1; i < n; i ++){
			int u, v;

			scanf("%d%d", &u, &v);
			Add_chrome(u, v);
			Add_chrome(v, u);
		}
		memset(vis, 0, sizeof(vis));
		be = Bfs(1);
		memset(vis, 0, sizeof(vis));
		en = Bfs(be);
		memset(vis, 0, sizeof(vis));
		// printf("%d %d\n", be, en);
		vis[be] = 1;
		Dfs(be, en, 1);
		// for(int i = 1; i <= mark; i ++){
		// 	// printf("%d ", st[i]);
		// }
		// printf("\n");
		if(mark % 2){
			int a, b;
			int c, d;
			int t;
			int q;

			t = mark;
			q = st[(t + 1) / 2];
			a = st[(t + 1) / 2 - 1];
			b = st[(t + 1) / 2 + 1];
			// printf("a = %d  b = %d\n", a, b);
			memset(vis, 0, sizeof(vis));
			vis[b] = 1;
			be1 = Bfs(q);
			memset(vis, 0, sizeof(vis));
			vis[b] = 1;
			en1 = Bfs(be1);
			memset(vis, 0, sizeof(vis));
			vis[b] = 1;
			mark = 0;
			vis[be1] = 1;
			Dfs(be1, en1, 1);
			c = st[(mark + 1) / 2];
			// printf("mark = %d\n", mark);
			ans1 = mark / 2;
			// printf("1 = %d %d\n", be1, en1);
			memset(vis, 0, sizeof(vis));
			vis[a] = 1;
			be2 = Bfs(q);
			memset(vis, 0, sizeof(vis));
			vis[a] = 1;
			en2 = Bfs(be2);
			memset(vis, 0, sizeof(vis));
			vis[a] = 1;
			mark = 0;
			vis[be2] = 1;
			Dfs(be2, en2, 1);
			d = st[(mark + 1) / 2];
			ans2 = mark / 2;
			if(ans1 < ans2){
				memset(vis, 0, sizeof(vis));
				vis[q] = 1;
				be2 = Bfs(b);
				memset(vis, 0, sizeof(vis));
				vis[q] = 1;
				en2 = Bfs(be2);
				memset(vis, 0, sizeof(vis));
				vis[q] = 1;
				mark = 0;
				vis[be2] = 1;
				Dfs(be2, en2, 1);
				d = st[(mark + 1) / 2];
				// printf("change ans2 = %d\n", ans2);
				ans2 = mark / 2;
			}
			else{
				memset(vis, 0, sizeof(vis));
				vis[q] = 1;
				be1 = Bfs(a);
				memset(vis, 0, sizeof(vis));
				vis[q] = 1;
				en1 = Bfs(be1);
				memset(vis, 0, sizeof(vis));
				vis[q] = 1;
				mark = 0;
				vis[be1] = 1;
				Dfs(be1, en1, 1);
				c = st[(mark + 1) / 2];
				// printf("mark = %d\n", mark);
				ans1 = mark / 2;
				// printf("change ans1 = %d\n", ans1);
				// printf("1 = %d %d\n", be1, en1);
			}
			// printf("2 = %d %d\n", be2, en2);
			// printf("%d %d\n", ans1, ans2);
			printf("%d %d %d\n", max(ans1, ans2), c, d);
		}
		else{
			int a, b;
			int c, d;
			int t;

			t = mark;
			a = st[t / 2];
			b = st[t / 2 + 1];
			// printf("a = %d  b = %d\n", a, b);
			memset(vis, 0, sizeof(vis));
			vis[b] = 1;
			be1 = Bfs(a);
			memset(vis, 0, sizeof(vis));
			vis[b] = 1;
			en1 = Bfs(be1);
			memset(vis, 0, sizeof(vis));
			vis[b] = 1;
			mark = 0;
			vis[be1] = 1;
			Dfs(be1, en1, 1);
			c = st[(mark + 1) / 2];
			// printf("mark = %d\n", mark);
			ans1 = mark / 2;
			// printf("1 = %d %d\n", be1, en1);
			memset(vis, 0, sizeof(vis));
			vis[a] = 1;
			be2 = Bfs(b);
			memset(vis, 0, sizeof(vis));
			vis[a] = 1;
			en2 = Bfs(be2);
			memset(vis, 0, sizeof(vis));
			vis[a] = 1;
			mark = 0;
			vis[be2] = 1;
			Dfs(be2, en2, 1);
			d = st[(mark + 1) / 2];
			ans2 = mark / 2;
			// printf("2 = %d %d\n", be2, en2);
			// printf("%d %d\n", ans1, ans2);
			printf("%d %d %d\n", max(ans1, ans2), c, d);
		}
	}

	return 0;
}
/**
8
1 2
2 3
2 4
4 6
4 7
1 5
5 8
*/