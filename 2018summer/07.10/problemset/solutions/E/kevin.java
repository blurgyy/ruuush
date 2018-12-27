// Solution to Benelux Software Engineers
// Author: Kevin Buchin

// Time complexity: O(n log n)
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

// Solution method:
// Incrementally build the set of interesting candidates according to (x,y) ignoring z: Insert points ordered by z (low to high rank). 
// Anyone that was on the short list at any point in time should be on the final shortlist
// A bit sloppy in the way it's implementing this, but it should be fast enough to pass

import java.util.*;

public class kevin {
	
	static final int NMAX = 100000;
	
	public static class Triple {
		int x,y,z;
		
		Triple(int x, int y, int z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
	}
	
	public static class TCompZYX implements Comparator<Triple> {

		public int compare(Triple s, Triple t) {
			return 4*Integer.signum(s.z-t.z) + 2 * Integer.signum(s.y-t.y) + Integer.signum(s.x-t.x) ;
		}
	}
	
	public static class TCompX implements Comparator<Triple> {

		public int compare(Triple s, Triple t) {
			return s.x-t.x ;
		}
	}
	
	
	public static void main(String[] args)
	{
		int runs;
		
		int n;
		Triple[] tripArr = new Triple[NMAX];
		
		Scanner in = new Scanner(System.in);
		
		runs = in.nextInt();


		while (runs-- != 0)
		{
			n = in.nextInt();
			int nShortlist = 0;
			
			for (int i=0; i<n; i++) tripArr[i] = new Triple(in.nextInt(),in.nextInt(),in.nextInt());
			Arrays.sort(tripArr,0,n, new TCompZYX());
			
			int M=0;
			NavigableSet<Triple> skyline2d = new TreeSet<Triple>(new TCompX());
			for (int i=0; i<n; i++)
			{
				Triple currPoint = tripArr[i];
				//System.out.println("68 " + currPoint.x + " " + currPoint.y);
				Triple vPoint = skyline2d.floor(currPoint);
				//System.out.println((vPoint==null)?"null":("70 " + vPoint.x + " " + vPoint.y));
				
				if ((vPoint == null)||(vPoint.y> currPoint.y)) {
				
					vPoint = skyline2d.ceiling(currPoint);
					//System.out.println("79");
					while ((vPoint != null)&&(vPoint.x>currPoint.x)&&(vPoint.y>currPoint.y)) {
						skyline2d.remove(vPoint);
						vPoint = skyline2d.ceiling(currPoint);
					}
					skyline2d.add(currPoint);
					//System.err.println(currPoint.x + " " + currPoint.y);
					nShortlist++;
				}
			}
			System.out.println(nShortlist);
		}
	}
}