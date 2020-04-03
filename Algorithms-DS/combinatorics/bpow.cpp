#include <bits/stdc++.h>
using namespace std;

int bpow(int a,int l, int md) {
    int res=1;
    while (l) {
        if (l&1)
            res=res*a%md;
        l/=2;
        a=a*a%md;
    }
    return res;
}