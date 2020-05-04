// u denotes the starting vertex (source);
// d[i][j] stores the distance of {i,j} from source. Initialize it to inf initially.
// mat[i][j]=0 if that vertex is unreachable
// mat[i][j]!=0 if state is reachable
// seen[i][j] is 1 vertex is visited previously.
// dx[]={0,0,1,-1},dy[]={1,-1,0,0}
// If finally d[i][h]==inf then {i,j} is unreachable from source.

void bfs(ii u, vector<vi>& d) {
	d[u.ff][u.ss]=0;
	deque<ii> dq;
	dq.push_front(u);
	seen[u.ff][u.ss]=1;
	while(!dq.empty()) {
		ii u = dq.front(); dq.pop_front();
		for(int i = 0; i < 4; i++) {
			int xx=u.ff+dx[i],yy=u.ss+dy[i];
			if(xx >= 0 && xx < n && yy >= 0 && yy < m && mat[xx][yy] && !seen[xx][yy]) {
				if(mat[xx][yy]==1) {
					seen[xx][yy]=1;
					d[xx][yy]=d[u.ff][u.ss]+1;
					dq.push_back({xx,yy});
				} else {
					seen[xx][yy]=1;
					d[xx][yy]=d[u.ff][u.ss];
					dq.push_front({xx,yy});
				}
			}
		}
	}
}