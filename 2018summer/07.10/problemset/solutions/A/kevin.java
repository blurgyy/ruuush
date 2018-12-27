// Solution to Avoiding the Apocalypse
// Author: Kevin Buchin

// Time complexity: O(V^2*E) = O(l^2*s*t^3)
// Memory: O((l+s)*t)

// @EXPECTED_RESULTS@: CORRECT
// Solution method: Dinic's Max FLow algorithm

 import java.util.Scanner;
 import java.util.ArrayList;
 import java.util.Arrays;
 
public class kevin {

	static final int MAXT = 100;
	static final int MAXL = 1000;
	static final int MAXS = 1000;
	static final int MAXN = (MAXT+1) * MAXL + 2;
	static final int MAXP = 100;

  static class Edge {
    int t, rev, cap, f;

    public Edge(int t, int rev, int cap) {
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
    graph.get(s).add(new Edge(t, graph.get(t).size(), cap));
    graph.get(t).add(new Edge(s, graph.get(s).size() - 1, 0));
  }

  static boolean dinicBfs(ArrayList<ArrayList<Edge>> graph, int src, int dest, int[] dist) {
    Arrays.fill(dist, -1);
    dist[src] = 0;
    int[] Q = new int[graph.size()];
    int sizeQ = 0;
    Q[sizeQ++] = src;
    for (int i = 0; i < sizeQ; i++) {
      int u = Q[i];
      for (Edge e : graph.get(u)) {
        if (dist[e.t] < 0 && e.f < e.cap) {
          dist[e.t] = dist[u] + 1;
          Q[sizeQ++] = e.t;
        }
      }
    }
    return dist[dest] >= 0;
  }

  static int dinicDfs(ArrayList<ArrayList<Edge>> graph, int[] ptr, int[] dist, int dest, int u, int f) {
    if (u == dest)
      return f;
    for (; ptr[u] < graph.get(u).size(); ++ptr[u]) {
      Edge e = graph.get(u).get(ptr[u]);
      if (dist[e.t] == dist[u] + 1 && e.f < e.cap) {
        int df = dinicDfs(graph, ptr, dist, dest, e.t, Math.min(f, e.cap - e.f));
        if (df > 0) {
          e.f += df;
          graph.get(e.t).get(e.rev).f -= df;
          return df;
        }
      }
    }
    return 0;
  }

  public static int maxFlow(ArrayList<ArrayList<Edge>> graph, int src, int dest) {
    int flow = 0;
    int[] dist = new int[graph.size()];
    while (dinicBfs(graph, src, dest, dist)) {
      int[] ptr = new int[graph.size()];
      while (true) {
        int df = dinicDfs(graph, ptr, dist, dest, src, Integer.MAX_VALUE);
        if (df == 0)
          break;
        flow += df;
      }
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
					//addEdge(graph, i+j*l, i+(j+1)*l,MAXP);
			
			m = in.nextInt();
			for(i=0; i<m; i++) 
			{
				//mIndex[i] = in.nextInt();
				//addEdge(graph, l*t+in.nextInt(), l*(t+1),MAXP);
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
			//System.out.println((p > maxFlow(graph, start, l*(t+1)))? "ZOMBIES" : "SAVED");
			//System.out.println( java.lang.Math.min(maxFlow(graph, start, l*(t+1)),p) );
			System.out.println( maxFlow(graph, l*(t+1)+1, l*(t+1)) );
			//System.out.println( java.lang.Math.min(maxFlow(graph, start, l*(t+1)),p) );
	}
  }
}
