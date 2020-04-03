// for better results hash with 2 different m eg m1=1e9+9 and m2=1e9+7 and store like a pair.
// eg let string s give hash h1,h2 with m1,m2 resp then it is identified by the pair {h1,h2}

// This helps because the probability of collision is n^2/(2*m) where n is the total number of strings that we store and m is the 
// number with which we take mod now if taking mod wrt m1,m2 separately will ecome equivalent to taking mod wrt m1*m2 which here 
// becomes approx 1e18 hence that chance of collision become a lot less. 

// Now p should be grater than the number of different characters that we can use so take p accordingly. 
int inv(int x, int p) {
	return powmod(x,p-2,p);
} 
long long compute_hash(string const& s, int p = 31, int m = 1e9+9) {
	long long hash_value = 0;
	long long p_pow = 1;
	for (char c : s) {
		hash_value = (hash_value + (c - 'a' + 1) * p_pow);
		p_pow = (p_pow * p);
		if(hash_value >= m) hash_value%=m;
		if(p_pow >= m) p_pow%=m;
	}
	return hash_value;
}

void prefixHash(string& s, vi& pre, vi& inverse, int p, int m) {
	int n=s.length();
	pre.assign(n,0);
	inverse.assign(n,0);
	int po=1;
	pre[0]=(s[0]-'a'+1);
	inverse[0]=1;
	for(int i = 1; i < n; i++) {
		po=(po*p);
		if(po>=m) po%=m;
		pre[i]=(pre[i-1]+((s[i]-'a'+1)*po));
		if(pre[i]>=m) pre[i]%=m;
		if(i==1) inverse[i]=powmod(po,m-2,m);
		else inverse[i]=inverse[i-1]*inverse[1];
		if(inverse[i]>=m) inverse[i]%=m;
	}
}

int hashSubstring(vi& pre, int lo, int hi, int p, int m, vi& inverse) {
	if(lo==0) return pre[hi];
	int p1=pre[hi]-pre[lo-1],p2=inverse[lo];;
	if(p1<0) p1+=m;
	int ret=p1*p2;
	if(ret >= m) ret%=m;
	return ret;
}

/*
If m1=2^31-1 and m2=2^61-1 then the chances of collision are very less but to multiple mod 2^61-1 is difficult (avoiding overflow)
So use the following multiplication function instean of * in compute_hash
Now collision is almost impossible.
To make powmod compatible with m2 we will need to replace * in powmod with mulmod down below. 
*/
constexpr uint64_t mod = (1ull<<61) - 1;
uint64_t modmul(uint64_t a, uint64_t b){
	uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	uint64_t ret = (l&mod) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod) + (ret>>61);
	ret = (ret & mod) + (ret>>61);
	return ret-1;
}