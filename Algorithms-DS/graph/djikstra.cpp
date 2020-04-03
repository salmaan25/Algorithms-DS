//INITIALIZE d VECTOR TO INF st IS THE STARTING VERTEX FROM WHERE WE HAVE TO FIND DISTANCE

void dj(vector<vii>& adj, vi& d, int st) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > p;
	p.push({0,st});
	d[st]=0;
	while(!p.empty()) {
		ii pr = p.top(); p.pop();
		int u = pr.ss; int c = pr.ff;
		if(d[u] < c) continue;
		// cout<<u<<" fr "<<c<<endl;
		for(int i = 0; i < adj[u].size(); i++) {
			ii v = adj[u][i];
			if(d[u]+v.ss < d[v.ff]) {
				d[v.ff] = d[u]+v.ss;
				p.push({d[v.ff], v.ff});
			}
		}
	}
}

//TO PRINT THE ADJACENCY LIST
void printadj(vector<vi>& adj, int n) {
	for(int i = 0; i < n; i++) {
		cout<<i<<"-> ";
		for(int j = 0; j < adj[i].size(); j++)
			cout<<"{"<<adj[i][j].ff<<","<<adj[i][j].ss<<"}-> ";
		cout<<endl;
	}
}

//NOTE: TO FIND DISTANCE FROM EACH POINT TO DST (DESTINATION) REVERSE THE ADJACENCY LIST I.E IF THERE'S A VERTEX
// FROM U TO V, IN THE NEW ADJACENCY LIST THE EDGE WILL BE FROM V TO U. NOW CALL DJIKSTRA ON THIS
// Use the BELOW CODE FOR THIS

void reverse(vector<vii>& adj, int n, vector<vii>& adj1) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < adj[i].size(); j++)
			adj1[adj[i][j].ff].pb({i,adj[i][j].ss});
	}
}