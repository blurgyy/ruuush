#include <bits/stdc++.h>
#define mp make_pair
using namespace std;

const int N = 22;
const int M = 200020;

struct Node
{
  int to;
  int w;
  int ne;
};

// 0 1 2 3
// U R D L
char ma[N][N];
//           U   R  D  L
int dx[6] = {-1, 0, 1, 0};
int dy[6] = {0,  1, 0, -1};
int dis[M];
int n;
int m;
int bx;
int by;
int ex;
int ey;
Node node[M];
int head[M];
int top;

void AddEdge(int from, int to, int w)
{
    node[top].to = to;
    node[top].w = w;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

void Ini()
{
   top = 0;
   memset(head, -1, sizeof(head));
}

int Get(int x, int y, int dir)
{
    return dir * n * m + x * m + y + 1;
}

bool Biild(int x, int y, int nx, int ny, int dir, int preDir, int w)
{
    int u;
    int v;

 if(nx < 0 || nx >= n) {
  return false;
 } else if(ny < 0 || ny >= m) {
  return false;
 } else if(ma[nx][ny] == '#') {
  return false;
 }
    u = Get(x, y, preDir);
    v = Get(nx, ny, dir);
    // printf("add edge[%d %d %d] = %d\n", x, y, preDir, u);
    // printf("add edge[%d %d %d] = %d\n", nx, ny, dir, v);
 AddEdge(u, v, w);
    // printf("add edge[%d %d %d]\n", u, v, w);
    // AddEdge(v, u, w);

    return true;
}

void Join(int x, int y, int dir)
{
    int nx;
    int ny;

 if(ma[x][y] == '#') {
  return  ;
 } else if(ma[x][y] == '.' || ma[x][y] == 'D' || ma[x][y] == 'S') {
        nx = x + dx[dir];
        ny = y + dy[dir];
        if(Biild(x, y, nx, ny, dir, dir, 1)) {
            int l;
   int r;
            int lx;
            int ly;
            int rx;
            int ry;

            // printf("qwe[%d %d %d]", x, y, dir);
            l = (dir - 1 + 4) % 4;
            r = (dir + 1) % 4;
            Biild(x, y, nx, ny, l, dir, 0);
            Biild(x, y, nx, ny, r, dir, 0);
            // lx = nx + dx[l];
            // ly = ny + dy[l];
            // rx = nx + dx[r];
            // ry = ny + dy[r];
            // Biild(nx, ny, lx, ly, l, dir, 0);
            // Biild(nx, ny, rx, ry, r, dir, 0);
        }
 } 
}


void Dij(int dir)
{
    int beg;

    beg = Get(bx, by, dir);
    // printf("beg = %d\n", beg);
   priority_queue< pair<int, int> > Q;
 memset(dis, 0x3f3f3f3f, sizeof(dis));
   dis[beg] = 0;
    Q.push(mp(0, beg));
    while(!Q.empty()){
        int w;
        int u;

        u = Q.top().second;
        Q.pop();
        for(int i = head[u]; i != -1; i = node[i].ne){
            int v;
            
            v = node[i].to;
            // printf("%d -> %d\n", u, v);
            if(dis[v] > dis[u] + node[i].w){
                dis[v] = dis[u] + node[i].w;
                // printf("in %d -> %d\n", u, v);
                Q.push(mp(-dis[v], v));
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int ans;

 while(scanf("%d%d", &n, &m) == 2) {
        ans = 0x3f3f3f3f;
     Ini();
  for(int i = 0; i < n; i ++) {
   scanf("%s", ma[i]);
  }
  for(int i = 0; i < n; i ++) {
   for(int j = 0; j < m; j ++) {
    if(ma[i][j] == 'S') {
     bx = i;
     by = j;
    } else if(ma[i][j] == 'D') {
     ex = i;
     ey = j;
    }
    for(int k = 0; k < 4; k ++) {
     Join(i, j, k);
    }
   }
  }
        for(int i = 0; i < 4; i ++) {
            Dij(i);
            for(int j = 0; j < 4; j ++) {
                int v;

                v = Get(ex, ey, j);
                // printf("v = %d\n", v);
                ans = min(ans, dis[v]);
            }
        }
        printf("%d\n", ans);
 }


 return 0;
}
