#include <bits/stdc++.h>
using namespace std;

const int N = 210;

struct Node
{
	int x;
	int y;
	int world;
};


int yy[5] = {-1, 1};
int ma[N][N];
int vis[N][N];
int n;
int m;
int w;
int ti;

bool Chekc(int x, int y, int ti)
{
	if(x < 1 || x > n + w){
		return false;
	}
	if(y < 1 || y > m){
		return false;
	}
	if(ma[x][y]){
		return false;
	}
	if(vis[x][y] >= ti){
        return false;
	}

	return true;
}

bool Bfs()
{
	Node node;
	queue<Node> Q;

	node.x = w + n;
	node.y = 1;
    node.world = ti;
	vis[node.x][node.y] = node.world;
	Q.push(node);
	while(!Q.empty()){
		Node ne;

		node = Q.front();
        Q.pop();
		if(node.x == 1){
			return true;
		}
		for(int i = 0; i < 2; i ++){
			ne.x = node.x;
			ne.y = node.y + yy[i];
			ne.world = node.world;
			if(Chekc(ne.x, ne.y, ne.world)){
				if(ne.world){
					ne.world --;
					vis[ne.x][ne.y] = ne.world;
					Q.push(ne);
					ne.world ++;
				}
                if(Chekc(ne.x - 1, ne.y, ne.world)){
                    ne.x --;
                    vis[ne.x][ne.y] = ne.world;
                    Q.push(ne);
                }
			}
		}
		ne.x = node.x - 1;
		ne.y = node.y;
		ne.world = node.world;
		if(Chekc(ne.x, ne.y, ne.world)){
            vis[ne.x][ne.y] = ne.world;
            Q.push(ne);
        }
	}

	return false;
}

int main(int argc, char const *argv[])
{
	int ncase;

	scanf("%d", &ncase);
	while(ncase --){
        memset(ma, 0, sizeof(ma));
        memset(vis, -1, sizeof(vis));
		scanf("%d%d%d%d", &m, &n, &w, &ti);
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= m; j ++){
				scanf("%d", &ma[i][j]);
			}
		}
		if(Bfs()){
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}
	}


	return 0;
}
/**
3
3 2 1 0
1 1 1
0 0 0

3 2 1 0
0 0 0
1 1 1

3 2 1 0
1 0 0
0 0 0

*/

