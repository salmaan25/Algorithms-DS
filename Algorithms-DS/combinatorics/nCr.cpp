#include <bits/stdc++.h>
using namespace std;
int powmod(int a,int l, int md){int res=1;while(l){if(l&1)res=res*a%md;l/=2;a=a*a%md;}return res;}
int md = 1e9 + 7;
#define int long long
typedef ll long long;


const int MX = 400010;

int f[MX];
int rf[MX];

int C(int l,int k, int md) 
{
    if (k<0||k>l){
        return 0;
    }
    return f[l]*rf[k]%md*rf[l-k]%md;
}

void precfac() {
    f[0]=1;
    for (int i=1;i<MX;i++){
        f[i]=f[i-1]*i%MOD;
    }
    rf[MX-1]=powmod(f[MX-1],MOD-2, MOD);
    for (int i=MX-2;i>=0;i--){
        rf[i]=rf[i+1]*(i+1)%MOD;
    }
}
int main(void) {
    prec();
    ll ans = C(3, 2);
    return 0;
}