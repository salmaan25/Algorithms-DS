// x0 = ans[0], x1 = ans[1],....,x(n-1) = ans[n-1]
//last column of a is the value of b where a general equation is
// a0*x0+a1*x1+....+a(n-1)*x(n-1) = b and so on.

int bpow(int a,int l) {// md is the prime with which remainder has to be calculated mostly 1e9+7
    int res=1;
    while (l){
        if (l&1){
            res=res*a%MOD;
        }
        l/=2;
        a=a*a%MOD;
    }
    return res;
}

int extended_euclidean(int a, int b, int& x, int& y) {
    if (a == 0) {
        x = 0; y = 1; return b;
    }
    int x1, y1;
    int d = extended_euclidean(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
int inverse(int a) {
	int x, y;
	int g = extended_euclidean(a, MOD, x, y);
	if (g != 1)
		return -1;
	return (x % MOD + MOD) % MOD;
}
int gauss (vector < vector<int> >& a, vector<int> & ans) {
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (!a[sel][col])
            continue;
        int pivot = a[sel][col];
        int ipivot = inverse(pivot);
        for (int i=col; i<=m; ++i) {
            swap (a[sel][i], a[row][i]);
            a[row][i] = (a[row][i]*ipivot)%MOD;
        }
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                int c = a[i][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] = (a[i][j]-((a[row][j]*c)%MOD)+MOD)%MOD;
            }
        ++row;
    }
    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m];
    for (int i=0; i<n; ++i) {
        int sum = 0;
        for (int j=0; j<m; ++j)
            sum = (sum+(ans[j]*a[i][j])%MOD+MOD)%MOD;
        if (sum != a[i][m])
            return 0;
    }
    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}