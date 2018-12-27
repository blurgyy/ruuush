// Problem: Performance Review
// Approach: Segment tree on preorder traversal
// Author: Miguel Oliveira
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX = 1 << 19;

struct Node {
  int key, value, preorder_index, subtree_end;
  vector<int> children;
} tree[MAX];

int preorder[MAX], preorder_index = 1;

void Preorder(int vertex) {
  preorder[preorder_index] = vertex;
  tree[vertex].preorder_index = preorder_index++;
  for (auto w : tree[vertex].children)
    Preorder(w);
  tree[vertex].subtree_end = preorder_index-1;
}

struct SegmentTreeNode {
  vector<pair<int,int>> nodes;
  vector<long long> sums;
  int from, to;
} segtree[MAX*2];

void BuildSegmentTree(int pos, int from, int to) {
  segtree[pos].from = from;
  segtree[pos].to = to;
  if (from > to) 
    return;
  segtree[pos].sums.push_back(0);
  if (from == to) {
    segtree[pos].nodes.push_back({tree[preorder[from]].key, tree[preorder[from]].value});
    segtree[pos].sums.emplace_back(tree[preorder[from]].value);
  } else {
    int mid = (from+to) / 2, left = pos*2, right = 2*pos+1;
    BuildSegmentTree(left, from, mid);
    BuildSegmentTree(right, mid+1, to);
    segtree[pos].nodes.reserve(to-from+1);
    for (const auto& p : segtree[left].nodes)
      segtree[pos].nodes.push_back(p);
    for (const auto& p : segtree[right].nodes)
      segtree[pos].nodes.push_back(p);
    sort(segtree[pos].nodes.begin(), segtree[pos].nodes.end());

    segtree[pos].sums.reserve(segtree[pos].nodes.size()+1);
    long long sum = 0;
    for (const auto& p : segtree[pos].nodes) {
      sum += p.second;
      segtree[pos].sums.push_back(sum);
    }
  }
}

long long Query(int pos, int a, int b, int key) {
  if (a > segtree[pos].to || b < segtree[pos].from)
    return 0;
  if (a <= segtree[pos].from && b >= segtree[pos].to) {
    pair<int,int> pp{key, -1};
    int ind = lower_bound(segtree[pos].nodes.begin(), segtree[pos].nodes.end(), pp) - segtree[pos].nodes.begin();
    return segtree[pos].sums[ind];  // not ind-1 because there's a dummy 0 in the begining of this vector 
  } else {
    return Query(pos*2, a, b, key) + Query(pos*2+1, a, b, key);
  }
}

int main() {
  int N, parent, root = 1;
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d %d %d", &parent, &tree[i].key, &tree[i].value);
    if (parent != -1)
      tree[parent].children.push_back(i);
    else 
      root = i;
  }
  Preorder(root);
  BuildSegmentTree(1, 1, N);
  for (int i = 1; i <= N; ++i) {
    printf("%lld\n", Query(1, tree[i].preorder_index, tree[i].subtree_end, tree[i].key));
  }
  return 0;
}
