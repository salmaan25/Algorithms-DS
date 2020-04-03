//PRECISION PROBLEM COMES BECAUSE IN FFT WE do w0*w THIS CAUSES PRECISION ERROR THUS NOT GIVING ACCURATE ANSWERS.

typedef complex<double> cd;
typedef vector<cd> vcd;

void pad(vi& poly1, vi& poly2, vcd& p1, vcd& p2) {
	ll sz = (ll)poly1.size() + (ll)poly2.size();
	ll mx = 2;
	while(sz > 1) {
		mx *= 2;
		sz = sz>>1;
	}
	sz = (ll)poly1.size() + (ll)poly2.size();
	if(sz == mx/2)
		mx /= 2;
	for(ll i = (ll)poly1.size(); i < mx; i++)
		poly1.pb(0);
	for(ll i = (ll)poly2.size(); i < mx; i++)
		poly2.pb(0);
	for(ll i = 0; i < (ll)poly1.size(); i++) {
		p1.pb({(double)poly1[i], 0.0});
		p2.pb({(double)poly2[i], 0.0});	
	}
}

void FFT(vcd& a, bool invert) {
	ll n = (ll)a.size();
	if(n == 1) {
		return;
	}
	vcd a1, a2;
	for(ll i = 0; 2*i<n; i++) {
		a1.pb(a[2*i]); 
		a2.pb(a[2*i+1]);
	}
	FFT(a1, invert);
	FFT(a2, invert);
	double ang = 2 * PI / n * (invert ? -1 : 1);
	cd w0 = {1.0, 0.0};
	cd w = {cos(ang), sin(ang)};
	for(ll i = 0; 2*i < n; i++) {
		a[i] = a1[i] + w0*a2[i];
		a[i+n/2] = a1[i] - w0*a2[i];
		w0 *= w;
	}
}

void find_product(vi& poly1, vi& poly2, vi& result) {
	vcd p1; vcd p2;
	pad(poly1, poly2, p1, p2);
	bool invert = false;
	FFT(p1, invert);
	FFT(p2, invert);
	vcd sample3;
	for(ll i = 0; i < (ll)p1.size(); i++)
		sample3.pb(p1[i]*p2[i]);
	invert = true;
	FFT(sample3, invert);
	ll n = (ll)sample3.size();
	// result.clear();
	// result.resize(n);
	// vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result.pb(round(sample3[i].real()/n));
    // return result;
}

/*TEST MAIN
int main(void)
{
	// IOS;
	  //OF THE FORM {a_0, a_1, a_2, ...,a_(n-1)} where a_i is the coefficient of x^i
	// vi poly1 = {1, 2, 3, 0, 0, 0, 0, 0};
	// vi poly2 = {2, 5, 0, 0, 0, 0, 0, 0};
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
TEST MAIN*/