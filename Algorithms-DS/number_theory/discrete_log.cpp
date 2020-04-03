//Finds smallest x such that a^x mod m = b mod m, returns -1 if there is no such x
//Complexity: O(sqrtM * logM)
/*this part is before using namespace std*/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
/*this part is before using namespace std*/

//for b=1 returned value is 0 so make sure that this 
// is valid in the given problem
int pow(int a, int b, int m)
{
	int ans=1;
	while(b)
	{
		if(b&1)
			ans=(ans*a)%m;
		b/=2;
		a=(a*a)%m;
	}
	return ans;
}

int discreteLog(int a, int b, int m)
{
	a %= m, b %= m;
	if(b == 1)
		return 0;
	int cnt = 0;
	int t = 1;
	for(int curg=__gcd(a, m);curg!=1;curg=__gcd(a, m))
	{
		if(b % curg)
			return -1;
		b /= curg, m /= curg, t = (t * a / curg) % m;
		cnt++;
		if(b == t)
			return cnt;
	}

	gp_hash_table<int, int> hash;
	int mid = ((int)sqrt(1.0 * m) + 1);
	int base = b;
	for(int i=0;i<mid;i++)
	{
		hash[base] = i;
		base = base * a % m;
	}

	base = pow(a, mid, m);
	int cur = t;
	for(int i=1;i<=mid+1;i++)
	{
		cur = cur * base % m;
		auto it = hash.find(cur);
		if(it != hash.end())
			return i * mid - it->second + cnt;
	}
}