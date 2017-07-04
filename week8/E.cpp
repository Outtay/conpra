#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <utility>
#include <stdint.h>


//Source for everything: http://fishi.devtail.io/weblog/2015/06/25/computing-large-binomial-coefficients-modulo-prime-non-prime/

long mod_exp(long b, long e, long mod){
    long r = 1;
    while (e > 0){
        if ((e&1) == 1)
            r = (r*b)%mod;
        b = (b*b)%mod;
        e >>= 1;
    }
    return r;
}

long fact_exp(long n, long p){
    long e = 0;
    long u = p;
    long t = n;
    while (u <= t){
        e += t/u;
        u *= p;
    }
    return e;
}


std::vector<long> get_base_digits(long n, long b){
    std::vector <long> d;
    while (n>0){
        d.push_back(n % b);
        n = n / b;
    }
    return d;
}

void egcd(long a, long b, long &x, long &y){
    long u = 1; long v = 0;
    x = 0; y = 1;
    while (a != 0){
        long q = b/a;
        long r = b % a;
        long m = x-u*q;
        long n = y-v*q;
        b = a; a = r;
        x = u; y = v;
        u = m; v = n;
    }

}

long crt (std::vector< std::pair <long, long> > congruences){
    long m = 1;
    for (long i = 0; i < congruences.size(); i++){
        m *= congruences[i].second;
    }

    long long int result = 0LL;
    for (long i = 0; i < congruences.size(); i++){
        long x, y;
        egcd(m/congruences[i].second,congruences[i].second, x, y);
        result += (congruences[i].first * x * m)/congruences[i].second;
    }
    return ((result % m) + m) % m;
}



long fermat_binom_advanced(long n, long k, long p){
    long num_degree = fact_exp(n,p) - fact_exp(n-k,p);
    long den_degree = fact_exp(k,p);
    if (num_degree > den_degree)
        return 0;
    if (k>n)
        return 0;
    
    long num = 1;
    for (long i = n; i > n-k; i--){
        long cur = i;
        while ( (cur % p) == 0){
            cur /= p;
        }
        num = (num * cur ) % p;
    }

    long denom = 1;
    for (long i = 1; i < k+1; i++){
        long cur = i;
        while ( (cur % p) == 0){
            cur /= p;
        }
        denom = (denom * cur) % p;
    }
    return (num * mod_exp(denom,p-2,p)) % p;
}


long lucas_binom(long n, long k, long p){
    std::vector<long> np = get_base_digits(n,p);
    std::vector<long> kp = get_base_digits(k,p);

    long binom = 1;
    for (long i = np.size()-1; i >= 0; i-- ){
        long ni = np[i];
        long ki = 0;
        if (i < kp.size())
            ki = kp[i];
        
        binom = (binom * fermat_binom_advanced(ni,ki,p)) % p;
    }
    return binom;
}


long binom(long n, long k, std::vector<long> mod_facts){
    std::vector< std::pair<long, long> > congruences;
    for (long i = 0; i < mod_facts.size(); i++){
        congruences.push_back(std::make_pair(lucas_binom(n,k,mod_facts[i]),mod_facts[i]));
    }
    return crt(congruences);
}

int main (){
    
    long t;
    std::cin >> t;
    std::vector<long> mod_facts;
    mod_facts.push_back(2);
    mod_facts.push_back(3);
    mod_facts.push_back(5);
    mod_facts.push_back(7);
    mod_facts.push_back(11);
    mod_facts.push_back(13);
    mod_facts.push_back(17);
    mod_facts.push_back(19);
    mod_facts.push_back(23);
    
    for (long i = 1; i <= t; i++) {
        long n, m;
        std::cin >> n >> m;
        

        std::cout << "Case #" << i << ": " << binom(n,m,mod_facts) << "\n";
    }
    return 0;
}
