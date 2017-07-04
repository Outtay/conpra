#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

long long gcd(long long n, long long m){
    while (m != 0){
        long long t = m;
        m = n % m;
        n = t;
    }
    return n;
}

std::vector<long> evenGold(long n, std::vector<bool> &primes){
    std::vector<long> result;
    for (long i = 2; i <= n/2; i++){
        if (primes[i] && primes[n-i]){
            result.push_back(i);
            result.push_back(n-i);
            return result;
        }
    }

    return result;
}

std::vector<long> oddGold(long n, std::vector<bool> &primes){
    std::vector<long> result;
    for (long i = 2; i <= n/2; i++){
        for (long j = 2; j <= n/2; j++){

            if (primes[i] && primes[j] && primes[n-i-j]){
                
                result.push_back(i);
                result.push_back(j);
                result.push_back(n-i-j);
                return result;
            }

        }
        
    }

    return result;
}


int main (){
    
    int t;
    std::cin >> t;

    std::vector<long> numbers;
    long max = 0;

    for (int i = 1; i <= t; i++) {

        long tmp;
        std::cin >> tmp;
        numbers.push_back(tmp);
        if (tmp > max)
            max = tmp;
    }

    std::vector<bool> primes = generatePrimes(max);
    
    for(int i = 1; i <= numbers.size(); i++){

        long n = numbers[i-1];
        std::vector<long> result;
        if (n % 2 == 0){
            result = evenGold(n, primes);
        } else {
            result = oddGold(n,  primes);
        }
        
        
        std::cout << "Case #" << i << ":"; 
        for(int i = 0; i < result.size(); i++)
            std::cout << " " << result[i];
        std::cout << "\n";

    }
    return 0;
}
