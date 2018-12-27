// Solution to Button Bashing
// Author: Kevin Buchin, based on thomas.cpp

// Time complexity: O()
// Memory: O()

// @EXPECTED_RESULTS@: CORRECT

class kevin {

	final static int nmax = 16, tmax = 3600;

	static int[] B = new int[nmax];

	static int[] BFS = new int[tmax+1];
	static int[] Presses = new int[tmax+1];
	static boolean[] Seen = new boolean[tmax+1];

	public static void main(String args[]) 
	{	int runs, run, n, t, i, k, k2, cur, last;

		java.util.Scanner in = new java.util.Scanner(System.in);
		runs = in.nextInt();
		
		for (run = 0; run < runs; run++)
		{
			// Read input
			n = in.nextInt();
			t = in.nextInt();
			
			for (i = 0; i < n; i++) B[i] = in.nextInt();

			for (i = 1; i < tmax + 1; i++) Seen[i] = false; 
			Seen[0] = true;
			
			BFS[0] = 0;
			Presses[0] = 0;
			last = 1;
			for (cur = 0; cur < last; cur++)
			{	k = BFS[cur];
				for (i = 0; i < n; i++)
				{	k2 = java.lang.Math.min(tmax, java.lang.Math.max(0, k+B[i]));
					if (!Seen[k2])
					{	Seen[k2] = true;
						Presses[k2] = Presses[k] + 1;
						BFS[last++] = k2;
					}
				}
			}
			for (k = t; !Seen[k]; k++); // Find smallest reachable time > t
			System.out.println(Presses[k] + " " + (k-t));
		}
	}
}