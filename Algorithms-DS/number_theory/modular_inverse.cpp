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