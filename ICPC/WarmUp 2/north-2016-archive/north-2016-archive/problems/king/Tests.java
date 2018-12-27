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
/* Tests                                                          */
/*                                                                */
/* Author                Pavel Kunyavskiy                         */
/******************************************************************/

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class Tests {
    Random rnd = new Random(123);

    public static void main(String[] args) {
        new Tests().gen();
    }

    Date genRandomDate() {
        int year = rnd.nextInt(10000) + 1;
        int month = rnd.nextInt(12) + 1;
        int day = rnd.nextInt(Date.daysInMonth[month]);
        return new Date(day, month, year);
    }

    Date genRandomDateInRange(Date date, int daysBeforeMin, int daysBeforeMax) {
        if (daysBeforeMin == -1) {
            int year = rnd.nextInt(date.year) + 1;
            int month = rnd.nextInt(year == date.year ? date.month : 12) + 1;
            int day = rnd.nextInt(year == date.year && month == date.month ? date.day - 1 : Date.daysInMonth[month]) + 1;
            return new Date(day, month, year);
        } else {
            return date.change(-(rnd.nextInt(daysBeforeMax - daysBeforeMin) + daysBeforeMin));
        }
    }

    public class TestCase {
        Date death;
        ArrayList<Date> dates;
        boolean noShuffle;

        public TestCase() {
            dates = new ArrayList<>();
        }

        void add(Date d) {
            if (!dates.contains(d)) {
                dates.add(d);
            }
        }

        void shrink(int n) {
            Collections.shuffle(dates, rnd);
            while (dates.size() > n) {
                dates.remove(dates.size() - 1);
            }
        }
    }

    int testId = 1;

    public void writeTest(TestCase test) {
        try {
            PrintWriter out = new PrintWriter(String.format("tests/%02d", testId++));
            out.println(test.death);
            out.println(test.dates.size());
            if (!test.noShuffle) {
                Collections.shuffle(test.dates, rnd);
            }
            test.dates.forEach(out::println);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    TestCase genSample1() {
        TestCase test = new TestCase();
        test.death = new Date(22, 10, 2016);
        test.noShuffle = true;
        test.add(new Date(28, 2, 1999));
        test.add(new Date(22, 7, 1995));
        test.add(new Date(21, 10, 1998));
        test.add(new Date(23, 10, 1998));
        test.add(new Date(3, 9, 2000));
        test.add(new Date(1, 4, 2013));
        test.add(new Date(17, 12, 2004));
        return test;
    }

    TestCase genSample2() {
        TestCase test = new TestCase();
        test.death = new Date(22, 10, 2016);
        test.noShuffle = true;
        test.add(new Date(28, 2, 1999));
        return test;
    }

    TestCase genRandomDeathDate(int n, Date death, int daysBeforeMin, int daysBeforeMax) {
        TestCase test = new TestCase();
        if (death == null) {
            death = genRandomDate();
        }
        test.death = death;

        for (int i = 0; i < n; i++) {
            test.add(genRandomDateInRange(death, daysBeforeMin, daysBeforeMax));
        }
        return test;
    }

    TestCase genRandom(int n) {
        return genRandomDeathDate(n, genRandomDate(), -1, -1);
    }

    TestCase genRange(Date d, int l, int r) {
        TestCase test = new TestCase();
        if (d == null) {
            d = genRandomDate();
        } else {
            d.fix();
        }
        test.death = d;

        for (int i = l; i <= r; i++) {
            test.add(d.change(i));
        }
        return test;
    }

    TestCase genPm(Date d, int c, int n) {
        TestCase test = new TestCase();
        if (d == null) {
            d = genRandomDate();
        } else {
            d.fix();
        }
        test.death = d;

        d = d.change(-18 * 365);

        for (int i = -c; i <= c; i++) {
            for (int j = -c; j <= c; j++) {
                for (int k = -c; k <= c; k++) {
                    Date nd = new Date(d.day + i, d.month + j, d.year + k);
                    nd.fix();
                    test.add(nd);
                }
            }
        }

        test.shrink(n);

        return test;
    }

    void writeTest3(TestCase test) {
        test.noShuffle = true;
        writeTest(test);
        Collections.reverse(test.dates);
        writeTest(test);
        test.noShuffle = false;
        writeTest(test);
    }

    public void gen() {
        new File("tests").mkdir();

        writeTest(genSample1());
        writeTest(genSample2());

        for (int i = 4; i <= 20; i += 4) {
            writeTest(genRandom(i));
        }
        writeTest(genRandomDeathDate(20, new Date(1, 1, 1900), -1, -1));
        writeTest(genRandomDeathDate(20, new Date(31, 12, 9999), -1, -1));
        writeTest(genRandomDeathDate(20, new Date(31, 1, 1), -1, -1));

        writeTest(genRandomDeathDate(20, null, 18 * 365 - 400, 18 * 365 + 400));
        writeTest(genRandomDeathDate(20, null, 1, 75 * 365));
        writeTest(genRandomDeathDate(20, null, 1, 18 * 365 - 1));

        writeTest3(genRange(null, -18 * 365 - 50, -18 * 365 + 49));
        writeTest3(genRange(new Date(1, 3, 2000), -18 * 365 - 50, -18 * 365 + 49));
        writeTest3(genRange(new Date(1, 1, 2000), -18 * 365 - 50, -18 * 365 + 49));
        writeTest3(genRange(new Date(101, 1, 1), -100, -1));
        writeTest3(genRange(new Date(31, 12, 9999), -100, -1));
        writeTest3(genRange(null, -18 * 365 - 99, -18 * 365));

        writeTest(genPm(null, 1, 100));
        writeTest(genPm(null, 2, 100));
        writeTest(genPm(new Date(1, 12, 2000), 1, 100));
        writeTest(genPm(new Date(1, 1, 2000), 1, 100));
        writeTest(genPm(new Date(28, 2, 2000), 1, 100));
        writeTest(genPm(new Date(1, 12, 2000), 2, 100));
        writeTest(genPm(new Date(1, 1, 2000), 2, 100));
        writeTest(genPm(new Date(28, 2, 2000), 2, 100));

    }
}

