#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>


//source = http://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/

long inv(long a, long m)
{
    long m0 = m, t, q;
    long x0 = 0, x1 = 1;
 
    if (m == 1)
       return 0;
 
    // Apply extended Euclid Algorithm
    while (a > 1)
    {
        // q is quotient
        q = a / m;
 
        t = m;
 
        // m is remainder now, process same as
        // euclid's algo
        m = a % m, a = t;
 
        t = x0;
 
        x0 = x1 - q * x0;
 
        x1 = t;
    }
 
    // Make x1 positive
    if (x1 < 0)
       x1 += m0;
 
    return x1;
}
 
// k is size of num[] and rem[].  Returns the smallest
// number x such that:
//  x % num[0] = rem[0],
//  x % num[1] = rem[1],
//  ..................
//  x % num[k-2] = rem[k-1]
// Assumption: Numbers in num[] are pairwise coprime
// (gcd for every pair is 1)
long findMinX(std::vector<long> &num, std::vector<long> &rem, long k)
{
    // Compute product of all numbers
    long prod = 1;
    for (long i = 0; i < k; i++)
        prod *= num[i];
 
    // Initialize result
    long result = 0;
 
    // Apply above formula
    for (long i = 0; i < k; i++)
    {
        long pp = prod / num[i];
        result += rem[i] * inv(pp, num[i]) * pp;
    }
 
    return result % prod;
}

int main (){
    
    long t;
    std::cin >> t;
    for (long i = 1; i <= t; i++) {
        
        long n, invited;

        std::cin >> n >> invited;

        std::vector<long> nums;
        std::vector<long> remainders;
        
        for (long j = 0; j < n; j++){
            long p, r;
            std::cin >> p >> r;
            nums.push_back(p);
            remainders.push_back(r);
        }

        

        bool impossible = false;
        std::set<int> delid;
        //if duplicated primes, then impossible if the remainder isn't the same
        for (long j = 0; j < n; j++){
            for (long k = j; !impossible && k < n; k++){
                if (j != k && nums[j] == nums[k])
                    if (remainders[j] != remainders[k]){
                        impossible = true;
                    } else {
                        delid.insert(k);    
                    }
            }
        }

        if (impossible){
            std::cout << "Case #" << i << ": " << "impossible" << "\n";
            continue;
        }

        //delete 
        if ( !delid.empty()){
            std::vector<int> delIdVector;
            for (std::set<int>::iterator it=delid.begin(); it!=delid.end(); ++it){
                delIdVector.push_back(*it);
            }
            std::sort(delIdVector.begin(), delIdVector.end(), std::greater<int>());
            for (int k = 0; k < delIdVector.size(); k++){
                nums.erase(nums.begin() + delIdVector[k]);
                remainders.erase(remainders.begin() + delIdVector[k]);
                n--;
            }
        }
        
        long min = findMinX(nums, remainders, n);
        if(min > invited) impossible = true;


        if (impossible){
            std::cout << "Case #" << i << ": " << "impossible" << "\n";
            continue;
        }

        long primeTotal = 1;
        for (long j = 0; j < n; j++){
            primeTotal *= nums[j];
        }

        long j = 1;
        long tmp = min;
        long result;
        while (tmp <= invited){
            result = tmp;
            tmp = min + primeTotal * j;
            j++;
        }

        if (nums.size() == 1){
            long sum = nums[0] + remainders[0];
            if(result < sum && sum <= invited){
                std::cout << "Case #" << i << ": " << nums[0] + remainders[0] << "\n";
                continue;
            }
            if (result < remainders[0] && remainders[0] <= invited){
                std::cout << "Case #" << i << ": " << remainders[0] << "\n";
                continue;
            }
        }
        
        std::cout << "Case #" << i << ": " << result << "\n";

    }
    return 0;
}
