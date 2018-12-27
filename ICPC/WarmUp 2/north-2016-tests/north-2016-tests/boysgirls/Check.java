/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem B. Boys and Girls                                      */
/*                                                                */
/* Original idea         Pavel Mavrin                             */
/* Problem statement     Pavel Mavrin                             */
/* Test set              Pavel Mavrin                             */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;
import static ru.ifmo.testlib.Outcome.Type.FAIL;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
    	int n = inf.nextInt();
    	int x = inf.nextInt();
    	int y = inf.nextInt();
        String a = ouf.nextToken();
        if (a.equals("Impossible")) {
            if (ans.nextToken().equals("Impossible")) {
                return new Outcome(OK, "impossible");
            } else {
                return new Outcome(WA, "Not impossible");
            }
        }
        if (a.length() != n) {
            return new Outcome(WA, "Wrong length: expected " + n + ", found " + a.length());
        }
        for (int i = 0; i < n; i++) {
        	if (a.charAt(i) != 'B' && a.charAt(i) != 'G') {
        	    return new Outcome(WA, "Invalid character: " + a.charAt(i));
        	}
        }
        int xx = 0;
        int yy = 0;
        for (int i = 0; i < n; i++) {
        	if (a.charAt((i + 1) % n) == 'B' || a.charAt((i + n - 1) % n) == 'B') {
        		xx++;
        	}
        	if (a.charAt((i + 1) % n) == 'G' || a.charAt((i + n - 1) % n) == 'G') {
        		yy++;
        	}
        }
        if (xx != x) {
            return new Outcome(WA, "Wrong number of children standing next to a boy: " + xx + ", instead of " + x);
        }
        if (yy != y) {
            return new Outcome(WA, "Wrong number of children standing next to a girl: " + yy + ", instead of " + y);
        }
        if (ans.nextToken().equals("Impossible")) {
            return new Outcome(FAIL, "not impossible");
        }
        return new Outcome(OK, "");
    }
}

