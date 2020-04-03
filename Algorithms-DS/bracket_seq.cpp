
// ith index of dp gives longest perfect bracket sequence ending at i

// is_perfect() returns one if the subarray s[l..r] is a perfect bracket sequence else it returns 0. Run this after solve()

/*-------------NOTE-----------*/
// is_perfect() can be used to calculate number of right circular shifts which result in a perfect bracket sequence. Just concatenate
// s to itself and call solve() on this now for each r in (0,2*n-1) call is_perfect(r-n+1,r,dp,s)
/*-------------NOTE-----------*/
int is_perfect(int l, int r, vi& dp, string& s) {
	int n=s.length();
	if(dp[r]==r-l+1)
		return 1;
	else if(dp[r] > r-l+1) {
		int i1=l-1;
		if(dp[i1]+(r-l+1)==dp[r])
			return 1;
	}
	return 0;
} 
int solve(string& s, vi& dp) {
	int n=s.length();
	dp.clear(); dp.assign(n,0);
	for(int i = 1; i < n; i++) {
		if(s[i]=='(') continue;
		if(s[i-1]=='(') {
			int i1=i-2;
			int ln=2;
			if(i1>=0)
				ln += dp[i1];
			dp[i]=max(dp[i],ln);
		}
		if(dp[i-1]!=0) {
			int i1=i-1-dp[i-1];
			int ln=0;
			if(i1 >= 0 && s[i1]=='(') { 
				ln += dp[i-1]+2;
				if(i1-1>=0)
					ln += dp[i1-1];
			}
			dp[i]=max(dp[i],ln);
		}
	}
}