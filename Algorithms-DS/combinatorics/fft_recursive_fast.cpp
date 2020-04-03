const double PI = acos(-1);
typedef complex<double> cd;
typedef vector<cd> vcd;

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

int main(void) {
	//OF THE FORM {a_0, a_1, a_2, ...,a_(n-1)} where a_i is the coefficient of x^i
	vi poly1 = {1, 2, 3};
	vi poly2 = {2, 5};
	vi ans;
	find_product(poly1, poly2, ans);
	for(ll i = 0; i < (ll)ans.size(); i++)
		cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}