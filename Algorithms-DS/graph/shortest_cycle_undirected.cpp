// Length of the shortest cycle containing s (the source), here A (or ss) is the number of vertices and g is the graph.
// DOES NOT WORK FOR DIRECTED GRAPH.
// n is number of nodes

int shortest_cycle(int s, int n) {
	if (g[s].empty()) {
		return inf;
	}
	int A=n;
	vector<bool> seen(A, false);
	vector<int> dist(A, inf);
	queue<int> q;
	q.push(s);
	seen[s] = true;
	dist[s] = 0;
	int ans = inf;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto& v : g[u]) {
			if (dist[u] + 1 < dist[v]) {
				dist[v] = dist[u] + 1;
				q.push(v);
			} else if (dist[v] >= dist[u]) {
				ans = min(ans, 1 + dist[u] + dist[v]);
			}
		}
	}
	return ans;
}