///Holy shit
///I almost lost my faith in this...
///Then, I made the variable "Xor" a global one...
///Then I ACed...
///Nope I'll write in Chinese...
/**
	好吧, 一开始我的Xor的计算放在了Query函数中，也就是在Query函数中我写了一个遍历，num的元素全部异或得到变量Xor
	然后在函数Query中输出Xor^num[query]，这样直接TLE...
	然后我把函数Query中的这个循环删除掉，并将Xor改为全局变量，在输入时就直接处理出Xor的值。。。
	噢噢噢噢噢我知道了。。。
	如果我在输入时就处理出Xor的值，那我只需要处理一次
	而如果我在函数中处理Xor的值那将每输入一次Query都会运行一次循环
	显然会T...
	好吧，那么这和全局变量或局部变量没有关系。
	不过我还没找出3.cpp及之前的线段树版本的问题所在。。
*/
///#include <bits/stdc++.h>



#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
const int maxn = 100010;
const int FULLBITS = 0x7fffffff;

int n, p, query;
int Xor;
map<int, int> mp;
int num[maxn];
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
	int mid = (left + right) >> 1;
	Build(nowNode<<1, left, mid);
	Build(nowNode<<1|1, mid+1, right);
	PushUp(nowNode);
}

void Query(int query){
	int index = mp[query];
	int rec1 = Tree[index].And, rec2 = Tree[index].Or;
	Tree[index].And = FULLBITS;
	Tree[index].Or = 0;
	while(index >>= 1)
		PushUp(index);
	printf("%d %d %d\n", Tree[1].And, Tree[1].Or, Xor^num[query]);
	index = mp[query];
	Tree[index].And = rec1;
	Tree[index].Or = rec2;
	while(index >>= 1)
		PushUp(index);
}

int main(){
	while(~scanf("%d%d", &n, &p)){
		Xor = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", num + i);
			Xor ^= num[i];
		}
		mp.clear();
		Build(1, 1, n);
		while(p--){
			scanf("%d", &query);
			Query(query);
		}
	}
	return 0;
}