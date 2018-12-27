#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#define bug(a) printf("(%d)\n", (a));
using namespace std;
const int maxn = 100010;
const int FULL_BITS = 0x7fffffff;

int n, q, query;
map<int, int> func;
pair<int, int> ans;
int Xor;
int num[maxn];
struct segTree
{
	int left, right;
	int And, Or;
}Tree[maxn<<2];

void PushUp(int index){
	Tree[index].And = Tree[index<<1].And & Tree[index<<1|1].And;
	Tree[index].Or = Tree[index<<1].Or | Tree[index<<1|1].Or;
	printf("tree[%d]: %d, %d\n", index, Tree[index].And, Tree[index].Or);
}

void out(){
	for(auto i = func.begin(); i != func.end(); ++ i)
		printf("Tree[%d]: and = %d, or = %d\n", (*i).second, Tree[(*i).second].And, Tree[(*i).second].Or);
}

void Build(int left, int right, int nowNode = 1){
	Tree[nowNode].left = left;
	Tree[nowNode].right = right;
	if(left == right){
		Tree[nowNode].And = num[right];
		Tree[nowNode].Or = num[right];
		func[right] = nowNode;
		return;
	}
	int mid = (left + right)>>1;
	Build(left, mid, nowNode<<1);
	Build(mid+1, right, nowNode<<1|1);
	PushUp(nowNode);
}

pair<int, int> Query(){
	int index = func[query];
	int rec_and = Tree[index].And;
	int rec_or = Tree[index].Or;
	Tree[index].And = FULL_BITS;
	Tree[index].Or = 0;
	out();
	int i = index;
	while(index >>= 1)
		PushUp(index);
	pair<int, int> ret = make_pair(Tree[1].And, Tree[1].Or);
	Tree[i].And = rec_and;
	Tree[i].Or = rec_or;
	return ret;
}

int main(){
	while(~scanf("%d%d", &n, &q)){
		func.clear();
		Xor = 0;
		for(int i = 1; i <= n; ++ i)
			scanf("%d", num + i);
		for(int i = 1; i <= n; ++ i)
			Xor ^= num[i];
		Build(1, n);
		out();
		while(q--){
			scanf("%d", &query);
			ans = Query();
			printf("%d %d %d\n", ans.first, ans.second, Xor^num[query]);
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