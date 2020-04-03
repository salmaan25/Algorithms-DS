// a is dividend
// b is divisor
int __ceil(int a, int b) {
	if(a%b==0) return a/b;
	if(a<0) return a/b;
	return a/b+1;
}
int __floor(int a, int b) {
	if(a%b==0) return a/b;
	if(a<0) return a/b-1;
	return a/b;
}