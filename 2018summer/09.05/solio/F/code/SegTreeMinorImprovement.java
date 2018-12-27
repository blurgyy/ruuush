// SWERC 2016 - Performance Review
// Approach: Segment tree on preorder traversal
// Author: Miguel Oliveira
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class SegTreeMinorImprovement {
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
    ArrayList<Pair> nodes = new ArrayList<Pair>();
    long[] sums;
    int from, to;
  }
  static ArrayList<SegmentTreeNode> segtree;

  static void merge(ArrayList<Pair> a, ArrayList<Pair> b, ArrayList<Pair> res) {
    int na = a.size(), nb = b.size();
    for (int i = 0, j = 0; i < na || j < nb; ) {
      if (i == na || (j < nb && b.get(j).key <= a.get(i).key)) {
        res.add(b.get(j));
        j++;
      } else {
        res.add(a.get(i));
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
      cur.nodes.add(new Pair(f.key, f.value));
      cur.sums = new long[]{0, (long)f.value};
    } else {
      int mid = (from+to) / 2, left = pos*2, right = 2*pos+1;
      buildSegmentTree(left, from, mid);
      buildSegmentTree(right, mid+1, to);
      merge(segtree.get(left).nodes, segtree.get(right).nodes, cur.nodes);
      /*
      System.out.printf("node at %d [%2d, %2d] :  left : ", pos, from, to);
      for (Pair p : segtree.get(left).nodes)
        System.out.printf("(%d, %d) ", p.key, p.value);
      System.out.printf("  right : ");
      for (Pair p : segtree.get(right).nodes)
        System.out.printf("(%d, %d) ", p.key, p.value);
      System.out.printf("  got : ");
      for (Pair p : cur.nodes)
        System.out.printf("(%d, %d) ", p.key, p.value);
      System.out.printf("\n");
      */
      cur.sums = new long[cur.nodes.size()+1];
      long sum = 0;
      int i = 1;
      for (Pair p : cur.nodes) {
        sum += p.value;
        cur.sums[i] = sum;
        i++;
      }
    }
  }
  
  static int lowerBound(ArrayList<Pair> nodes, int key) {
    int left = 0, right = nodes.size()-1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (nodes.get(mid).key < key) 
        left = mid+1;
      else
        right = mid-1;
    }
    /*
    for (left = 0; left < nodes.size(); left++)
      if (nodes.get(left).key >= key)
        return left; 
        */
    return left;
  }
  static long query(int pos, int a, int b, int key) {
    SegmentTreeNode cur = segtree.get(pos);
    //System.out.printf("pos %d   %d %d %d  cur %d, %d\n", pos, a, b, key, cur.from, cur.to);
    if (a > cur.to || b < cur.from)
      return 0;
    if (a <= cur.from && b >= cur.to) {
      int ind = lowerBound(cur.nodes, key);
     /*
      System.out.printf("node at %d :  ", pos);
      for (Pair p : cur.nodes)
        System.out.printf("(%d, %d) ", p.key, p.value);
      System.out.printf(" key was %d  got ind %d\n", key, ind);
      */
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
    /*
    System.out.println("preorder ");
    for (int i = 0; i < N; i++)
      System.out.println(preorder[i]);
    System.out.println();
*/
    segtree = new ArrayList<SegmentTreeNode>(3*N);
    for (int i = 0; i < 3*N; i++)
      segtree.add(new SegmentTreeNode());
    buildSegmentTree(1, 1, N);
 /*
    for (int i = 1; i <= N; ++i) {
      System.out.printf("node %2d  preorder index %d  subtree_end %d  key %d\n", i, tree.get(i).preorderIndex, tree.get(i).subtreeEnd, tree.get(i).key);
    }
    */
    PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    for (int i = 1; i <= N; ++i) {
      out.println(query(1, tree.get(i).preorderIndex, tree.get(i).subtreeEnd, tree.get(i).key));
    }
    out.flush();
  }
}
