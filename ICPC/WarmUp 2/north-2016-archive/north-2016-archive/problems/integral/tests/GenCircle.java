import java.io.PrintWriter;
import java.util.Random;

/**
 * Created by Niyaz Nigmatullin on 11.10.16.
 */
public class GenCircle {

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
        int maxx = Integer.parseInt(args[1]) - 1;
        Point2DInteger[] p = new Point2DInteger[n];
        double dAngle = Math.PI * 2 / n;
        for (int i = 0; i < n; i++) {
            double angle = i * dAngle;
            int x = (int) (Math.cos(angle) * maxx);
            int y = (int) (Math.sin(angle) * maxx);
            x += rnd.nextInt(3) - 1;
            y += rnd.nextInt(3) - 1;
            p[i] = new Point2DInteger(x, y);
        }
        p = GeometryAlgorithms.convexHull(p);
        if (p.length < 3) {
            throw new AssertionError();
        }
        if (rnd.nextBoolean()) {
            ArrayUtils.reverse(p);
        }
        {
            int k = rnd.nextInt(p.length);
            Point2DInteger[] np = new Point2DInteger[p.length];
            System.arraycopy(p, k, np, 0, p.length - k);
            System.arraycopy(p, 0, np, p.length - k, k);
        }
        PrintWriter out = new PrintWriter(System.out);
        out.println(p.length);
        for (Point2DInteger e : p) {
            out.println(e.x + " " + e.y);
        }
        out.close();
    }
}
