#include<bits/stdc++.h>
using namespace std;

struct cord
{
	int x, y;
}ans[30];
int p;
int T, Case = 0;
char board[10][10];

bool check(int x, int y){
	board[x][y] = 'x';
	bool ans = true;
	for(int i = 1; i <= 4; ++ i){
		if(board[x][i] != 'x')ans = false;
	}
	if(ans){
		board[x][y] = '.';
		return true;
	}
	ans = true;
	for(int i = 1; i <= 4; ++ i)
		if(board[i][y] != 'x')ans = false;
	if(ans){
		board[x][y] = '.';
		return true;
	}
	ans = true;
	if(x == y){
		for(int i = 1; i <= 4; ++ i)
			if(board[i][i] != 'x')ans = false;
		board[x][y] = '.';
		return ans;
	}
	if(x + y == 5){
		for(int i = 1; i <= 4; ++ i)
			if(board[i][5-i] != 'x')ans = false;
		board[x][y] = '.';
		return ans;
	}
	board[x][y] = '.';
	return false;
}

bool operator< (cord a, cord b){
	if(a.x < b.x)return true;
	if(a.x > b.x)return false;
	return a.y < b.y;
}

int main(){
	string str;

	cin >> str;

	//cout << str  << endl;
	T = 0;
	int pos = 0;
	for(int i = 0; i < str.size(); i ++){
		if(str[i] < '0' || str[i] > '9'){
			pos = i + 1;
		}
	}
	for(int i = pos; i < str.size(); ++ i){
		T *= 10;
		T += str[i] - '0';
		//printf("T = %d\n", T);
	}
	//cout << T << endl;
	while(T--){
		if(Case)printf("\n");
		memset(ans, 0, sizeof(ans));
		p = 0;
		//cout << T << endl;
		for(int i = 1; i <= 4; ++ i){
			scanf("%s", board[i] + 1);
			/*for(int j = 1; j <= 4; ++ j){
				scanf("%c", board[i] + j);
				getchar();
			}*/
		}
		//cout << 666 << endl;
		for(int i = 1; i <= 4; ++ i){
			for(int j = 1; j <= 4; ++ j){
				if(board[i][j] == '.'){
					if(check(i, j)){
						ans[p].x = i;
						ans[p++].y = j;
					}
				}
			}
		}
		printf("Case #%d:\n", ++ Case);
		if(p == 0){
			printf("#####\n");
			continue;
		}
		sort(ans, ans + p);
		for(int i = 0; i < p; ++ i)
			printf("(%d, %d)\n", ans[i].x - 1, ans[i].y - 1);
	}
	return 0;
}

/**

2
xxx.
xxx.
.ooo
ooo.

....
.xo.
.ox.
....

2
xxx.
xxx.
.ooo
ooo.

....
.xo.
.ox.
....

*/