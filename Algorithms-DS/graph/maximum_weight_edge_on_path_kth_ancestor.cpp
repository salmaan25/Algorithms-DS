// SIMILAR TO LCA_KTH_ANCESTOR BUT HERE ONE MORE FUNCTION KTH_MAX GIVES TEH MAXIMUM WEIGHT EDGE ON THE PATH FROM U TO IT'S KTH ANCESTOR. 
struct AncestorK {
public:
	int n,m,depth,root,timer;
	vector< vector<pair<int,int>> > g; vector< vector<int> > table,mn;
	vector<int> dis,parent,tin,tout,sub;
	void dfs(int u) {
		tin[u]=++timer;
		for(pair<int,int> p: g[u]) {
			int v=p.ff,w=p.ss;
			if(dis[v]==-1) {
				dis[v]=dis[u]+1;
				depth=max(depth,dis[v]);
				parent[v]=u;
				table[v][0]=u;
				mn[v][0]=w;
				dfs(v);
				sub[u] += sub[v];
			}
		}
		tout[u]=++timer;
	}
	void compute() {
		dis[root]=0;
		dfs(root);
		for(int i = 0; i < m-1; i++) {
			for(int u = 0; u < n; u++) {
				int v1=table[u][i];
				if(v1!=-1) {
					int v2=table[v1][i];
					if(v2!=-1) {
						table[u][i+1]=v2;
						mn[u][i+1]=max(mn[u][i],mn[v1][i]);
					}
				}
			}
		}
	}
	int is_ancestor(int u, int v) {return tin[u] <= tin[v] && tout[u] >= tout[v];}
	AncestorK(vector<vii>& __g, int __n, int __root=0) {
		g=__g, root=__root,n=__n,m=(int)log2(n)+1,depth=0,timer=0;
		dis.assign(n,-1); parent.assign(n,-1); tin.assign(n,0); tout.assign(n,0); sub.assign(n,1);
		for(int i = 0; i < n; i++) {
			vector<int> tp(m,-1);
			table.pb(tp);
			tp.assign(m,0);
			mn.pb(tp);
		}
		compute();
	}
	int kth_ancestor(int u, int k) {
		if(dis[u] < k) return -1;
		if(k==0) return u;
		int c=u;
		for(int bit=0; bit<m; ++bit) {
			if(c==-1) return -1;
			if((k&(1ll<<bit)))
				c=table[c][bit];
		}
		return c;
	}
	int kth_max(int u, int k) {
		if(dis[u] < k) return -inf;
		if(k==0) return 0;
		int c=-inf,node=u;
		for(int bit=0; bit<m; ++bit) {
			if(node==-1) return -inf;
			if((k&(1ll<<bit))) {
				c=max(c,mn[node][bit]);
				node=table[node][bit];
			}
		}
		return c;
	}
	int lca(int u, int v) {
		if (is_ancestor(u, v))
	        return u;
	    if (is_ancestor(v, u))
	        return v;
	    for (int i = m-1; i >= 0; --i) {
	    	if(table[u][i]==-1) continue;
	        if (!is_ancestor(table[u][i], v))
	            u = table[u][i];
	    }
	    // u is then node just above LCA in u's path to LCA(u,v);
	    return table[u][0];
	}
};
