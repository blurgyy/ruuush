// Solution to Highway Hassle
// Author: Kevin Buchin based on thomas.cpp

// Time complexity: O(s*m*log m)
// Memory: O(n*s)

// @EXPECTED_RESULTS@: CORRECT

import java.util.*;
	
class kevin {

	static final int nmax = 1000, smax = 120;

	static final int infty = 1<<30;

	static int[] X = new int[smax+1];
	static int[] P = new int[smax+1];
	static int[][] Dis = new int[smax][nmax];
	static int[] Dis2 = new int[2*smax*smax];
	static ArrayList<ArrayList<Integer> > Adj = new ArrayList<ArrayList<Integer> >(2*smax*smax);
	static ArrayList<ArrayList<Integer> > Len = new ArrayList<ArrayList<Integer> >(2*smax*smax);
	static ArrayList<Map<Integer,Integer> > T = new ArrayList<Map<Integer,Integer> >(smax+1);

	static class node implements Comparable<node>
	{	int k, dis;
		node (int a, int b) {
			k = a; dis = b;
		} 
		
		@Override
		public int compareTo(node o) {
        return this.dis - o.dis;
		}
	}

	static void dijkstra (int start, int n, int maxdis, int D[])
	{	int i, j, k, dis, dis2;
		PriorityQueue<node> pq = new PriorityQueue<node>();
		
		//System.err.println(D.length);
		for (i=0; i<n;i++) D[i] = infty;
		D[start] = 0;
		pq.add(new node(start, 0));
		while (!pq.isEmpty())
		{	k = pq.peek().k;
			dis = pq.poll().dis;
			if (D[k] < dis)
				continue;
			for (i = Adj.get(k).size()-1; i >= 0; i--)
				if ((dis2 = dis + Len.get(k).get(i)) <= maxdis && D[j = Adj.get(k).get(i)] > dis2)
					pq.add(new node(j, D[j] = dis2));
		}
	}

	public static void main(String args[]) 
	{	int runs, run, n, m, s, t, a, b, f, x, c, d, i, j, cs, dis;
		Iterator <Map.Entry<Integer,Integer>> it, it2;
		
		for (i = 0; i < 2*smax*smax; i++) {	
			Adj.add(new ArrayList<Integer>());
			Len.add(new ArrayList<Integer>());
			//Dis2[i]=0;
		}		
		for (i = 0; i < smax+1; i++) {	
			T.add(new TreeMap<Integer,Integer>());
		}
		
		Scanner in = new Scanner(System.in);
		
		runs = in.nextInt();
		
		for (run = 0; run < runs; run++)
		{
			// Read input
			n = in.nextInt(); m = in.nextInt(); s = in.nextInt(); t = in.nextInt();
			
			for (i = 0; i < n; i++)
			{	Adj.get(i).clear();
				Len.get(i).clear();
			}
			for (j = 0; j < m; j++)
			{	a = in.nextInt(); b = in.nextInt(); f = in.nextInt();	
			
				Adj.get(a-1).add(b-1);
				Adj.get(b-1).add(a-1);
				Len.get(a-1).add(f);
				Len.get(b-1).add(f);
			}
			for (i = 0; i < s; i++)
			{	x = in.nextInt(); P[i] = in.nextInt();		
				X[i] = x-1;
			}
			c = in.nextInt(); d = in.nextInt();		

			// Find station at start node
			for (i = 0; i < s && X[i] != c-1; i++);
			cs = i;
			// Add station with free petrol at end node
			X[s] = d-1;
			P[s] = 0;
			// Find shortest path from every station to all nodes within reach
			for (i = 0; i < s; i++)
				dijkstra(X[i], n, t, Dis[i]);
			// Create nodes (station,fuel)
			for (i = 0; i <= s; i++)
				T.get(i).clear();
			// Add a node for the start with zero fuel
			T.get(cs).put(0,0);
			// For all stations within reach of each other...
			for (i = 0; i < s; i++)
				for (j = 0; j <= s; j++)
					if (i != j && (dis = Dis[i][X[j]]) <= t)
					{	// If P[i] < P[j], get as much petrol as possible; otherwise, as little as possible
						T.get(i).put(P[i] < P[j] ? t : dis, 0);
						T.get(j).put(P[i] < P[j] ? t-dis : 0, 0);
					}
			// Assign unique id's to all nodes
			n = 0;
			for (i = 0; i <= s; i++) {
				it = T.get(i).entrySet().iterator();
				while (it.hasNext())
					it.next().setValue(n++);
			}
			for (i = 0; i < n; i++)
			{	Adj.get(i).clear();
				Len.get(i).clear();
			}
			// For every station, add an edge between all fuel nodes with corresponding price
			for (i = 0; i < s; i++)
				if (!T.get(i).isEmpty()) {
					it2 = T.get(i).entrySet().iterator();
					Map.Entry<Integer,Integer> previous = it2.next();
					Map.Entry<Integer,Integer> current;
					while (it2.hasNext())
					{	
						current = it2.next();
						Adj.get(previous.getValue()).add(current.getValue());
						Len.get(previous.getValue()).add(P[i] * (current.getKey() - previous.getKey()));
						previous = current;
					}
				}
			// Add an edge for all stations within reach of each other
			for (i = 0; i < s; i++)
				for (j = 0; j <= s; j++)
					if (i != j && (dis = Dis[i][X[j]]) <= t)
					{	a = T.get(i).get(P[i] < P[j] ? t : dis);
						b = T.get(j).get(P[i] < P[j] ? t-dis : 0);
						Adj.get(a).add(b);
						Len.get(a).add(0);
					}
			// Find shortest path
			dijkstra(T.get(cs).get(0), n, infty, Dis2);
			System.out.println(Dis2[n-1]);
		}
	}
}
