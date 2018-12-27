//Not solved wtf i gotta sleeeep

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

int n, m, t;
int sx, sy;
int p0, p;
char maze[maxn][maxn];
char ans[2][5] = {"NO", "YES"};
bool res;
struct Node
{
	int time;
	int x, y;
	char maze[maxn][maxn];
}node[100010];

bool inline not_outside(int x, int y){
	return (x >= 1 && x <= n && y >= 1 && y <= m);
}

void inline Find(){
	for(int i = 1; i <= n; ++ i)
		for(int j = 1; j <= m; ++ j)
			if(maze[i][j] == 'S'){
				sx = i, sy = j;
				return;
			}
}

void inline copy(Node &a, char ma[][maxn]){
	for(int i = 0; i < maxn; ++ i)
		for(int j = 0; j < maxn; ++ j)
			a.maze[i][j] = ma[i][j];
}

void inline init(){
	p0 = 0;
	p = 1;
	copy(node[0], maze);
	node[0].x = sx;
	node[0].y = sy;
	node[0].time = 0;
	res = false;
}

void inline out(char a[][maxn]){
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= m; ++ j)
			printf("%c", a[i][j]);
		printf("\n");
	}
}

int main(){
	while(~scanf("%d%d%d", &n, &m, &t) && n || m || t){
		for(int i = 1; i <= n; ++ i)
			scanf("%s", maze[i] + 1);
		Find();
		init();
		while(p0 <= p){
			for(int d = 0; d < 4; ++ d){
				int nx = node[p0].x + dx[d];
				int ny = node[p0].y + dy[d];
				if(not_outside(nx, ny) && node[p0].maze[nx][ny] != 'X'){
					if(maze[nx][ny] == 'D' && node[p0].time + 1 == t){
						res = true;
						break;
					}
					copy(node[p], node[p0].maze);
					node[p].maze[node[p0].x][node[p0].y] = 'X';
					node[p].x = nx;
					node[p].y = ny;
					node[p++].time = node[p0].time + 1;
				}
			}
			if(res)break;
			++ p0;
		}
		printf("%s\n", ans[res]);
	}
	return 0;
}

/**

4 4 5
S.X.
..X.
..XD
....
3 4 5
S.X.
..X.
...D

4 4 5
...D
....
....
S...

0 0 0

*/