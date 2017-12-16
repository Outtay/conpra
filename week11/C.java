import java.math.*;
import java.util.*;

public class C {

    public static void main(String[] args) {

        Scanner s = new Scanner(System.in);
        int t = s.nextInt();

        for (int i = 1; i <= t; i++){
            double digits = (double) s.nextLong();
            BigInteger a = s.nextBigInteger(); 
            long mod = (long) (Math.pow(10.0,digits));

            BigInteger m = BigInteger.valueOf(mod);

            System.out.println("Case #" + i + ": " + (a.modInverse(m)).toString());

        }
        s.close();
    
    }
}