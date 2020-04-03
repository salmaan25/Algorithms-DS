#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll md = 1000000007;

void factorize(ll n, map<ll, ll>& factors)
{
    //ll count = 0;
    if(n % 2 == 0) {
        factors[2]=1;
        n=n/2;
    }
    while (n%2 == 0)
    {
        factors[2]+=1;
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        if(n % i == 0) {
            factors[i]=1;
            n=n/i;
        }
        while (n%i == 0)
        {
            factors[i]+=1;
            n = n/i;
        }
    }
    if (n > 2)
        factors[n]=1;
}

int main(void) {
    ll n = 50;
    map<ll, ll> factors;
    factorize(50, factors);
    for(map<>::iterator it = factors.begin(); it != factors.end(); it++)
        printf("prime=%lld it's power=%lld\n", it->first, it->second);
    return 0;
}