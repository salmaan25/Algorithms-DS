//ax^2+bx+c where a!=0 and out contains the  solutions of the equationa nd the function returns number of real solutions.

int quadRoots(double a, double b, double c, pair<double,double> &out) {
	assert(a != 0);
	double disc = b*b - 4*a*c;
	if (disc < 0) return 0;
	double sum = (b >= 0) ? -b-sqrt(disc) : -b+sqrt(disc);
	out = {sum/(2*a), sum == 0 ? 0 : (2*c)/sum};
	return 1 + (disc > 0);
}