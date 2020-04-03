// JUST PASS G (ADJACENCY LIST)
// m = (int)log2(n)+1 AS MAX DEPTH CAN BE 2^m;
// tin and tout are in and out times used to know whther a is ancestor of b. a is ancestor of b
// iff tin(a)<=tin(b) and tout(a)>=tout(b);
// table is basically the sparse table
// dis stores the distance of some node u from the root.


struct AncestorK {
public:
	int n,m,depth,root,timer;
	vector< vector<int> > g; vector< vector<int> > table;
	vector<int> dis,parent,tin,tout,sub;
	void dfs(int u) {
		tin[u]=++timer;
		for(int v: g[u]) {
			if(dis[v]==-1) {
				dis[v]=dis[u]+1;
				depth=max(depth,dis[v]);
				parent[v]=u;
				table[v][0]=u;
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
					v1=table[v1][i];
					if(v1!=-1)
						table[u][i+1]=v1;
				}
			}
		}
	}
	int is_ancestor(int u, int v) {return tin[u] <= tin[v] && tout[u] >= tout[v];}
	AncestorK(vector<vi>& __g, int __root=0) {
		g=__g, root=__root,n=sz(g),m=(int)log2(n)+1,depth=0,timer=0;
		dis.assign(n,-1); parent.assign(n,-1); tin.assign(n,0); tout.assign(n,0); sub.assign(n,1);
		for(int i = 0; i < n; i++) {
			vector<int> tp(m,-1);
			table.pb(tp);
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