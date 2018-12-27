// Solution to Key to Knowledge
// Author: Kevin Buchin based on thomas.cpp

// Time complexity: O(n*2^(n/2))
// Memory: O(2^(n/2))

// @EXPECTED_RESULTS@: CORRECT

import java.util.Scanner;

class kevin {
	
	static class pair implements Comparable<pair> {
		long first;
		int second;
		
		pair(long x, int y) {
			first = x; second = y;
		}
		
		@Override
		public int compareTo(pair o) {
			if (first < o.first) return -1;
			else if (first > o.first) return 1;
			else return second - o.second;
		}
	}
	
	final static int nmax = 12, mmax = 30;

	static int[] StudentAnswers = new int[nmax];
	static int[] StudentScore= new int[nmax];

	static pair[] Scores1 = new pair[1<<(mmax/2)];
	static pair[] Scores2 = new pair[1<<(mmax-mmax/2)]; // (scores, answers)

	static int score (int m, int solution, int answers)
	{	return m - Integer.bitCount(solution ^ answers);
	}

	public static void main(String args[]) 
	{	int runs, run, n, m, a, a1, a2, i, j, k1, k2, m1, m2, nsol, solution;
		long s, s1, s2, target;
		String ins;
		char c;
		Scanner in = new Scanner(System.in);
		
		runs = in.nextInt();
		
		for (run = 0; run < runs; run++)
		{
			// Read input
			n = in.nextInt();
			m = in.nextInt();
			for (i = 0; i < n; i++)
			{	a = 0;
				ins = in.next();
				for (j = 0; j < m; j++)
				{	c = ins.charAt(j);
					a = 2*a; 
					a += (c=='0')?0:1;
				}
				StudentAnswers[i] = a;
				StudentScore[i] = in.nextInt();
			}

			// Accumulate all scores
			target = 0;
			for (i = 0; i < n; i++)
				target |= (((long)StudentScore[i]) << (5*i));
			// Split questions in two parts
			m1 = m/2;
			m2 = m-m1;
			// Consider all possible answers to the first m1 questions
			for (a1 = 0; a1 < (1<<m1); a1++)
			{	// Accumulate scores
				s1 = 0;
				for (i = 0; i < n; i++)
					s1 |= ((long)(score(m1, a1, StudentAnswers[i] >> m2))) << (5*i);
				Scores1[a1] = new pair(s1, a1);
			}
			// Consider all possible answers to the last m2 questions
			for (a2 = 0; a2 < (1<<m2); a2++)
			{	// Accumulate scores
				s2 = 0;
				for (i = 0; i < n; i++)
					s2 |= ((long)(score(m2, a2, StudentAnswers[i] & ((1<<m2)-1)))) << (5*i);
				Scores2[a2] = new pair(s2, a2);
			}
			java.util.Arrays.sort(Scores1, 0, (1<<m1));
			java.util.Arrays.sort(Scores2, 0, (1<<m2));

			nsol = solution = 0;
			i = 0;
			j = (1<<m2)-1;
			while (i < (1<<m1) && j >= 0)
			{	s = Scores1[i].first + Scores2[j].first; // Overall score
				if (s == target) // Solution found
				{	solution = ((Scores1[i].second << m2) | Scores2[j].second);
					// Check for redundancy
					k1 = k2 = 1;
					for (i++; i < (1<<m1) && Scores1[i].first == Scores1[i-1].first; i++, k1++);
					for (j--; j >= 0 && Scores2[j].first == Scores2[j+1].first; j--, k2++);
					nsol += k1*k2;
				}
				else if (s < target) // Score too small: try next smallest Scores1
					i++;
				else // Score too large: try next largest Scores2
					j--;
			}

			// Print answer
			if (nsol == 1)
			{	for (j = m-1; j >= 0; j--)
					System.out.print(((solution & (1<<j))==0)?0:1);
				System.out.println();
			}
			else
				System.out.println(nsol + " solutions");
		}
	}
}