// src denotes the starting vertex (source);
// d[i] stores the distance of i from src. Initialize it to inf initially.
// seen[i] is 1 vertex is visited previously.
// If finally d[i]==inf then i is unreachable from src.

void bfs(vector<vii>& g, int src, vector<vi>& d) {
	deque<int> dq;
	dq.push_front(src);
	seen[src]=1;
	while(!dq.empty()) {
		int u = dq.front(); dq.pop_front();
		for(ii p: g[u]) {
			int v=p.ff,c=p.ss;
			if(!seen[v]) {
				seen[v]=1;
				if(c) {
					d[v]=d[u]+1;
					pq.push_back(v);
				} else {
					d[v]=d[u];
					pq.push_front(v);
				}
			}
		}
	}
}