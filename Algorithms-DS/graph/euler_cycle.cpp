//if we want euler cycle starting at a particular vertex say 0 then 
// check  if the degree of vertex 0 is not 0 
// cyc starts with the neighbor of the starting vertex and ends at starting vertex
// we need list for fast insertion in the middle
list<int> cyc;
void EulerTour(list<int>::iterator i, int u, vector<vii>& adj) {
	for (int j = 0; j < (int)adj[u].size(); j++) {
		ii& v = adj[u][j];
		if (v.second) { // if this edge can still be used/not removed
			v.second = 0; // make the weight of this edge to be 0 (‘removed’)
			for (int k = 0; k < (int)adj[v.first].size(); k++) {
				ii& uu = adj[v.first][k]; // remove bi-directional edge
				if (uu.first == u && uu.second) {
					uu.second = 0;
					break;
				} 
			}
			EulerTour(cyc.insert(i, u), v.first, adj);
		}
	}
}
void dfs(int u, vector<vii>& adj, vi& vis) {
	vis[u]=1;
	for(int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].ff;
		if(!vis[v])
			dfs(v,adj);
	}
}
int euler(vector<vi>& adj) {
	int n = (int)adj.size();
	vi vis((int)adj.size(),0);
	vi deg(n,0);
	for(int i = 0; i < n; i++)
		deg[i]=(int)adj[i].size();
	int cnt=0,cmp=0;
	for(int i = 0; i < n; i++) {
		if(deg[i]%2!=0)
			return 0;
		if(deg[i]==0)
			cnt++;
	}
	for(int i = 0; i < n; i++) {
		if(!vis[i]) {
			dfs(i,adj);
			cmp++;
		}
	}
	if(cmp-cnt!=1)
		return 0;
	cyc.clear();
	EulerTour(cyc.begin(), 0, adj);
	return 1;
}