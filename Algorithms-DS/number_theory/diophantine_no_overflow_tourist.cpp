//define mulmod
// not sure but most probably x < abs(c) and y < abs(c)

int extgcd(int a, int b, int& x, int& y) {
    if (a == 0) {
        x = 0; y = 1; return b;
    }
    int x1, y1;
    int d = extgcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
bool fsol(int a, int b, int c, int& x, int& y) {
	g = extgcd(a, b, x, y);
	if (c % g != 0) {
	  return false;
	}
	int dx = c / a;
	c -= dx * a;
	int dy = c / b;
	c -= dy * b;
	x = dx + mulmod(x, c / g, b);
	y = dy + mulmod(y, c / g, a);
	g = abs(g);
	return true;
}