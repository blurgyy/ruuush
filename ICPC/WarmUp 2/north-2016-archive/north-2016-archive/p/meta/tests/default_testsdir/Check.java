import ru.ifmo.testlib.*;

public class Check implements Checker {
    void check(InStream s, Outcome.Type type, String value) {
        if (!"Hi".equals(s.nextToken())) {
            throw new Outcome(type, "'Hi' expected");
        }
        if (!value.equals(s.nextToken())) {
            throw new Outcome(type, String.format("'%s' expected", value));
        }
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        if (!"Hello".equals(inf.nextToken())) {
            return new Outcome(Outcome.Type.FAIL, "'Hello' expected");
        }
        String value = inf.nextToken();
        check(ans, Outcome.Type.FAIL, value);
        check(ouf, Outcome.Type.WA, value);
        return new Outcome(Outcome.Type.OK, value);
    }
}
