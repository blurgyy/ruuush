#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>

#define MAXN 400005
#define MAXK 1200
using namespace std;

int n;
stack<int> freeBits;
int root;

int getBit() { 
  if (freeBits.empty())
    puts("NO MORE BITS");
  int res = freeBits.top(); 
  freeBits.pop();
  return res;
}

struct node {
  vector<int> children;
  int time;
  int rank;
  long long spend;
  int depth;
  int bit;
} v[MAXN];

struct BIT {
  long long tree[MAXN];
  vector<int> elems;
  
  long long read(int x) { 
    long long sum = 0;
    for (sum = 0 ; x > 0 ; x -= (x & -x))
      sum += tree[x];
    return sum;
  }

  void add(int k, bool remove = false) {
    long long val = v[k].time;
    if (remove) val = -val;
    else elems.push_back(k);
    int x = v[k].rank;
    for (; x < MAXN; x += (x & -x))
      tree[x] += val;
  }
  
  void clear(int me) {
    for (size_t i = 0; i < elems.size(); i++) 
      add(elems[i], true);
    elems.clear();
    freeBits.push(me);
  }

  int size() {
    return elems.size();
  }
} bits[MAXK];

void merge(int a, int b) { // throw from a to b
  for (size_t i = 0; i < bits[a].elems.size(); i++)
    bits[b].add(bits[a].elems[i]);
}

int findDepth(int k) {
  int maior = 0;
  for (size_t i = 0; i < v[k].children.size(); i++)
    maior = max(maior, findDepth(v[k].children[i])+1);
  return v[k].depth = maior;
}

bool compare(int i, int j) {
  return v[i].depth > v[j].depth;
}

void sortByDepth(int k) {
  sort(v[k].children.begin(), v[k].children.end(), compare);
  for (size_t i = 0; i < v[k].children.size(); i++)
    sortByDepth(v[k].children[i]);
}

void calculate(int k) {
  if (v[k].children.size() > 0) {
    calculate(v[k].children[0]);
    v[k].bit = v[v[k].children[0]].bit;
    for (size_t i = 1; i < v[k].children.size(); i++) {
      calculate(v[k].children[i]);
      int bit2 = v[v[k].children[i]].bit;
      if (bits[v[k].bit].size() < bits[bit2].size()) { // swap
	int tmp = v[k].bit;
	v[k].bit = bit2;
	bit2 = tmp;
      }
      merge(bit2, v[k].bit);
      bits[bit2].clear(bit2);
    }
    bits[v[k].bit].add(k);
    v[k].spend = bits[v[k].bit].read(v[k].rank-1);
  }
  else {
    v[k].bit = getBit();
    v[k].spend = 0;
    bits[v[k].bit].add(k);
  }
}

int main() {
  scanf("%d", &n);
  int parent;
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &parent, &v[i].rank, &v[i].time);
    if (parent != -1)
      v[parent-1].children.push_back(i);
    else 
      root = i;
  }

  for (int i = MAXK-1; i >= 0; i--)
    freeBits.push(i);
  findDepth(root);
  sortByDepth(root);

  calculate(root);

  for (int i = 0; i < n; i++) 
    printf("%lld\n", v[i].spend);

  return 0;
}
