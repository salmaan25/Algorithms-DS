#define IS_SQ(a, b) (a % b == 0 && a / b == b)
#define IS_CB(a, b) (a % b == 0 && (a / b) % b == 0 && (a / (b * b)) == b)

int root(const int x, int lo, int hi) {
	// trace("ROOT", x);
	while (lo < hi) {
		// trace(lo, hi);
		int mid = (lo + hi) / 2;
		if (IS_SQ(x, mid)) return mid;
		if (mid > x / mid) {
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	// trace(lo, hi);
	if (IS_SQ(x, lo)) return lo;
	if (IS_SQ(x, hi)) return hi;
	return 0;
}
 
int croot(const int x, int lo, int hi) {
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (IS_CB(x, mid)) return mid;
		if (mid * mid > x / mid) {
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	if (IS_CB(x, lo)) return lo;
	if (IS_CB(x, hi)) return hi;
	return 0;
}