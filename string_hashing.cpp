// From https://cp-algorithms.com/
vector<long long> p_pow; 
vector<long long> prefix_hash;

void computePrefixHash(string &S) {
    const int p = 31; 
    int n = S.size();

    p_pow.assign(n, 0);
    prefix_hash.assign(n + 1, 0);
    
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % mod;

    for (int i = 0; i < n; i++)
        prefix_hash[i+1] = (prefix_hash[i] + (S[i] - 'a' + 1) * p_pow[i]) % mod; 
}

long long getSubstringHash(int l, int r, long long multiplier = 0) {
    long long cur_h = (prefix_hash[r] + mod - prefix_hash[l - 1]) % mod;
    return (cur_h * p_pow[multiplier] % mod);
}
