#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>


int mod_exp(int b, int e, int mod){
    int r = 1;
    while (e > 0){
        if ((e&1) == 1)
            r = (r*b)%mod;
        b = (b*b)%mod;
        e >>= 1;
    }
    return r;
}

int fact_exp(int n, int p){
    int e = 0;
    int u = p;
    int t = n;
    while (u <= t){
        e += t/u;
        u *= p;
    }
    return e;
}


std::vector<int> get_base_digits(int n, int b){
    std::vector <int> d;
    while (n>0){
        d.push_back(n % b);
        n = n / b;
    }
    return d;
}

//init x with 0 and y with 1
void egcd(int a, int b, int &x, int &y){
    int u = 1; int v = 0;
    while (a != 0){
        int q = b/a;
        int r = b % a;
        int m = x-u*q;
        int n = y-v*q;
        b = a; a = r;
        x = u; y = v;
        u = m; v = n;
    }

}

/*
# Chinese Remainder Theorem
# Combine given congruences to one solution
def crt(congruences):
    # calculate the original modulo m
    m = 1
    for congruence in congruences:
        m *= congruence[1]

    # combine congruences
    result = 0
    for congruence in congruences:
        s, t = egcd(m//congruence[1],congruence[1])
        result += (congruence[0]*s*m)//congruence[1]

    return result%m
    */
//int crt (std::vector) 


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        
        std::cout << "Case #" << i << ": " << "something" << "\n";

    }
    return 0;
}
