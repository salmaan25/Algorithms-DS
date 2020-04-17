int ncr[110][110];
int C(int l,int k, int md) 
{
    if (k>l||l<0||k<0){
        return 0;
    }
    return ncr[l][k];
}
int solve(int l1, int p1) {
	if(l1==0 && p1==0) return 1;
	if(p1==0) return 0;
	if(l1<p1) return 0;
	return ncr[l1-1][p1-1];
}