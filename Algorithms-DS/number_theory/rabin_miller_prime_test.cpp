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

ll pot(ll a, ll b, ll c){
   if(b == 0) return 1;
   if(b == 1) return a%c;
   ll resp = pot(a,b>>1,c);
   resp = mul_mod(resp,resp,c);
   if(b&1)
      resp = mul_mod(resp,a,c);
   return resp;
}

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