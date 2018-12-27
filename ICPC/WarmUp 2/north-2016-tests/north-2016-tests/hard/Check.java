/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem H. Hard Cuts                                           */
/*                                                                */
/* Original idea         Georgiy Korneev                          */
/* Problem statement     Gennady Korotkevich                      */
/* Test set              Gennady Korotkevich                      */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Gennady Korotkevich                      */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;
import static ru.ifmo.testlib.Outcome.Type.FAIL;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
    	int tests = inf.nextInt();
    	for (int tc = 0; tc < tests; tc++) {
    	    int w = inf.nextInt();
    	    int h = inf.nextInt();
    	    int user = ouf.nextInt();
            if (user <= 0) {
                return new Outcome(Outcome.Type.WA, String.format("Test case %d (%d * %d): the number of squares should be positive, found %d", tc + 1, w, h, user));
            }
            if (user > w * h) {
                return new Outcome(Outcome.Type.WA, String.format("Test case %d (%d * %d): the number of squares should not exceed w * h, found %d", tc + 1, w, h, user));
            }
            int[][] a = new int[w][h];
    	    for (int id = 0; id < user; id++) {
    	        int x = ouf.nextInt();
    	        int y = ouf.nextInt();
    	        int side = ouf.nextInt();
    	        if (x < 0 || y < 0 || x > w || y > h || side <= 0 || side > w || side > h || x + side > w || y + side > h) {
                    return new Outcome(Outcome.Type.WA, String.format("Test case %d (%d * %d): invalid square %d %d %d", tc + 1, w, h, x, y, side));
    	        }
                for (int i = x; i < x + side; i++) {
                    for (int j = y; j < y + side; j++) {
                        if (a[i][j] > 0) {
                            return new Outcome(Outcome.Type.WA, String.format("Test case %d (%d * %d): cell (%d, %d) is covered by more than one square", tc + 1, w, h, i, j));
                        }
                        a[i][j]++;
                    }
    	        }
    	    }
	        for (int i = 0; i < w; i++) {
	          for (int j = 0; j < h; j++) {
	            if (a[i][j] == 0) {
                    return new Outcome(Outcome.Type.WA, String.format("Test case %d (%d * %d): cell (%d, %d) is not covered by any squares", tc + 1, w, h, i, j));
	            }
	          }
	        }
            int jury = ans.nextInt();
            if (jury < user) {
                return new Outcome(Outcome.Type.WA, String.format("Test case %d (%d * %d): expected %d squares, found %d", tc + 1, w, h, jury, user));
            }
            if (jury > user) {
                return new Outcome(Outcome.Type.FAIL, String.format("Test case %d (%d * %d): expected %d squares, found %d", tc + 1, w, h, jury, user));
            }
            for (int id = 0; id < user; id++) {
                ans.nextInt();
                ans.nextInt();
                ans.nextInt();
            }
    	}
        return new Outcome(OK, tests + " test cases");
    }
}

