#include<bits/stdc++.h>
using namespace std;

int N = 1000000;
bool sieve[1000001];
void createSieve() {
    for(int i = 2; i <= N; i++) {
        sieve[i] = true;
    }
    for(int i=2; i*i <= N; i++) {
        if(sieve[i] == true) {
            for(int j = i*i; j <= N; j+=i) {
                sieve[j] = false;
            }
        }
    }
}

int main() {
    createSieve();
    int n;
    cin >> n;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(sieve[i] == 2) cnt++;
    }
    cout << cnt << endl;
}
