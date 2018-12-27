// Solution to Direction Dropping
// Author: Kevin Buchin

// Time complexity: O(n)
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

import java.util.Scanner;

public class kevin {

	public static void main(String[] args)
	{
		final int nmax = 100000;
		int[][] A = new int[nmax][4];
		
		int runs;
		int run = 0;
		
		Scanner in = new Scanner(System.in);
		runs = in.nextInt();

		while (run++ < runs)
		{
			int n = in.nextInt();
			int g = in.nextInt()-1;
			
			for(int i = 0; i< n; i++) {
				A[i][0] = in.nextInt()-1;
				A[i][1] = in.nextInt()-1;
				A[i][2] = in.nextInt()-1;
				A[i][3] = in.nextInt()-1;
			}
			
			int m=0;
			
			for(int i = 0; i< n; i++) {
				for(int j = 0; j<2; j++) { 
					
					int previous, current;
					if (A[i][j] != -1) {
						boolean seenGoal = (i==g);
						previous = i;
						current = A[i][j];
						int k = j;
						
						//System.out.println("new cycle");
						//System.out.println(previous + " " + current);
						while (current != -1) {
							if (g==current) seenGoal = true;
							
							A[previous][k] = -1;
							A[previous][(k+2)%4] = -1;
							
							for(k=0; (k<4)&&(A[current][k]!=previous);k++);
							previous = current;
							current = (k<4)? A[previous][(k+2)%4]:-1;
							//System.out.println(previous + " " + current);
							
						}
						if (!seenGoal) m++;
					}
				}
			}
			
			System.out.println(m); 

		}
	}
}
