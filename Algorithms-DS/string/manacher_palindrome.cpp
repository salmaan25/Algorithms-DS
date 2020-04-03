// d1[i] is for number of odd palindromes centered at i. To get longest odd palindrome centered at i  do 2*d1[i]-1. 
// d2[i] is number of even palindromes centered at i. Do 2*d2[i] to get the longest palindrome length centered at i;
// Center in case of even length is the point to the right.
// s: abccba
// d1: 1 1 1 1 1 1
// d2: 0 0 0 3 0 0



void manacher(vi& d1, vi& d2, int n, string& s) {
	for(int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
			k++;
		d1[i] = k--;
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	for(int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
			k++;
		d2[i] = k--;
		if (i + k > r) {
			l = i - k - 1;
			r = i + k ;
		}
	}
}