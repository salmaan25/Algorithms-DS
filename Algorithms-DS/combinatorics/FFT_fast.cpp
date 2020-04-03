//g++ --std=c++11 auto.cpp
//-fsanitize=address for segfault
#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define mem(a,val) memset(a,val,sizeof(a))
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
#define pb push_back
#define mp make_pair
// #define PI 3.1415926535897932384626433832795
const ll inf = 0xFFFFFFFFFFFFFFFL; //very large number
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define int long long
const double PI = acos(-1);
typedef complex<double> cd;
typedef vector<cd> vcd;
ll mod = 13313;
clock_t time_p=clock();
void time()
{
	time_p=clock()-time_p;
	cerr<<"Time Taken : "<<(float)(time_p)/CLOCKS_PER_SEC<<"\n";
}

void fft(const vcd &as, vcd& cur, bool invert) {
  int n = as.size();
  int k = 0;
  while ((1 << k) < n) k++;
  vector<int> rev(n);
  rev[0] = 0;
  int high1 = -1;
  for (int i = 1; i < n; i++) {
	if ((i & (i - 1)) == 0)
	  high1++;
	rev[i] = rev[i ^ (1 << high1)];
	rev[i] |= (1 << (k - high1 - 1));
  }

  vcd roots(n);
  for (int i = 0; i < n; i++) {
    double alpha;
    if(invert)
        alpha = -2 * PI * i / n;
    else
	   alpha = 2 * PI * i / n;
	roots[i] = cd(cos(alpha), sin(alpha));
  }
  cur.clear();
  cur.resize(n);
  for (int i = 0; i < n; i++)
	cur[i] = as[rev[i]];

  for (int len = 1; len < n; len <<= 1) {
	vcd ncur(n);
	int rstep = roots.size() / (len * 2);
	for (int pdest = 0; pdest < n;) {
	  int p1 = pdest;
	  for (int i = 0; i < len; i++) {
		cd val = roots[i * rstep] * cur[p1 + len];
		ncur[pdest] = cur[p1] + val;
		ncur[pdest + len] = cur[p1] - val;
		pdest++, p1++;
	  }
	  pdest += len;
	}
	cur.swap(ncur);
  }
  // return cur;
}

void find_product(vi& poly1, vi& poly2, vi& result) {
  vcd p1(poly1.begin(), poly1.end()); 
  vcd p2(poly2.begin(), poly2.end());
  // pad(poly1, poly2, p1, p2);
  ll sz = 1;
  while(sz < (ll)poly1.size() + (ll)poly2.size())
	sz <<= 1;
  p1.resize(sz);
  p2.resize(sz);
  vcd p11;
  vcd p22;
  bool invert = false;
  fft(p1, p11, invert);
  fft(p2, p22, invert);
  // vcd sample3;
  for(ll i = 0; i < (ll)p11.size(); i++)
	p11[i] *= p22[i];
  invert = true;
  vcd p111;
  fft(p11, p111, invert);
  ll n = (ll)p111.size();
	for (int i = 0; i < n; i++) {
	  ll tmp = round(p111[i].real()/n);
	  tmp %= mod;
		result.pb(tmp);
	}
}

void solve(vi& a, vi& ans, ll lo, ll hi) {
    if(lo == hi) {
        for(ll i = 0; i < a[lo]+1; i++)
            ans.pb(1);
        return;
    }
    ll mid = (lo+hi)/2;
    vi ans1, ans2;
    solve(a, ans1, lo, mid);
    solve(a, ans2, mid+1, hi);
    ll deg = (ll)ans1.size() + (ll)ans2.size() - 1;
    find_product(ans1, ans2, ans);
    ans.resize(deg);
}

int32_t main(void)
{
  IOS;
  vi poly1 = {1, 2, 3};
    vi poly2 = {2, 5};
    vi ans;
    find_product(poly1, poly2, ans);
    for(ll i = 0; i < (ll)ans.size(); i++)
        cout<<ans[i]<<" ";
    cout<<endl;
  time();
  return 0;
}