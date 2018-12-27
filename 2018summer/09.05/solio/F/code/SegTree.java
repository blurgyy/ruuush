// SWERC 2016 - Performance Review
// Approach: Segment tree on preorder traversal
// Author: Miguel Oliveira
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class SegTree {
  private static final int MAX = 1 << 17;
  
  static class Pair {
    int key;
    int value;
    public Pair(int k, int v) {
      key = k;
      value = v;
    }
  }

  static int[] preorder = new int[MAX];
  static int gpreorderIndex = 1;

  static class TreeNode {
    int key;
    int value;
    int preorderIndex;
    int subtreeEnd;
    int index;
    ArrayList<TreeNode> children = new ArrayList<TreeNode>();
  
    TreeNode(int i) {
      index = i;
    }
    void preorder() {
      preorder[gpreorderIndex] = this.index;
      this.preorderIndex = gpreorderIndex;
      gpreorderIndex++;
      for (TreeNode w : this.children)
        w.preorder();
      this.subtreeEnd = gpreorderIndex-1;
    }
  }

  static ArrayList<TreeNode> tree = new ArrayList<TreeNode>();

  static class SegmentTreeNode {
    int[] keys;
    int[] values;
    long[] sums;
    int from, to;
  }
  static ArrayList<SegmentTreeNode> segtree;

  static void merge(SegmentTreeNode a, SegmentTreeNode b, SegmentTreeNode res) {
    int na = a.keys.length, nb = b.keys.length, k = 0;
    res.keys = new int[na+nb];
    res.values = new int[na+nb];
    for (int i = 0, j = 0; i < na || j < nb; k++ ) {
      if (i == na || (j < nb && b.keys[j] <= a.keys[i])) {
        res.keys[k] = b.keys[j];
        res.values[k] = b.values[j];
        j++;
      } else {
        res.keys[k] = a.keys[i];
        res.values[k] = a.values[i];
        i++;
      }
    }
  }

  static void buildSegmentTree(int pos, int from, int to) {
    SegmentTreeNode cur = segtree.get(pos);
    cur.from = from;
    cur.to = to;
    if (from > to) 
      return;
    if (from == to) {
      TreeNode f = tree.get(preorder[from]);
      cur.keys = new int[]{f.key};
      cur.values = new int[]{f.value};
      cur.sums = new long[]{0, (long)f.value};
    } else {
      int mid = (from+to) / 2, left = pos*2, right = 2*pos+1;
      buildSegmentTree(left, from, mid);
      buildSegmentTree(right, mid+1, to);
      merge(segtree.get(left), segtree.get(right), cur);
      cur.sums = new long[cur.keys.length+1];
      long sum = 0;
      int i = 1;
      for (int v : cur.values) {
        sum += v;
        cur.sums[i] = sum;
        i++;
      }
    }
  }
  
  static int lowerBound(int[] cur, int key) {
    int left = 0, right = cur.length-1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (cur[mid] < key) 
        left = mid+1;
      else
        right = mid-1;
    }
    return left;
  }
  static long query(int pos, int a, int b, int key) {
    SegmentTreeNode cur = segtree.get(pos);
    if (a > cur.to || b < cur.from)
      return 0;
    if (a <= cur.from && b >= cur.to) {
      int ind = lowerBound(cur.keys, key);
      return cur.sums[ind];  // not ind-1 because there's a dummy 0 in the begining of this vector 
    } else {
      return query(pos*2, a, b, key) + query(pos*2+1, a, b, key);
    }
  }

  public static void main(String[] args) throws IOException {
    BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
    int N = Integer.parseInt(input.readLine());
    int root = -1;
    for (int i = 0; i <= N; i++)
      tree.add(new TreeNode(i));

    for (int i = 1; i <= N; i++) {
      String[] tokens = input.readLine().split(" ");
      int parent = Integer.parseInt(tokens[0]);
      tree.get(i).key = Integer.parseInt(tokens[1]);
      tree.get(i).value = Integer.parseInt(tokens[2]);
      if (parent == -1)
        root = i;
      else
        tree.get(parent).children.add(tree.get(i));
    }
    tree.get(root).preorder();
    segtree = new ArrayList<SegmentTreeNode>(3*N);
    for (int i = 0; i < 3*N; i++)
      segtree.add(new SegmentTreeNode());
    buildSegmentTree(1, 1, N);
    PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    for (int i = 1; i <= N; ++i) {
      out.println(query(1, tree.get(i).preorderIndex, tree.get(i).subtreeEnd, tree.get(i).key));
    }
    out.flush();
  }
}
