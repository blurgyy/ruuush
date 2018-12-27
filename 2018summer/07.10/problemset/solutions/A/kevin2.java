// Solution to Zombies
// Author: Kevin Buchin

// Time complexity: O(E*flow) = O(p*s*t)
// Memory: O((l+s)*t)

// @EXPECTED_RESULTS@: CORRECT
// Solution method: Edmond-Karp's Max FLow algorithm

 import java.util.Scanner;
 import java.util.ArrayList;
 import java.util.Arrays;
 
public class kevin2 {

	static final int MAXT = 100;
	static final int MAXL = 1000;
	static final int MAXS = 1000;
	static final int MAXN = (MAXT+1) * MAXL + 2;
	static final int MAXP = 100;

  static class Edge {
    int s, t, rev, cap, f;

    public Edge(int s, int t, int rev, int cap) {
      this.s = s;
      this.t = t;
      this.rev = rev;
      this.cap = cap;
    }
  }

  public static ArrayList<ArrayList<Edge>> createGraph(int nodes) {
    ArrayList<ArrayList<Edge>> graph = new ArrayList<ArrayList<Edge>>(nodes);
    for (int i = 0; i < nodes; i++)
      graph.add(new ArrayList<Edge>());
    return graph;
  }
  
  public static void recreateGraph(ArrayList<ArrayList<Edge>> graph, int nodes) {
    graph.clear();
    for (int i = 0; i < nodes; i++)
      graph.add(new ArrayList<Edge>());
  }
  
  public static void addEdge(ArrayList<ArrayList<Edge>> graph, int s, int t, int cap) {
    graph.get(s).add(new Edge(s, t, graph.get(t).size(), cap));
    graph.get(t).add(new Edge(t, s, graph.get(s).size() - 1, 0));
  }

  public static int maxFlow(ArrayList<ArrayList<Edge>> graph, int s, int t) {
    int flow = 0;
    int[] q = new int[graph.size()];
    while (true) {
      int qt = 0;
      q[qt++] = s;
      Edge[] pred = new Edge[graph.size()];
      for (int qh = 0; qh < qt && pred[t] == null; qh++) {
        int cur = q[qh];
        for (Edge e : graph.get(cur)) {
          if (pred[e.t] == null && e.cap > e.f) {
            pred[e.t] = e;
            q[qt++] = e.t;
          }
        }
      }
      if (pred[t] == null)
        break;
      int df = Integer.MAX_VALUE;
      for (int u = t; u != s; u = pred[u].s)
        df = Math.min(df, pred[u].cap - pred[u].f);
      for (int u = t; u != s; u = pred[u].s) {
        pred[u].f += df;
        graph.get(pred[u].t).get(pred[u].rev).f -= df;
      }
      flow += df;
    }
    return flow;
  }

  public static void main(String[] args) {
    ArrayList<ArrayList<Edge>> graph = new ArrayList<ArrayList<Edge>>(MAXN);
	//int[] mIndex = new int[MAXL];
	
	int runs, run, l, start, p, t, m, s, sA, sB, sP, sT, i;
		
	Scanner in = new Scanner(System.in);
		
	runs = in.nextInt();
		
	for (run = 0; run < runs; run++)
	{
			// Read input
			l = in.nextInt();
			start = in.nextInt();
			p = in.nextInt();
			t = in.nextInt();
			
			recreateGraph(graph, l*(t+1)+2);
			
			
			for(i=0; i<l; i++)
				for(int j=0; j<t; j++)
					addEdge(graph, i+j*l, i+(j+1)*l,p);
			
			m = in.nextInt();
			for(i=0; i<m; i++) 
			{
				//mIndex[i] = in.nextInt();
				addEdge(graph, l*t+in.nextInt()-1, l*(t+1),p);
			}
			addEdge(graph, l*(t+1)+1, start-1,p);
			
			s = in.nextInt();
			
			for(i=0; i<s; i++) {
				sA = in.nextInt();
				sB = in.nextInt();
				sP = in.nextInt();
				sT = in.nextInt();
				
				for (int j=0; j <= t-sT; j++) {
						addEdge(graph, sA+j*l-1, sB+(j+sT)*l-1, sP);
						
						//Am I allowed to use the road in any direction?
						//addEdge(graph, sB+j*l, sA+(j+sT)*l, sP);
				}
			}
			System.out.println( java.lang.Math.min(maxFlow(graph, l*(t+1)+1, l*(t+1)),p) );
	}
  }
}