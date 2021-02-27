#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;

#define int long long

//find_by_order(k) : returns an iterator to the k-th largest element (counting from zero)
//order_of_key(item) : number of items in a set that are strictly smaller than our item
//for set
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;   
// for multiset
typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_multiset;

#define ff first
#define ss second
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x.size())
int powmod(int a,int l, int md){int res=1;while(l){if(l&1)res=res*a%md;l/=2;a=a*a%md;}return res;}
int binpow(int a,int l){int res=1;while(l){if(l&1)res=res*a;l/=2;a=a*a;}return res;}
int invmod(int a, int md){return powmod(a,md-2,md);}
typedef long long ll; typedef unsigned long long ull; typedef long double ld;
typedef vector<int> vi; typedef pair<int, int> ii; typedef vector<ii> vii;
#define pb push_back
int __set(int b, int i) {return b|(1LL<<i);} //set ith bit
int __unset(int b, int i) {return b&(~(1UL<<i));}
int __check(int b, int i) {return b&(1LL<<i);} //returns 0 if ith bit is 0
int mulmod(int a, int b, int md) {return (((a%md)*(b%md))%md+md)%md;}
int addmod(int a, int b, int md) {return ((a%md+b%md)%md+md)%md;}
int submod(int a, int b, int md) {return (((a%md-b%md)%md)+md)%md;}
int divmod(int a, int b, int md) {return mulmod(a, powmod(b, md-2, md), md);} //if md is prime;
const ll inf = 0xFFFFFFFFFFFFFFFL; //very large number
priority_queue<int, vector<int>, greater<int> > pq; //for min priority_queue
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

signed main(void)
{
    IOS;
    
    return 0;
}