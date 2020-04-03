#include <bits/stdc++.h>
using namespace std;
const long long int arr=2e5+10;
long long int md1=1e9+6;
long long int md2=(1e9+6)/2;
long long int md3 = 2;
long long int md4 = 1e9 + 7;

#define arr (long long int)(4e5+10)

long long int f[arr];
long long int rf[arr];
long long int n, k;

long long int bpow(long long int a,long long int l, long long int md)
{
    long long int res=1;
    while (l){
        if (l&1){
            res=res*a%md;
        }
        l/=2;
        a=a*a%md;
    }
    return res;
}

long long int C(long long int l,long long int k, long long int md) 
{
    if (k<0||k>l){
        return 0;
    }
    return f[l]*rf[k]%md*rf[l-k]%md;
}


long long int giveModmd1(long long int val1, long long int l, long long int  k) {
    long long int ans;
    if(k & (l - k)) 
        { //even nCp then p & (n - p) >= 1
            if(val1 % 2 == 1)
                ans = (md2 + val1) % md1;
            else 
                ans = (val1) % md1;
        }
    else {
        if(val1 % 2 == 1)
            ans = (val1) % md1;
        else
            ans = (md2 + val1) % md1;
    }
    return ans;
}

int main(void)
{
    f[0]=1;
    for (long long int i=1;i<arr;i++){
        f[i]=f[i-1]*i%md2;
    }
    rf[arr-1]=bpow(f[arr-1],md2-2, md2);
    for (long long int i=arr-2;i>=0;i--){
        rf[i]=rf[i+1]*(i+1)%md2;
    }
    
    int t;
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        scanf("%lld%lld", &n, &k);
        long long int nums[n + 1];
        for(long long int j = 1; j <= n; j++)
            scanf("%lld", &nums[j]);
        sort(nums + 1, nums + n + 1);
        // for(long long int j = 1;  j <= n; j++) {
        //     printf("%lld ", nums[j]);
        // }
        // printf("\n");
        long long int powers[n + 1];
        for(long long int j = 1; j <= n; j++) {
            powers[j] = 0;
        }
        long long int val1 = C(n - 1, k - 1, md2);
        val1 = giveModmd1(val1, n - 1, k - 1);
        for(long long int j = 2; j < n ; j++) {
            long long int val2 = C(j - 1, k - 1, md2);
            long long int val3 = C(n - j, k - 1, md2);
            val2 = giveModmd1(val2, j - 1, k - 1);
            val3 = giveModmd1(val3, n - j, k - 1);
            long long int val = (val1 - val2 - val3 + 3 * md1) % md1;
            powers[j] += val;
        }
        long long int ans = 1;
        long long int answers[n + 1];
        for(long long int j = 2; j <= n; j++) {
            answers[j] = bpow(nums[j], powers[j], md4);
            ans = (ans * answers[j]) % md4;
            // for(int k = 0; k < powers[j]; k++) {
            //     ans = (ans * nums[j]) % md4;
            // }
        }
        printf("%lld\n", ans);
    }
    
    return 0;
}