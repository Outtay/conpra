import java.math.*;
import java.util.*;

class itemstruct implements Comparator<itemstruct>, Comparable<itemstruct>{
    long util;
    long weight;

    itemstruct(long u, long w){
        this.util = u * w;
        this.weight = w;
    }

    public int compareTo(itemstruct i) {
        double d1 = (double) this.util/this.weight;
        double d2 = (double) i.util/i.weight;
        if (d1 > d2)
            return -1;
        if (d1 == d2)
            return 0;
        return 1;
    }
 
    public int compare(itemstruct i1, itemstruct i2) {
        Double d1 = (double) i1.util/i1.weight;
        Double d2 = (double) i2.util/i2.weight;
        return d2.compareTo(d1);
    }
}

public class J {

    public static void main(String[] args) {

        Scanner s = new Scanner(System.in);
        int t = s.nextInt();

        for (int i = 1; i <= t; i++){
            int n = s.nextInt();
            long max = s.nextLong() * 60;

            itemstruct[] items = new itemstruct[n];
            for (int j = 0; j < n; j++){
                String str = s.next();
                long u = s.nextLong();
                long w = s.nextLong();
                itemstruct tmp = new itemstruct(u, w);
                items[j] = tmp;
            }

            Arrays.sort(items);

            long current = 0;
            long result = 0;

            //fractional knapsack
            for (int j = 0; j < n; j++){
                if (current + items[j].weight <= max){
                    current += items[j].weight;
                    result += items[j].util;
                } else {
                    long rem = max - current;
                    result += items[j].util * rem/items[j].weight;
                    break;
                }

            }

            System.out.println("Case #" + i + ": " + result);

        }
        s.close();
    
    }
}