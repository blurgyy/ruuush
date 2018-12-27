#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int FULLBITS = 0x7fffffff;

int n, q, Xor;
int query;
int num[maxn];
map<int ,int> mp;
pair<int, int> ans;
struct segTree
{
	int left, right;
	int And, Or;
}Tree[maxn<<2];

void PushUp(int index){
	Tree[index].And = Tree[index<<1].And & Tree[index<<1|1].And;
	Tree[index].Or = Tree[index<<1].Or | Tree[index<<1|1].Or;
}

void Build(int nowNode, int left, int right){
	Tree[nowNode].left = left;
	Tree[nowNode].right = right;
	if(left == right){
		Tree[nowNode].And = num[right];
		Tree[nowNode].Or = num[right];
		mp[right] = nowNode;
		return;
	}
	int mid = (left + right)>>1;
	Build(nowNode<<1, left, mid);
	Build(nowNode<<1|1, mid+1, right);
	PushUp(nowNode);
}
/*
void Query(){
	int index = mp[query];
	int tmp = index>>1;
	if(index&1){
		Tree[index>>1].And = Tree[index-1].And;
		Tree[index>>1].Or = Tree[index-1].Or;
	}
	else{
		Tree[index>>1].And = Tree[index+1].And;
		Tree[index>>1].Or = Tree[index+1].Or;
	}
	index >>= 1;
	while(index >>= 1)
		PushUp(index);
	ans = make_pair(Tree[1].And, Tree[1].Or);
	PushUp(tmp);
}
*/

void Query(){
	int index = mp[query];
	printf("index = %d\n", index);
	int tmp = index;
	int rec1 = Tree[index].And, rec2 = Tree[index].Or;
	Tree[index].And = FULLBITS;
	Tree[index].Or = 0;
	while(index){
		if(index == 0)break;
		printf("%d\n", index);
		PushUp(index);
		index >>= 1;
	}
	printf("%d %d ", Tree[1].And, Tree[1].Or);
	Tree[tmp].And = rec1;
	Tree[tmp].Or = rec2;
}

int main(){
	while(~scanf("%d%d", &n, &q)){
		mp.clear();
		Xor = 0;
		for(int i = 1; i <= n; ++ i){
			scanf("%d", num + i);
			Xor ^= num[i];
		}
		Build(1, 1, n);
		while(q--){
			scanf("%d", &query);
			Query();
			printf("%d\n", Xor^num[query]);
		}
	}
	return 0;
}

/**

Sample Input:
5 5
684 489465 48 6487 165
1 2 3 4 5

Sample Output:
0 491519 486971
0 7167 7022
0 491519 486567
32 489469 488896
0 491519 486450

*/