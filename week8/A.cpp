#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

long long gcd(long long n, long long m){
    while (m != 0){
        long long t = m;
        m = n % m;
        n = t;
    }
    return n;
}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        long long n, m;
        std::cin >> n >> m;
        
        std::cout << "Case #" << i << ": " << gcd(n,m) << "\n";

    }
    return 0;
}
