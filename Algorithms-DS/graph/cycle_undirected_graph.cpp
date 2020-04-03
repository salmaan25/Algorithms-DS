#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define int long long
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
// #define PI 3.1415926535897932384626433832795
#define PI acos(-1.0)
int MOD=1e9+7;
int powmod(int a,int l, int md){int res=1;while(l){if(l&1)res=res*a%md;l/=2;a=a*a%md;}return res;}
typedef long long ll; typedef vector<ll> vi; typedef pair<ll, ll> ii; typedef vector<ii> vii;
#define pb push_back
int __set(int b, int i) {return b|(1<<i);} //set ith bit
int __unset(int b, int i) {return b&(~(1UL<<i));}
int __check(int b, int i) {return b&(1<<i);} //returns 0 if ith bit is 0
int mul(int a, int b) {return ((a%MOD)*(b%MOD))%MOD;}
int add(int a, int b) {return (a+b)%MOD;}
int sub(int a, int b) {return (((a-b)%MOD)+MOD)%MOD;}
int __div(int a, int b) {return mul(a, powmod(b, MOD-2, MOD));} //if MOD is prime;
const ll inf = 0xFFFFFFFFFFFFFFFL; //very large number
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq; //for min priority_queue
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
clock_t time_p=clock();
void time()
{
    time_p=clock()-time_p;
    cerr<<"Time Taken : "<<(float)(time_p)/CLOCKS_PER_SEC<<"\n";
}

// map<char, int> m;
// bool cmp(const pair< pair<int,int> , int>& a, const pair < pair<int,int> , int>& b) {
// 	return a.ff.ss < b.ff.ss;
// }
// int mod=1e9+7;

vi vis(100100, 0);
int cyc1=-1, cyc2=-1;
vi par(100100, -1);
void dfs(int u, vector<vi>& adj) {
	vis[u]=1;
	for(int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if(!vis[v]) {
			par[v]=u;
			dfs(v, adj);
		}
		else if(vis[u]==1 && vis[v]==1 && par[u]!=v) {
			cyc1=u;
			cyc2=v;
		} 
	}
	vis[u]=2;
}
int32_t main(void) {
	IOS;
	int n,m; cin>>n>>m;
	vector<vi> adj(n);
	for(int i = 0; i < m; i++) {
		int u,v; cin>>u>>v;
		adj[u-1].pb(v-1);
		adj[v-1].pb(u-1);
	}
	for(int i = 0; i < n; i++) {
		if(cyc1!=-1) break;
		if(!vis[i]) {
			par[i]=i;
			dfs(i, adj);
		}
	}
	if(cyc1==-1) {
		cout<<"IMPOSSIBLE"<<endl;
		return 0;
	}
	int cur=cyc1;
	vi ans; ans.pb(cyc2);
	while(cur!=cyc2) {
		ans.pb(cur);
		cur = par[cur];
	}
	ans.pb(cyc2);
	cout<<ans.size()<<endl;
	for(int i: ans) cout<<i+1<<" ";
	cout<<endl;
   	time();
	return 0;
}