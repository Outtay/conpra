# modular exponentiation: b^e % mod 
def mod_exp(b,e,mod):
    r = 1
    while e > 0:
        if (e&1) == 1:
            r = (r*b)%mod
        b = (b*b)%mod
        e >>= 1

    return r

# get degree of p in n! (exponent of p in the factorization of n!)
def fact_exp(n,p):
    e = 0
    u = p
    t = n
    while u <= t:
        e += t//u
        u *= p

    return e

# convert given number n into array of its base b representation
# most significant digit is at rightmost position in array
def get_base_digits(n,b):
    d = []
    while n > 0:
        d.append(n % b)
        n  = n // b

    return d

# Extended Euclidean GCD
# compute x,y for ax + by = gcd(a,b)
# here, a,b are coprime, meaning gcd(a,b) = 1
def egcd(a, b):
    x,y, u,v = 0,1, 1,0
    while a != 0:
        q, r = b//a, b%a
        m, n = x-u*q, y-v*q
        b,a, x,y, u,v = a,r, u,v, m,n
    gcd = b
    return (x, y)

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

# Using Fermat's little theorem to compute nCk mod p
# considering cancelation of p in numerator and denominator
# Note: p must be prime
def fermat_binom_advanced(n,k,p):
    # check if degrees work out
    num_degree = fact_exp(n,p) - fact_exp(n-k,p)
    den_degree = fact_exp(k,p)
    if num_degree > den_degree:
        return 0

    if k > n:
        return 0

    # calculate numerator and cancel out occurrences of p
    num = 1
    for i in range(n,n-k,-1):
        cur = i
        while cur%p == 0:
            cur //= p
        num = (num*cur)%p

    # calculate denominator and cancel out occurrences of p
    denom = 1
    for i in range(1,k+1):
        cur = i
        while cur%p == 0:
            cur //= p
        denom = (denom*cur)%p

    # numerator * denominator^(p-2) (mod p)
    return (num * mod_exp(denom,p-2,p))%p

# Using Lucas' theorem to split the problem into smaller sub-problems
# p must be prime
def lucas_binom(n,k,p):
    # get n and k in base p representation
    np = get_base_digits(n,p)
    kp = get_base_digits(k,p)

    # calculate (nCk) = (n0 choose k0)*(n1 choose k1) ... (ni choose ki) (mod p)
    binom = 1
    for i in range(len(np)-1,-1,-1):
        ni = np[i]
        ki = 0
        if i < len(kp):
            ki = kp[i]

        binom = (binom * fermat_binom_advanced(ni,ki,p)) % p

    return binom

# Compute n choose k for given prime factors of m
# prime factors need to have multiplicity 1 in m
def binom(n,k,mod_facts):
    # build congruences for all prime factors
    congruences = []
    for p in mod_facts:
        # add (binom,p) to congruence list
        congruences.append((lucas_binom(n,k,p),p))
        #print (str(congruences[-1][0]) + " " + str(congruences[-1][1]))

    # use CRT to combine congruences to one solution
    return crt(congruences)

if __name__ == '__main__':
    mod_facts = [2,3,5,7,11,13,17,19,23] # prime factors of m = 1155

    # (8100 choose 4000) mod 1155
    print(binom(18,3,mod_facts)) # should be 924