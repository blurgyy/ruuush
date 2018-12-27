import java.io.*;

public class MakeEven {
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);
    int n = Integer.parseInt(br.readLine());
    out.println(n);
    for (int i = 0; i < n; i++) {
      String[] f = br.readLine().split(" ");
      out.println(Integer.parseInt(f[0]) * 2 + " " + Integer.parseInt(f[1]) * 2);
    }
    out.close();
  }
}