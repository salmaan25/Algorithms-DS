// Length of the shortest cycle containing s (the source), here n is the number of vertices and g is the graph.
// DOES NOT WORK FOR UNDIRECTED GRAPH.

int shortest_cycle(int s, int n) {
	queue<int> q;
	q.push(s);
	vi dist(n,inf);
	dist[s]=0;
	int ans = inf;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto& v : g[u]) {
			if(v==s) {
				ans=min(ans,dist[u]+1);
			}
			if(dist[v]==inf) {
				dist[v]=dist[u]+1;
				q.push(v);
			}
		}
	}
	return ans;
}