#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


int modInverse(long long a, long long m){
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1)
    {
        // q is quotient
        q = a / m;
 
        t = m;
 
        // m is remainder now, process same as
        // Euclid's algo
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


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        long long n, y;

        std::cin >> n >> y;

        long long z = 9223372036854775100;

        long long k = 0;
        for (long long j = 0; j < z; j++){
            if (j % 3 == 0)
                k = z /1000 - j;
        }
        
        
        
        if (0)
            std::cout << "Case #" << i << ": " << "jackpot" << "\n";
        else 
            std::cout << "Case #" << i << ": " << "too bad" << "\n";

    }
    return 0;
}
