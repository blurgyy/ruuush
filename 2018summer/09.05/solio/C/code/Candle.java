//  Candle Box solution
//  Author: Sergio Crisostomo
//  November 2016
//-------------------------------------------------

import java.util.*;

public class Candle
{
	public static final int RSTART = 4;
	public static final int TSTART = 3;

	public static void main( String[] args )
	{
		int D, Rsum, Tsum, Rbox, Tbox, Ra, Ta;

		Scanner in = new Scanner(System.in);
		D = in.nextInt();
		Rbox = in.nextInt();
		Tbox = in.nextInt();
	
		Rsum=0;
		Tsum=0;
		Ra = RSTART;
		Ta = TSTART;
		while(Rsum + Tsum < Rbox + Tbox){
			Rsum += Ra;
			Ra++;
			if(Ra >= TSTART + D){
				Tsum += Ta;
				Ta++;
			}
		}
	
		System.out.println(Rbox-Rsum);
	}
}
	
