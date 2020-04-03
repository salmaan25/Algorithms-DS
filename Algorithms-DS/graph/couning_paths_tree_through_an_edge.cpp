// REFER TO https://www.urionlinejudge.com.br/judge/en/problems/view/2103 FOR PROBLEM STATEMENT 
// SOLUTION BASED ON https://codereview.stackexchange.com/questions/135915/sum-of-all-paths-between-all-pairs-of-nodes-in-a-tree
//GRAPH TREE PROBLEM MIGHT BE USEFUL FOR LONCYC  LONELY CYCLES


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<ll> vi;

ll mod = 1300031;
int main(void) {
	int t;
	scanf("%d" ,&t);
	while(t--) {
		ll V;
		scanf("%lld", &V);
		vector<vii> AdjList(V);
		for(ll i = 0; i < V-1; i++) {
			ll a, b, c;
			scanf("%lld%lld%lld", &a, &b, &c);
			AdjList[a-1].push_back(make_pair(b-1, c));
			AdjList[b-1].push_back(make_pair(a-1, c));
		}
		stack<ll> leaf;
		vi vertexWt(V, 1);
		vi degree(V);
		for(ll i = 0; i < V; i++) {
			ll deg = (ll)AdjList[i].size();
			if(deg == 1)
				leaf.push(i);
			degree[i] = deg;
		}
		ll ans = 0;
		while(!leaf.empty()) {
			ll u = leaf.top();
			leaf.pop();
			ans = (ans + vertexWt[u] * (V - vertexWt[u]) * AdjList[u][0].second)%mod;
			ll v = AdjList[u][0].first;
			vertexWt[v] += vertexWt[u];
			for(ll i = 0; i < (ll)AdjList[v].size(); i++) {
				if(AdjList[v][i].first == u) {
					AdjList[v].erase(AdjList[v].begin() + i);
					break;
				}
			}
			degree[v] -= 1;
			if(degree[v] == 1)
				leaf.push(v);
		}
		ans = ans%mod;
		printf("%lld\n", ans);
	}
	return 0;
}