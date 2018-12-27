/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem G. Gangsters in Central City                           */
/*                                                                */
/* Original idea         Vitaly Aksenov                           */
/* Problem statement     Vitaly Aksenov                           */
/* Test set              Vitaly Aksenov                           */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Vitaly Aksenov                           */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.Outcome;
import ru.ifmo.testlib.InStream;

/**
 * Created by Aksenov239 on 02.10.2016.
 */
public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        inf.nextInt();
        int q = inf.nextInt();
        for (int i = 0; i < q; i++) {
            int jae = ans.nextInt();
            int pae = ouf.nextInt();
            if (jae != pae) {
                return new Outcome(Outcome.Type.WA, String.format("Action %d: Clogged pipes: expected %d, found %d", i + 1, jae, pae));
            }
            int jav = ans.nextInt();
            int pav = ouf.nextInt();
            if (jav != pav) {
                return new Outcome(Outcome.Type.WA, String.format("Action %d: Houses: expected %d, found %d", i + 1, jav, pav));
            }
        }
        return new Outcome(Outcome.Type.OK, String.format("%d answers", q));
    }

}

