// iterative
ll power(ll base, ll exponent, ll modx = mod) {
    ll ret = 1 % modx;
    base %= modx;
    while(exponent) {
        if(exponent & 1) {
            ret = (ret * base) % modx;
        }
        base = (base * base) % modx;
        exponent >>= 1;
    }
    return ret;
}
ll inv(ll val, ll modx = mod) {
    return power(val, modx - 2, modx);
}
 
vector <ll> fac, ifac;
void preFac(ll sz) {
    fac.resize(sz + 1),
    ifac.resize(sz + 1);
    fac[0] = 1;
    for(int i = 1; i <= sz; i++) {
        fac[i] = (i * fac[i - 1]) % mod;
    }
    ifac[sz] = inv(fac[sz]);
    for(int i = sz - 1; i >= 0; i--) {
        ifac[i] = ((i + 1) * ifac[i + 1]) % mod;
    }
}
ll nCr(ll N, ll R) {
    if(R <= N && R >= 0) {
        return ((fac[N] * ifac[R]) % mod * ifac[N - R]) % mod;
    }
    return 0;
}
// recursive
int modpow(int x, int n, int m) {
    if (n == 0) return 1%m;
    long long u = modpow(x,n/2,m);
    u = (u*u)%m;
    if (n%2 == 1) u = (u*x)%m;
    return u;
}
