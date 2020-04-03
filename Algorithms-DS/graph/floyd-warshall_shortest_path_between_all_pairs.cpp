// d is the adjoint matrix
// d[i][i]=0;
// d[i][j]=inf is there is "NO EDGE" between vertex i and j
// d[i][j]=wij where wij is the weight of the edge between vertex i and j.
// here n is the number of vertices.
signed main(void) { 
	for (int k = 0; k < n; ++k) {
	    for (int i = 0; i < n; ++i) {
	        for (int j = 0; j < n; ++j) {
	            if (d[i][k] < inf && d[k][j] < inf)
	                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
	        }
	    }
	}
}