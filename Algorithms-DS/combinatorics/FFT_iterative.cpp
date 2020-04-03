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

const double PI = acos(-1);
typedef complex<double> cd;
typedef vector<cd> vcd;
void FFT(vcd& a, bool invert, vcd& omega, ll init_n) {
	ll n = (ll)a.size();
	if(n == 1) {
		return;
	}
	vcd a1, a2;
	for(ll i = 0; 2*i<n; i++) {
		a1.pb(a[2*i]); 
		a2.pb(a[2*i+1]);
	}
	FFT(a1, invert, omega, init_n);
	FFT(a2, invert, omega, init_n);
	double ang = 2 * PI / n * (invert ? -1 : 1);
	ll mul = init_n/n;
	for(ll i = 0; 2*i < n; i++) {
		a[i] = a1[i] + omega[i*mul]*a2[i];
		a[i+(n/2)] = a1[i] - omega[i*mul]*a2[i];
	}
}

void find_product(vi& poly1, vi& poly2, vi& result) {
	vcd p1(poly1.begin(), poly1.end()); 
	vcd p2(poly2.begin(), poly2.end());
	ll sz = 1;
	while(sz < (ll)poly1.size() + (ll)poly2.size())
		sz <<= 1;
	p1.resize(sz);
	p2.resize(sz);
	bool invert = false;
	vcd omega(sz);
	double ang = 2 * PI / sz;
	for(ll i=0;i<sz;i++)
		omega[i]=cd(cos(i*ang), sin(i*ang));
	FFT(p1, invert, omega, sz);
	FFT(p2, invert, omega, sz);
	for(ll i = 0; i < (ll)p1.size(); i++)
		p1[i] *= p2[i];
	invert = true;
	ang = -2 * PI / sz;
	for(ll i=0;i<sz;i++)
		omega[i]=cd(cos(i*ang), sin(i*ang));
	FFT(p1, invert, omega, sz);
	ll n = (ll)p1.size();
    for (int i = 0; i < n; i++) {
    	ll tmp = round(p1[i].real()/n);
    	// tmp %= mod;
        result.pb(tmp);
    }
}

int main(void) {
	//OF THE FORM {a_0, a_1, a_2, ...,a_(n-1)} where a_i is the coefficient of x^i
	//IN THE EXAMPLE a_0 = 1, a_1 = 2, a_2 = 3
	vi poly1 = {1, 2, 3};
	vi poly2 = {2, 5};
	vi ans;
	find_product(poly1, poly2, ans);
	for(ll i = 0; i < (ll)ans.size(); i++)
		cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}