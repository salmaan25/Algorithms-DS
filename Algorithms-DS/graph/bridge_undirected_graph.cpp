// FOR UNDIRECTED GRAPH
// MAKE GLOBAL VIS, PARENT, DP EACH
// ROOT IS CONSIDERED AT THE TOP AND IT'S CHILDREN ARE BELOW IT
// VIS STORES WHETHER A NODE IS VISITED OR NOT
// PARENT STORES THE PARENT OF A NODE IN DFS TREE 
// DP[U] STORES THE NUMBER OF BACK EDGES GOING UP FROM SUBTREE OF U TO THE ANCESTORS OF U
// IF DP[U]==0 THEN THE EDGE BETWEEN U AND IT'S PARENT IS A BRIDGE.

void dfs(int u,int root=0) {
	seen[u]=1;
	int down=0,up=0,ch=0;
	for(int v: g[u]) {
		if(seen[v]==1 && v!=parent[u])
			down++;	
		if(!seen[v]) {
			parent[v]=u;
			dfs(v,root);
			ch++;
			dp[u]+=dp[v];
		}
	}
	up=sz(g[u])-down-ch-1;
	dp[u]=dp[u]-up+down;
	if(u==root) dp[u]=0; 
	seen[u]=2;
}