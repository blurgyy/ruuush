/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem I. Integral Polygons                                   */
/*                                                                */
/* Original idea         Niyaz Nigmatullin                        */
/* Problem statement     Dmitry Shtukenberg                       */
/* Test set              Niyaz Nigmatullin                        */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        long user = ouf.nextLong();
        long jury = ans.nextLong();
        if (user != jury) {
            return new Outcome(WA, String.format("Expected %d, found %d", jury, user));
        } else {
            return new Outcome(OK, "" + jury);
        }
    }
}

