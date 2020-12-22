//WORKS FOR DISCONNECTED GRAPHS AS WELL
//THIS ADJACENCY LIST CONTAINS DUPLICATES. TO REMOVE SUPLICATES USE SET
// BUT THIS IS SUFFICIENT FOR COUNTING COMPONENTS WITH 0 INDEGREE.

class tarjanscc {
private:
	int n, m, sz, tm; //sz->number of SCCs or number of vertices in the DAG, n->vertex count, m->edge count, tm->time
	vector<vi> adjlist; // adjacency list of the original graph
	vector<vi> adjlist1; //graph after reverting the direction of edges
	vector<vi> comp; //comp[i] stores the list of vertices in ith strongly connected component here i also means vertex i in the DAG
	vi vis; vi fv; vi lv; //fv->first value, lv->last value
	void dfs(int u) {
		fv[u]=tm;
		tm+=1;
		vis[u]=1;
		for(int i = 0; i < adjlist[u].size(); i++) {
			int v = adjlist[u][i];
			if(!vis[v])
				dfs(v);
		}
		lv[u]=tm;
		tm+=1;
	}
	void dfs1(int u) {
		comp[sz].pb(u);
		vis[u]=1;
		for(int i = 0; i < adjlist1[u].size(); i++) {
			int v = adjlist1[u][i];
			if(!vis[v]) {
				dfs1(v);
			}
		}
	}
public:
	tarjanscc (int vct, int ect, vector<vi>& adjlistt) {
		n=vct; m=ect; sz=0; tm=0;
		adjlist.resize(n); adjlist1.resize(n); comp.resize(n); 
		vis.resize(n, 0); fv.resize(n, 0); lv.resize(n, 0);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < adjlistt[i].size(); j++) {
				adjlist[i].pb(adjlistt[i][j]);
				adjlist1[adjlistt[i][j]].pb(i);
			}
		}
	}
	void findscc() {
		for(int i = 0; i < n; i++) {
			if(!vis[i])
				dfs(i);
		}
		fill(vis.begin(), vis.begin()+n, 0);
		priority_queue<ii> pq;
		for(int i = 0; i < n; i++)
			pq.push({lv[i], i});
		while(!pq.empty()) {
			ii u = pq.top(); pq.pop();
			if(!vis[u.ss]) {
				dfs1(u.ss);
				sz++;
			}
		}
	}
	int getSizeOfSCC() { return sz; }
	int getcomp(vector<vi>& comp1) {
		for(int i = 0; i < sz; i++) {
			for(int j = 0; j < comp[i].size(); j++) {
				comp1[i].pb(comp[i][j]);
			}
		}
		return sz;
	}
	int getdag(vector<vi>& adjlist1) {
		vi cat(n, 0);
		for(int i = 0; i < sz; i++) {
			for(int j = 0; j < comp[i].size(); j++) {
				cat[comp[i][j]]=i;
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < adjlist[i].size(); j++) {
				int v = adjlist[i][j];
				if(cat[i] != cat[v])
					adjlist1[cat[i]].pb(cat[v]);
			}
		}
		//THIS ADJACENCY LIST CONTAINS DUPLICATES. TO REMOVE SUPLICATES USE SET
		// BUT THIS IS SUFFICIENT FOR COUNTING COMPONENTS WITH 0 INDEGREE.
		return sz;
	}
};