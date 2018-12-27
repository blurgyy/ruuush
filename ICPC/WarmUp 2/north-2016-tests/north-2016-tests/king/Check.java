/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem K. King's Heir                                         */
/*                                                                */
/* Original idea         Andrew Stankevich                        */
/* Problem statement     Andrew Stankevich                        */
/* Test set              Pavel Kunyavskiy                         */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Pavel Kunyavskiy                         */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int user = ouf.nextInt();
        int jury = ans.nextInt();
        if (user != jury) {
            return new Outcome(WA, String.format("Expected %d, found %d", jury, user));
        } else {
            return new Outcome(OK, "" + jury);
        }
    }
}

