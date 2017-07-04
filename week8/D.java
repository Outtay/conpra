import java.util.*;
import java.math.*;

public class D {
	//https://stackoverflow.com/questions/14224953/get-all-subsets-of-a-set
	public static ArrayList<ArrayList<Integer>> getSubsets2(ArrayList<Integer> set) {

        ArrayList<ArrayList<Integer>> allsubsets = new ArrayList<ArrayList<Integer>>();
        int max = 1 << set.size();             //there are 2 power n different subsets

        for (int i = 0; i < max; i++) {
            ArrayList<Integer> subset = new ArrayList<Integer>();
            for (int j = 0; j < set.size(); j++) {
                if (((i >> j) & 1) == 1) {
                    subset.add(set.get(j));
                }
            }
            allsubsets.add(subset);
        }
        return allsubsets;
    }
	
	public static BigInteger findlcm (Set<Integer> lcmNumbers){
		
	    BigInteger result = BigInteger.valueOf(0);
	 
	    for (int number : lcmNumbers){
	    	if (result.equals(BigInteger.valueOf(0))){
	    		result = BigInteger.valueOf(number);
	    		continue;
	    	}
	    			
	    	BigInteger bignum = BigInteger.valueOf(number);
	    	BigInteger tmp = bignum.multiply(result);
	    	result = tmp.divide(bignum.gcd(result));
	    }
		return result;
	}
	
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int t = s.nextInt();
				
		for(int i = 1; i <= t; i++ ){
			
			int n = s.nextInt();
			
			ArrayList<Integer> candies = new ArrayList<Integer>();
			for (int j = 0; j < n; j++){
	            int c = s.nextInt();
	            candies.add(c);
	        }
			
			ArrayList<ArrayList<Integer>> subsets = getSubsets2(candies);
			
			Set<Integer> lcmNumbers = new HashSet<Integer>();
			int max = 0;
			for (int j = 0; j < subsets.size(); j++){
	            int number = 0;
	            for (int k = 0; k < subsets.get(j).size(); k++){
	                number +=  subsets.get(j).get(k);
	            }
	            if (number > 0){
	                ++number;
	                lcmNumbers.add(number);
	            }
	            if (number > max)
	                max = number;
	        }
			BigInteger result = findlcm(lcmNumbers);
			
			System.out.println("Case #" + i + ": " + result.toString());
			
		}
		
		s.close();
	}
	
	
	
}