#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>

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
  unordered_map<int, long long> tree;
  vector<int> elems;
  
  long long read(int x) { 
    long long sum = 0;
    for (sum = 0 ; x > 0 ; x -= (x & -x)) {
      auto it = tree.find(x);
      sum += it != tree.end() ? it->second : 0;
    }
    return sum;
  }

  void add(int k) {
    long long val = v[k].time;
    elems.push_back(k);
    int x = v[k].rank;
    for (; x < MAXN; x += (x & -x)) {
      if (tree.find(x) != tree.end())
	tree[x] += val;
      else 
	tree[x] = val;
    }
  }
  
  void clear(int me) {
    tree.clear();
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

stack<int> s;
void findDepth() {
  s.push(root);
  while (!s.empty()) {
    int k = s.top();
    if (v[k].depth == 0) { //push children
      for (size_t i = 0; i < v[k].children.size(); i++)
	s.push(v[k].children[i]);
      v[k].depth = -1;
    } 
    else if (v[k].depth == -1) { // you can update k
      int maior = 0;
      for (size_t i = 0; i < v[k].children.size(); i++)
	maior = max(maior, v[v[k].children[i]].depth+1);
      v[k].depth = maior;
      s.pop();
    }
  }
}

bool compare(int i, int j) {
  return v[i].depth > v[j].depth;
}

void sortByDepth() {
  s.push(root);
  while (!s.empty()) {
    int k = s.top(); s.pop();
    sort(v[k].children.begin(), v[k].children.end(), compare);
    for (size_t i = 0; i < v[k].children.size(); i++)
      s.push(v[k].children[i]);
  }   
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
  findDepth();
  sortByDepth();

  calculate(root);

  for (int i = 0; i < n; i++) 
    printf("%lld\n", v[i].spend);

  return 0;
}
