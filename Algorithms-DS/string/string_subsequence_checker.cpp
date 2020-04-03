//PASS THE STRINGS BY REFERENCE ELSE IF THE STRING IS LONG O(n) COPYING WILL TAKE A LOT OF TIME

bool check(string s3, string s2) {
	ll i1 = 0; ll i2 = 0;
	while(1) {
		if(i2 >= (ll)s2.length())
			return true;
		if(i1 >= (ll)s3.length())
			return false;
		if(s3[i1] == s2[i2]) {
			i1++;
			i2++;
		}
		else {
			i1++;
		}
	}
}