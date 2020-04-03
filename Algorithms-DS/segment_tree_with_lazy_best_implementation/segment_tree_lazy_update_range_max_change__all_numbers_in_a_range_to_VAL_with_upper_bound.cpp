// IN THIS CODE, IN UPDATE ALL THE VALUES IN THE RANGE (L,R) ARE SET TO X (NOT INCREASED).
// lower_bound returns leftmost element greater than or equal to x
// WHILE IMPLEMENTING YOUR OWN lower_bound remember to propagate 2*node and 2*node+1 before using them. see code.

class SegmentTreeMax {
private:
	int n; vii st; vi lz; vi a; //In st ss contains value and ff contains the index of the value
	void merge(int node) {
		if(st[2*node].ss >= st[2*node+1].ss)
			st[node]=st[2*node];
		else
			st[node]=st[2*node+1];
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
			lz[2*node] = lz[node];
			lz[2*node+1] = lz[node];
		}
		st[node].ss = lz[node];
		lz[node]=inf;
	}
	void update(int node, int l, int r, int lo, int hi, int val) {
		if(lz[node]!=inf)
			propagate(node,l,r);
		if(hi < l || lo > r)
			return;
		if(hi >= r && lo <= l) {
			lz[node]=val;
			propagate(node,l,r);
			return;
		}
		update(2*node,l,(l+r)/2,lo,hi,val);
		update(2*node+1,(l+r)/2+1,r,lo,hi,val);
		merge(node);
	}
	ii rmq(int node, int l, int r, int lo, int hi) { //ss contains value and ff contains the index of the value
		if(lz[node]!=inf)
			propagate(node,l,r);
		if(hi < l || lo > r)
			return {-1, -inf};
		if(hi >= r && lo <= l)
			return st[node];
		ii d1 = rmq(2*node, l, (l+r)/2, lo, hi);
		ii d2 = rmq(2*node+1, (l+r)/2+1, r, lo, hi);
		if(d1.ss >= d2.ss)
			return d1;
		return d2;
	}
	int lower_bound(int node, int l, int r, int x) {
		if(lz[node]!=inf)
			propagate(node,l,r);
		if(l==r) return st[node].ff;
		if(lz[2*node]!=inf) propagate(2*node,l,(l+r)/2);
		if(lz[2*node+1]!=inf) propagate(2*node+1,(l+r)/2+1,r);
		if(st[2*node].ss >= x)
			return lower_bound(2*node,l,(l+r)/2,x);
		else
			return lower_bound(2*node+1,(l+r)/2+1,r,x);
	}
public:
	SegmentTreeMax(vi& __a) {
		n = __a.size();
		a=__a;
		st.assign(4*n,{0,0});
		lz.assign(4*n,inf);
		build(1,0,n-1);
	}
	void Update(int l, int r, int val) {return update(1,0,n-1,l,r,val);}
	ii RMQ(int l, int r) {return rmq(1,0,n-1,l,r);}
	int lowerbound(int x) {return lower_bound(1,0,n-1,x);}
};