#include <bits/stdc++.h>
using namespace std;

int N = 100001;
bool sieve[100001];

void createSieve() {
    for(int i = 0; i <= N; i++) sieve[i] = 1;
    for(int i = 2; i*i <= N; i++) {
        if(sieve[i] == 1)
            for(int j = i*i; j <= N; j+=i) {
                sieve[j] = 0;
            }
    }
}

vector<int> generatePrimes(int n) {
    vector<int> ds;
    for(int i = 2; i<= n; i++) {
        if(sieve[i]) ds.push_back(i);
    }
    return ds;
}

void segSieve(long long l, long long r) {    
    // generate all sqrt(r) primes;
    vector<int> primes = generatePrimes(sqrt(r));    

    // Take dummy array of size r-l+1;
    int dummy[r-l+1];
    for(int i = 0; i <= r-l; i++) dummy[i] = 1;

    // Mark all primes with the prime factors in primes array;
    for(auto pr: primes) {
        int firstMul = (l/pr)*pr;
        if(firstMul < l) firstMul += pr;
        for(int j = max(firstMul, pr*pr); j<=r; j+=pr) {
            dummy[j-l] = 0;
        }
    }

    // Get all primes
    if(l == 1) dummy[0] = 0;
    for(int i = l; i<= r; i++) {
        if(dummy[i-l]) cout << i << endl;
    }
    return;
}

int main() {
    createSieve();
    long long i = 2;
    int range = 100000;
    while(i <= (long long)1e9) {
        long long next = (i+range < 1e9) ? i+range : 1e9;
        segSieve(i, next);
        i += range + 1;
    }
    return 0;
}
