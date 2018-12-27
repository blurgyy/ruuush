
import java.io.PrintWriter;
import java.util.Random;

/**
 * Created by Niyaz Nigmatullin on 11.10.16.
 */
public class GenConvexHull {

    static Random rnd;

    public static void main(String[] args) {
        {
            long seed = 0;
            for (String e : args) {
                seed = seed * 239017 + e.hashCode();
            }
            rnd = new Random(seed);
        }
        int n = Integer.parseInt(args[0]);
        int maxx = Integer.parseInt(args[1]);
        Point2DInteger[] p = new Point2DInteger[n];
        for (int i = 0; i < n; i++) {
            p[i] = new Point2DInteger(rnd.nextInt(maxx), rnd.nextInt(maxx));
        }
        p = GeometryAlgorithms.convexHull(p);
        if (p.length < 3) {
            throw new AssertionError();
        }
        if (rnd.nextBoolean()) {
            ArrayUtils.reverse(p);
        }
        PrintWriter out = new PrintWriter(System.out);
        out.println(p.length);
        for (Point2DInteger e : p) {
            out.println(e.x + " " + e.y);
        }
        out.close();
    }
}
