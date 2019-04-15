#include <bits/stdc++.h>
using namespace std;

const int N = 410;

struct Node
{
	int x;
	int y;
};

Node node[N];

int main(int argc, char const *argv[])
{
	int cnt;

	cnt = 0;
	printf("400\n");
	for(int i = 1; i <= 20; i ++){
		for(int j = 1; j <= 20; j ++){
			node[cnt].x = i;
			node[cnt].y = j;
			cnt ++;
		}
	}
	random_shuffle(node, node + 400);
	for(int i = 0; i < 400; i ++){
        printf("%d %d\n", node[i].x, node[i].y);
	}


	return 0;
}
