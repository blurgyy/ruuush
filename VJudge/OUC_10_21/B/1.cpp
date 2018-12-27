#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, m;
char mp[maxn][maxn];
int p;
pair<int, int> rec[5];

bool check_mp(/**/){
	for(int i = 1; i <= n; ++ i)
		for(int j = 1; j <= m; ++ j)
			if(mp[i][j] == '*')return false;
	return true;
}

bool check(pair<int, int> a, pair<int, int> b){
	int x1 = a.first, y1 = a.second;
	int x2 = b.first, y2 = b.second;
	int recx[maxn<<1], recy[maxn<<1];
	int px = 0, py = 0;
	for(int i = 1; i <= n; ++ i){
		if(mp[i][y1] == '*'){
			mp[i][y1] = '.';
			recx[px++] = i;
		}
	}
	for(int j = 1; j <= m; ++ j){
		if(mp[x2][j] == '*'){
			mp[x2][j] = '.';
			recy[py++] = j;
		}
	}
	if(check_mp())return true;
	for(int i = 0; i < px; ++ i)
		mp[recx[i]][y1] = '*';
	for(int j = 0; j < py; ++ j)
		mp[x2][recy[j]] = '*';
	return false;
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		p = 0;
		memset(rec, 0, sizeof(rec));
		for(int i = 1; i <= n; ++ i)
			scanf("%s", mp[i] + 1);
		if(check_mp()){
			printf("YES\n1 1\n");
			continue;
		}
		for(int i = 1; i <= n; ++ i){
			for(int j = 1; j <= m; ++ j)
				if(mp[i][j] == '*'){
					if(p > 0 && i == rec[p-1].first || j == rec[p-1].second)continue;
					rec[p++] = make_pair(i, j);
					break;
				}
			if(p > 1)break;
		}
		if(p <= 1){
			printf("YES\n%d %d\n", rec[0].first, rec[0].second);
			continue;
		}
		if(check(rec[0], rec[1])){
			printf("YES\n%d %d\n", rec[1].first, rec[0].second);
		}
		else if(check(rec[1], rec[0])){
			printf("YES\n%d %d\n", rec[0].first, rec[1].second);
		}
		else printf("NO\n");
	}
	return 0;
}

/**

6 5
..*.*
..*..
*****
..*..
..*..
..*..

*/