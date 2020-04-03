//USING POLICY BASED DATA STRUCTURES

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
//for set
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;   
// for multiset
typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_multiset;

typedef long long ll; typedef vector<ll> vi; typedef pair<ll, ll> ii; typedef vector<ii> vii;
#define pb push_back
const ll inf = 0xFFFFFFFFFFFFFFFL; //very large number
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define int long long

int32_t main(void)
{
	IOS;	
	ll n;
	cin>>n;
	vi a(n);
	for(ll i = 0; i < n; i++)
		cin>>a[i];
	map<ll, vi> m;
	for(ll i = 0; i < n; i++)
		m[a[i]].pb(i);
	vi pre(n); vi post(n);
	for(ll i = 0; i < n; i++) {
		pre[i] = lower_bound(m[a[i]].begin(), m[a[i]].end(), i)-m[a[i]].begin()+1;
		post[i] = m[a[i]].size()-pre[i]+1;
	}
	ll ans = 0;
	ordered_multiset os;
	os.insert({post[n-1], n-1});
	for(ll i = n-2; i >= 0; i--) {
		// cout<<os.order_of_key({pre[i], -1})<<" "<<i<<endl;
		ans += os.order_of_key({pre[i], -1});
		os.insert({post[i], i});	
	}
	cout<<ans<<endl;
	return 0;
}