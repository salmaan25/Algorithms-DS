vi st(500000*4);
void build(vi& a, int p, int l, int r) {
	if(l == r)
		st[p] = a[l];
	else {
		build(a, 2*p, l, (l+r)/2);
		build(a, 2*p+1, (l+r)/2+1, r);
		st[p] = __gcd(st[2*p], st[2*p+1]);
	}
}
void update(int p, int l, int r, int ind, int val) {
	if(l > ind || r < ind)
		return;
	if(l==r)
		st[p]=val;
	else {
		update(2*p, l, (l+r)/2, ind, val);
		update(2*p+1, (l+r)/2+1, r, ind, val);
		st[p] = __gcd(st[2*p], st[2*p+1]);
	}
}

void query(int p, int l, int r, int lo, int hi, int x, int* ct) {
	if(l > hi || r < lo)
		return;
	if(*ct > 1)
		return;
	if(l == r) {
		if(st[p]%x!=0) {
			// cout<<p<<" in1 "<<st[p]<<" "<<l<<" "<<r<<" "<<lo<<" "<<hi<<endl; 
			*ct += 1;
		}
		return;
	}
	if(l >= lo && r <= hi) {
		if(st[p]%x!=0) {
			if(st[2*p]%x!=0 && st[2*p+1]%x!=0) {
				// cout<<p<<" in2 "<<st[p]<<" "<<l<<" "<<r<<" "<<lo<<" "<<hi<<endl;
				*ct += 2;
				return;
			} else if(st[2*p]%x!=0)
				query(2*p, l, (l+r)/2, lo, hi, x, ct);
			else
				query(2*p+1, (l+r)/2+1, r, lo, hi, x, ct);
		}
	} else {
		query(2*p, l, (l+r)/2, lo, hi, x, ct);
		query(2*p+1, (l+r)/2+1, r, lo, hi, x, ct);
	}
}