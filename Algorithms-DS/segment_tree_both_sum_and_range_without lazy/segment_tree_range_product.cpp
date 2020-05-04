class SegmentTree {
private:
	int n; vii st; vi lz; vi a;
	void merge(int node) {
		st[node].ss=st[2*node].ss*st[2*node+1].ss;
		st[node].ss%=MOD;
	}
	void build(int node, int lo, int hi) {
		if(lo==hi) {
			st[node]={lo,a[lo]};
			return;
		}
		build(2*node,lo,(lo+hi)/2);
		build(2*node+1,(lo+hi)/2+1,hi);
		merge(node);
	}
	void propagate(int node, int l, int r) {
		if(l!=r) {
			lz[2*node] += lz[node];
			lz[2*node] %=MOD;
			lz[2*node+1] += lz[node];
			lz[2*node+1]%=MOD;
		}
		st[node].ss += (r-l+1)*(lz[node]);
		st[node].ss%=MOD;
		lz[node]=0;
	}
	void update(int node, int l, int r, int lo, int hi, int val) {
		if(lz[node]!=0)
			propagate(node,l,r);
		if(hi < l || lo > r)
			return;
		if(hi >= r && lo <= l) {
			lz[node]+=val;
			lz[node]%=MOD;
			propagate(node,l,r);
			return;
		}
		update(2*node,l,(l+r)/2,lo,hi,val);
		update(2*node+1,(l+r)/2+1,r,lo,hi,val);
		merge(node);
	}
	ii rmq(int node, int l, int r, int lo, int hi) {
		// cout<<l<<" "<<r<<" "<<lo<<" "<<hi<<endl;
		if(lz[node]!=0)
			propagate(node,l,r);
		if(hi < l || lo > r)
			return {-1, 1};
		if(hi >= r && lo <= l)
			return st[node];
		ii d1 = rmq(2*node, l, (l+r)/2, lo, hi);
		ii d2 = rmq(2*node+1, (l+r)/2+1, r, lo, hi);
		return {-1, (d1.ss*d2.ss)%MOD};
	}
public:
	SegmentTree(vi& __a) {
		n = __a.size();
		a=__a;
		st.assign(4*n,{0,0});
		lz.assign(4*n,0);
		build(1,0,n-1);
	}
	void Update(int l, int r, int val) {return update(1,0,n-1,l,r,val);}
	ii RMQ(int l, int r) {return rmq(1,0,n-1,l,r);}
};