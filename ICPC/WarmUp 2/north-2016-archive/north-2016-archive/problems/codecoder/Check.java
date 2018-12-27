/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem C. CodeCoder vs TopForces                              */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Egor Kulikov                             */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int n = inf.nextInt();
        for (int i = 0; i < n; i++) {
            int user = ouf.nextInt();
            int jury = ans.nextInt();
            if (user != jury) {
                return new Outcome(WA, String.format("For person %d: expected %d, found %d", i, jury, user));
            }
        }
        return new Outcome(OK, n + " answers");
    }
}

