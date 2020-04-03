#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;
#define mp make_pair
#define pb push_back
//typedef long long unsigned int ll;
// typedef long long int ll;
typedef long double float64;
//ll md = 1000000007;

ll mul_mod(ll a, ll b, ll m){
   ll y = (ll)((float64)a*(float64)b/m+(float64)1/2);
   y = y * m;
   ll x = a * b;
   ll r = x - y;
   if (r < 0 ){
      r = r + m; y = y - 1;
   }
   return r;
}

ll C,a,b;
ll gcd(){
   ll c;
   if(a>b){
      c = a; a = b; b = c;
   }
   while(1){
      if(a == 1LL) return 1LL;
      if(a == 0 || a == b) return b;
      c = a; a = b%a;
      b = c;
   }
}

ll f(ll a, ll b){
   ll tmp;
   tmp = mul_mod(a,a,b);
   tmp+=C; tmp%=b;
   return tmp;
}

ll pollard(ll n){
   if(!(n&1)) return 2;
   C=0;
   ll iteracoes = 0;
   while(iteracoes <= 1000){
      ll x,y,d;
      x = y = 2; d = 1;
      while(d == 1){
          x = f(x,n);
          y = f(f(y,n),n);
          ll m = (x>y)?(x-y):(y-x);
          a = m; b = n; d = gcd();
      }
      if(d != n)
          return d;
      iteracoes++; C = rand();
   }
   return 1;
}

ll pot(ll a, ll b, ll c){
   if(b == 0) return 1;
   if(b == 1) return a%c;
   ll resp = pot(a,b>>1,c);
   resp = mul_mod(resp,resp,c);
   if(b&1)
      resp = mul_mod(resp,a,c);
   return resp;
}

// Rabin-Miller primality testing algorithm
bool isPrime(ll n){
   ll d = n-1;
   ll s = 0;
   if(n <=3 || n == 5) return true;
   if(!(n&1)) return false;
   while(!(d&1)){ s++; d>>=1; }
   for(ll i = 0;i<32;i++){
      ll a = rand();
      a <<=32;
      a+=rand();
      a%=(n-3); a+=2;
      ll x = pot(a,d,n);
      if(x == 1 || x == n-1) continue;
      for(ll j = 1;j<= s-1;j++){
         x = mul_mod(x,x,n);
         if(x == 1) return false;
         if(x == n-1)break;
      }
      if(x != n-1) return false;
   }
   return true;
}
//map<ll,int> factors;
// Precondition: factors is an empty map, n is a positive integer
// Postcondition: factors[p] is the exponent of p in prime factorization of n
void fact(ll n, map<ll, ll>& factors){
   if(!isPrime(n)){
      ll fac = pollard(n);
      fact(n/fac, factors); fact(fac, factors);
   }else{
      map<ll,ll>::iterator it;
      it = factors.find(n);
      if(it != factors.end()){
         (*it).second = ((*it).second+1);
      }else{
         factors[n] = 1;
      }
   }
}



int main(void) {
   ll n = 10171165997;
   map<ll, ll> factors;
   cout<<"good"<<endl;
   fact(6237542524442623, factors);
   for(auto it = factors.begin(); it!=factors.end(); it++)
      cout<<it->first<<" ";
   cout<<endl;
   return 0;
}