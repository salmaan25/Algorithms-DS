//d stores the diameter for each component, For a component all the points of 
// that component store teh value of the diameter of that component./
// g is the graph and vis is visited array.

vector<vi> g(300010);
vi vis(300010,0);
void dfs(int u, int dp, vii& dis) {
	dis.pb({dp,u});
	vis[u]=1;
	for(int i = 0; i < sz(g[u]); i++) {
		int v=g[u][i];
		if(!vis[v]) {
			dfs(v,dp+1,dis);
		}
	}
}
void dfs1(int u, int dp, vii& dis) {
	dis.pb({dp,u});
	vis[u]=1;
	for(int i = 0; i < sz(g[u]); i++) {
		int v = g[u][i];
		if(!vis[v]) {
			dfs(v,dp+1,dis);
		}
	}
}
void diameter(int n, vi& d) {
	for(int i = 0; i < n; i++) {
		if(!vis[i]) {
			vii dis; 
			dfs(i,0,dis);
			sort(all(dis));
			int u = dis[sz(dis)-1].ss;
			for(int j = 0; j < sz(dis); j++)
				vis[dis[j].ss]=0;
			dis.clear();
			dfs1(u,0,dis);
			sort(all(dis));
			for(int j = 0; j < sz(dis); j++)
				d[dis[j].ss]=dis[sz(dis)-1].ff;
		}
	}
}