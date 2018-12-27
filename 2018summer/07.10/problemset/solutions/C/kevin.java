// Solution to Citadel Construction
// Author: Kevin Buchin based on thomas-ternarysearch.cpp

// Time complexity: O(n^2 log n)
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT


class kevin {

	final static int nmax = 1000;

	static int[] X = new int[nmax];
	static int[] Y = new int[nmax];

	// Returns the area of a triangle (times two)
	// The answer is negative iff the loop a->b->c->a is clockwise
	static int area2 (int a, int b, int c)
	{	return X[a]*Y[b] - X[b]*Y[a] + X[b]*Y[c] - X[c]*Y[b] + X[c]*Y[a] - X[a]*Y[c];
	}

	static void swap (int a, int b) {
		int c = X[a];
		X[a] = X[b];
		X[b] = c;
		
		c = Y[a];
		Y[a] = Y[b];
		Y[b] = c;
	}

	// Gift wrap algorithm (O(n*m))
	// Returns number of vertices m
	static int convexhull (int n)
	{	int m, i, j = 0;
		// Find leftmost vertex
		for (i = 1; i < n; i++)
			if (X[i] < X[j])
				j = i;
		// Put at the front
		swap(0, j);

		for (m = 1; true; m++)
		{	// Find the vertex that is furthest to the right w.r.t. vertex m-1
			j = (m==1?1:0); // Start with 0, unless vertex m-1 is 0
			for (i = 0; i < n; i++)
				if (area2(m-1, i, j) > 0) // If (m-1)->i->j->(m-1) is counterclockwise
					j = i;
			if (j == 0) // Back to start
				return m;
			swap(m, j);
		}
	}

	static int ternarysearch (int a, int b, int m, int lb, int ub)
	{	int c1 = ((2*lb+ub)/3), c2 = ((lb+2*ub)/3);
		if (ub - lb < 3)
			return area2(a, c2%m, b);
		else if (area2(a, c1%m, b) > area2(a, c2%m, b))
			return ternarysearch(a, b, m, lb, c2);
		else
			return ternarysearch(a, b, m, c1, ub);
	}

	public static void main(String args[]) 
	{	int runs, run, n, i, j, m, amax;

		java.util.Scanner in = new java.util.Scanner(System.in);
		runs = in.nextInt();
		
		for (run = 0; run < runs; run++)
		{
			n = in.nextInt();
			for (i = 0; i < n; i++) {
				X[i] = in.nextInt();
				Y[i] = in.nextInt();
			}

			m = convexhull(n);
			amax = 0;
			for (i = 0; i < m; i++)
				for (j = i+1; j < m; j++)
					amax = java.lang.Math.max(amax, ternarysearch(i, j, m, i, j) + ternarysearch(j, i, m, j, i+m));
			if (amax % 2 == 0)
				System.out.println(amax/2);
			else
				System.out.println(amax/2 + ".5");
		}
	}
}