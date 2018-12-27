// SWERC 2016 - Performance Review
// Author: Miguel Oliveira
import java.io.*;
import java.util.ArrayList;

public class PerformanceReview {
  private static final int MAX = 1 << 17;
    
  static long[] tree = new long[MAX];

  static void BITUpdate(int x, long value) {
    for (; x < MAX; x += x & -x)
      tree[x] += value;
  }

  static long BITRead(int x) {
    long sum = 0;
    for (; x > 0; x -= x & -x) 
      sum += tree[x];
    return sum;
  } 

  static class TreeNode {
    int key;
    long value;
    ArrayList<TreeNode> children = new ArrayList<TreeNode>();

    void Update() {
      long sum_before = BITRead(key - 1);
      for (TreeNode w : children) 
        w.Update();
      BITUpdate(key, value);
      value = BITRead(key - 1) - sum_before;
    }
  }

  public static void main(String[] args) throws IOException {
    BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
    int N = Integer.parseInt(input.readLine());
    int root = -1;
    ArrayList<TreeNode> nodes = new ArrayList<TreeNode>();
    for (int i = 0; i < N; i++)
      nodes.add(new TreeNode());

    for (int i = 0; i < N; i++) {
      String[] tokens = input.readLine().split(" ");
      int parent = Integer.parseInt(tokens[0]);
      nodes.get(i).key = Integer.parseInt(tokens[1]);
      nodes.get(i).value = Integer.parseInt(tokens[2]);
      if (parent == -1)
        root = i;
      else
        nodes.get(parent-1).children.add(nodes.get(i));
    }
    nodes.get(root).Update();
    PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    for (TreeNode node : nodes)
      out.println(node.value);
    out.flush();
  }
}
