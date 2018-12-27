// Solution to Floating Formation
// Author: Kevin Buchin

// @EXPECTED_RESULTS@: CORRECT

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Stack;

public class kevin
{

	public static void main(String[] args)
	{
		final int nmax = 10000;
		
		int runs, run, n, m, k;
		ArrayList<ArrayList<Integer> > edges = new ArrayList<ArrayList<Integer> >(nmax);
		for (int i=0; i<nmax; i++) edges.add(new ArrayList<Integer>());
		
		int[] nVisits = new int[nmax]; // we will traverse the non-2-connected part of the graph starting at leafs, and store how often we have seen a vertex
		int[] activeLeaf = new int[nmax]; // with a traversed vertex we store an "active" leaf 
		
		int nLeafs; // number of leafs
		int[] leaf = new int[nmax]; // indices of leafs
		int[] lPathlength = new int[nmax]; // how many designs a leaf could rescue
		
		Stack<Integer> unsafe = new Stack<Integer>();
		unsafe.ensureCapacity(nmax);
		
		Scanner in = new Scanner(System.in);
		
		runs = in.nextInt();
		
		for (run = 0; run < runs; run++)
		{
			// Read input
			n = in.nextInt();
			m = in.nextInt();
			k = in.nextInt();
			
			if (run > 0)
			{
				for (int i=0; i<n; i++) {
					edges.get(i).clear();
					nVisits[i] = 0;
				}
			}

			for (int i=0; i < m; i++)
			{
				int a;
				int b;
				a = in.nextInt();
				b = in.nextInt();
				
				edges.get(a-1).add(b-1);
				edges.get(b-1).add(a-1);
			}
			
			unsafe.clear();
			nLeafs = 0;
			for (int i=0; i < n; i++) {
				if (edges.get(i).size() == 1) {
					leaf[nLeafs] = i;
					lPathlength[nLeafs] = 1;
					activeLeaf[i]=nLeafs;
					unsafe.push(i);
					
					nLeafs++;
				} 
			}
			
			while(!unsafe.isEmpty()) {
				int currV = unsafe.pop();
				int nextV = -1;
				
				for (int i : edges.get(currV)) {
					if (nVisits[i] < edges.get(i).size()-1) {
						nextV = i;
						break;
					}
				}
				
				nVisits[nextV]++;
				if (nVisits[nextV] == 1) activeLeaf[nextV] = activeLeaf[currV];
				else {
					int oldL = lPathlength[activeLeaf[nextV]];
					int currL = lPathlength[activeLeaf[currV]];
					if (oldL<currL) activeLeaf[nextV] = activeLeaf[currV];
				}
				if (nVisits[nextV] == edges.get(nextV).size()-1) {
					lPathlength[activeLeaf[nextV]]++;
					unsafe.push(nextV);
				}
			}
			java.util.Arrays.sort(lPathlength, 0, nLeafs);
			int sum = 0;
			int j = k;
			if (j>nLeafs) j = nLeafs;
			for (int i=0; i< nLeafs - j; i++) sum += lPathlength[i];
			System.out.println(sum);
		}
	}
}
