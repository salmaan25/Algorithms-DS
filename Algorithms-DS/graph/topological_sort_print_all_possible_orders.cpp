#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define PI 3.1415926535897932384626433832795
int MOD=1e9+7;
int powmod(int a,int l, int md){int res=1;while(l){if(l&1)res=res*a%md;l/=2;a=a*a%md;}return res;}
typedef long long ll; typedef vector<ll> vi; typedef pair<ll, ll> ii; typedef vector<ii> vii;
#define pb push_back
int __set(int b, int i) {return b|(1<<i);} //set ith bit
int __unset(int b, int i) {return b&!(1<<i);}
int __check(int b, int i) {return b&(1<<i);} //returns 0 if ith bit is 0
int mul(int a, int b) {return ((a%MOD)*(b%MOD))%MOD;}
int add(int a, int b) {return (a+b)%MOD;}
int sub(int a, int b) {return (((a-b)%MOD)+MOD)%MOD;}
int __div(int a, int b) {return mul(a, powmod(b, MOD-2, MOD));} //if MOD is prime;
const ll inf = 0xFFFFFFFFFFFFFFFL; //very large number
priority_queue<int, vector<int>, greater<int> > pq; //for min priority_queue
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
clock_t time_p=clock();
void time()
{
	time_p=clock()-time_p;
	cerr<<"Time Taken : "<<(float)(time_p)/CLOCKS_PER_SEC<<"\n";
}
int pres[26];
int n;
void solve(vi& ar, set< vector<char> >& ans, vector<vi>& adjlist, vi& tmp, vi& ind) {
	if(!ar.size()) {
		vector<char> tp;
		for(int i = 0; i < tmp.size(); i++) {
			tp.pb((char)(tmp[i]+'A'));
		}
		ans.insert(tp);
		return;
	}
	vi ar1;
	int v = ar[0];
	for(int i  = 1; i < ar.size(); i++)
		ar1.pb(ar[i]);
	vi ind1;
	for(int i = 0; i < ind.size(); i++)
		ind1.pb(ind[i]);
	for(int i = 0; i < adjlist[v].size(); i++) {
		ind1[adjlist[v][i]]--;
		if(!ind1[adjlist[v][i]])
			ar1.pb(adjlist[v][i]);
	}
	sort(all(ar1));
	while(1) {
		vi tmp1;
		for(int i = 0; i < tmp.size(); i++)
			tmp1.pb(tmp[i]);
		tmp1.pb(v);
		solve(ar1, ans, adjlist, tmp1, ind1);
		if(!next_permutation(all(ar1)))
			break;
	}
}
void dfs(int v, vector<vi>& adjlist, vi& vis, int* loop) {
	vis[v]=1;
	for(int i = 0; i < adjlist[v].size(); i++) {
		if(!vis[adjlist[v][i]])
			dfs(adjlist[v][i], adjlist, vis, loop);
		else if(vis[v]==1 && vis[adjlist[v][i]]==1)
			*loop=1;
	}
	vis[v]=2;
}

int32_t main(void)
{
	// IOS;
	int t;
	scanf("%lld", &t);
	getchar();
	string line;
	while(t--) {
		while((getchar()) != '\n');	
		getline(cin, line);
		stringstream sin;
		sin << line;
		string s;
		s = "";
		while(sin >> line)  s += line;
		sort(s.begin(), s.end());
		getline(cin, line);
		vector<vi> adjlist(26);
		sin.clear();
		sin << line;
		while(sin >> line) {
			adjlist[line[0]-'A'].pb(line[2]-'A');
		}

		n = s.length();
		memset(pres, 0, sizeof(pres));
		for(int i = 0; i < n; i++)
			pres[s[i]-'A']=1;
		vi vis(26, 0);
		int loop=0;
		for(int i = 0; i < n; i++) {
			if(!vis[i])
				dfs(i, adjlist, vis, &loop);
		}
		if(loop) {
			cout<<"NO"<<endl;
			if(t!=0)
				cout<<endl;
			continue;
		}
		vi ind(26, 0);
		for(int i = 0; i < 26; i++) {
			for(int j = 0; j < adjlist[i].size(); j++)
				ind[adjlist[i][j]]++;
		}
		vi ar;
		for(int i = 0; i < 26; i++) {
			if(!ind[i] && pres[i])
				ar.pb(i);
		}
		int st=0;
		set< vector<char> > ans; int in = 0;
		vi tmp;
		sort(all(ar));
		while(1) { 
			solve(ar, ans, adjlist, tmp, ind);
			if(!next_permutation(all(ar)))
				break;
		}
		for(auto it = ans.begin(); it != ans.end(); it++) {
			const vector<char>& tp = (*it);
			for(int j = 0; j < tp.size(); j++) {
				if(j != tp.size()-1)
					cout<<tp[j]<<" ";
				else cout<<tp[j];
			}
			cout<<endl;
		}
		if(t!=0)
		cout<<endl;
	}
	time();	
	return 0;
}