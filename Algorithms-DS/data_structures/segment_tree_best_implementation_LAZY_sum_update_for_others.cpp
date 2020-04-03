int MX = 200100;
int t[800010], lu[800010];
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void update(int v, int tl, int tr, int l, int r, int add) {
    if(lu[v] != 0) {
    	t[v] += (tr-tl+1)*lu[v];
    	if(tr != tl) {
	    	lu[2*v] += lu[v];
	    	lu[2*v+1] += lu[v];
		}
    	lu[v] = 0;
	}
	if (l > r)
        return;
    if (l == tl && r == tr) {
        t[v] += (tr-tl+1)*(add);
        if(tl != tr) {
        	lu[2*v] += (lu[v]+add);
	    	lu[2*v+1] += (lu[v]+add);
	    }
    	lu[v] = 0;
    } else {
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), add);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        t[v] = t[2*v+1]+t[2*v];
    }
}

int sum(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v]+(tr-tl+1)*lu[v];
    }
    if(lu[v] != 0) {
    	if(tl != tr) {
	    	lu[2*v] += lu[v];
	    	lu[2*v+1] += lu[v];
	    }
    	lu[v] = 0;
	}
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}