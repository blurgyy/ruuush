// Problem: Performance Review
// Approach: Use a post-order traversal of the tree and keep a Binary Indexed Tree
//           with the accumulated sums up to a value. O(N log N)
// Author: Miguel Oliveira
#include <cstdio>
#include <vector>
using namespace std;
const int MAX = 1 << 19;

struct BITree {
  vector<long long> tree;
  BITree(int n = MAX) {
    tree.assign(n, 0);
  }
  void Update(int x, long long value) {
    for (; x < (int)tree.size(); x += x & -x)
      tree[x] += value;
  }
  long long Read(int x) {
    long long sum = 0;
    for (; x > 0; x -= x & -x) 
      sum += tree[x];
    return sum;
  }
} bit;

struct Node {
  long long key, value;
  vector<int> children;
} tree[MAX+1];

void TreeUpdate(int curv) {
  long long sum_before = bit.Read(tree[curv].key - 1);
  for (auto w : tree[curv].children) 
    TreeUpdate(w);
  bit.Update(tree[curv].key, tree[curv].value);
  tree[curv].value = bit.Read(tree[curv].key - 1) - sum_before;
}

int main() {
  int N, parent, root = 1;
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d %lld %lld", &parent, &tree[i].key, &tree[i].value);
    if (parent != -1)
      tree[parent].children.push_back(i);
    else 
      root = i;
  }
  TreeUpdate(root);
  for (int i = 1; i <= N; ++i) {
    printf("%lld\n", tree[i].value);
  }
  return 0;
}
