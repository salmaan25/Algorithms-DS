#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
int n,q;
vector<int> nxt(200010,0);
int prec[200010][30];
void create() {
	for(int i = 0; i < n; i++)
		prec[i][0]=nxt[i];
	for(int i=1; i < 30; i++) {
		for(int j=0; j<n; j++) {
			prec[j][i]=prec[prec[j][i-1]][i-1];
		}
	}
}
int solve(int u, int k) {
	int pp=0;
	while(k) {
		if(k%2) {
			u=prec[u][pp];
		}
		k/=2;
		pp++;
	}
	return u;
}
signed main(void)
{
	cin>>n>>q;
	for(int i = 0; i < n; i++) {
		cin>>nxt[i];
		nxt[i]--;
	}
	create();
	while(q--) {
		int u,k;
		cin>>u>>k; u--;
		cout<<solve(u,k)+1<<endl;
	}
	return 0;
}