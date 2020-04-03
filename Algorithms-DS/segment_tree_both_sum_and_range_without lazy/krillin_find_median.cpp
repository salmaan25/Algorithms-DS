#include <bits/stdc++.h>
using namespace std;

typedef vector<long long int> vi;

long long int gcd(long long int a, long long int b)
{
    if (a == b)
        return a;
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}
 
long long int lcm(long long int a, long long int b)
{
    return (a*b)/gcd(a, b);
}
class SegmentTree {                                                        // the segment tree is stored like a heap array
	private: vi st, A;                                                     // recall that vi is: typedef vector<long long int> vi;
	long long int n;
	long long int left (long long int p) { return p << 1; } 								   // same as binary heap operations
	long long int right(long long int p) { return (p << 1) + 1; }
	void build(long long int p, long long int L, long long int R) { 									   // O(n)
		if (L == R)                                                        // as L == R, either one is fine
		st[p] = L;                                                         // store the index
		else {                                                             // recursively compute the values
			build(left(p) , L , (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R );
			long long int p1 = st[left(p)], p2 = st[right(p)];
			st[p] = (A[p1] >= A[p2]) ? p1 : p2;
	} }
	long long int rmq(long long int p, long long int L, long long int R, long long int i, long long int j) {                          // O(log n)
		if (i > R || j < L) return -1;                                    // current segment outside query range i.e completely to the right or left resp.
		if (L >= i && R <= j) return st[p];                               // inside query range
		                                                                  // compute the min position in the left and right part of the long long interval
		long long int p1 = rmq(left(p) , L , (L+R) / 2, i, j);
		long long int p2 = rmq(right(p), (L+R) / 2 + 1, R , i, j);
		if (p1 == -1) return p2;                                          // if we try to access segment outside query
		if (p2 == -1) return p1;                                          // same as above
		return (A[p1] >= A[p2]) ? p1 : p2;                                // as in build routine
	}
	void update(long long int p, long long int L, long long int R, long long int i, long long int j) {
		if (A[st[left(p)]] >= A[st[right(p)]])
			st[p] = st[left(p)];
		else
			st[p] = st[right(p)];
	}
	void divide(long long int p, long long int L, long long int R, long long int i, long long int j, long long int val){
		if (i > R || j < L) return;
		else if(L != R) {
			divide(left(p), L, (L+R) / 2, i, j, val);
			divide(right(p), (L+R) / 2 + 1, R, i, j, val);
			update(p , L, R, i, j);
		}
		else if(L == R) {
			A[st[p]] = val;
		}
	}
	public:
		SegmentTree(const vi &_A) {
			A = _A; n = (long long int)A.size();                                    // copy content for local usage
			st.assign(4 * n, 0);                                          // create large enough vector of zeroes
			build(1, 0, n - 1);                                           // recursive build
		}
		long long int rmq(long long int i, long long int j) { return rmq(1, 0, n - 1, i, j); }          // overloading
		long long int rangeUpdate(long long int L, long long int R, long long int val) { 
			divide(1, 0, n - 1, L, R, val); 
		}
};

class SegTreeSum {
private:
	vi st, A;
	long long int n;
	long long int left(long long int p) {return p << 1;}
	long long int right(long long int p) {return (p << 1) + 1;}
	void build(long long int p, long long int L, long long int R) {
		if(L == R)
			st[p] = A[L];
		else {
			build(left(p), L, (L+R) / 2);
			build(right(p), ((L+R) / 2) + 1, R);
			st[p] = st[left(p)] + st[right(p)];
		}
	}
	long long int rs(long long int p, long long int L, long long int R, long long int i, long long int j) {
		if (j < L || i > R)
			return -1;
		if (L >= i && R <= j)
			return st[p];
		else {
			long long int s1 = rs(left(p), L, (L+R) / 2, i, j);
			long long int s2 = rs(right(p), (L+R) / 2 + 1, R, i, j);
			if (s1 == -1)
				return s2;
			if (s2 == -1)
				return s1;
			else
				return (s1 + s2);			
		}
	}
	void update(long long int p, long long int L, long long int R, long long int i, long long int j) {
		st[p] = st[left(p)] + st[right(p)];
	}
	void divide(long long int p, long long int L, long long int R, long long int i, long long int j, long long int val) {
		if (i > R || j < L) return;
		else if(L != R) {
			divide(left(p), L, (L+R) / 2, i, j, val);
			divide(right(p), (L+R) / 2 + 1, R, i, j, val);
			update(p , L, R, i, j);
		}
		else if(L == R) {
			st[p] = val;
		}
	}
	void find_median(long long int p, long long int L, long long int R, long long int i, long long int j, long long int eltNo, pair<long long int, long long int>& sum ) {
		if(sum.second != -1) {
			return;
		}
		if (j < L || i > R) {
			return;
		}
		if(L == R) { 
			if(sum.first + st[p] >= eltNo) {
				sum.second = L;
				return;
			}
			else {
				sum.first += st[p];
				return;
			}
		}
		long long int mid = (L + R) / 2;	
		if (L >= i && R <= j) {
			if(sum.first + st[left(p)] >= eltNo) {
				find_median(left(p), L, mid, i, j, eltNo, sum);
			}
			else if(sum.first + st[left(p)] < eltNo) {
				sum.first += st[left(p)];
				find_median(right(p), mid + 1, R, i, j, eltNo, sum);
			}
		}
		else {
			find_median(left(p), L, (L+R) / 2, i, j, eltNo, sum);
			find_median(right(p), (L+R) / 2 + 1, R, i, j, eltNo, sum);
		}
	}
public:
	SegTreeSum(const vi &_A) {
		A = _A; n = (long long int)A.size();                                    // copy content for local usage
		st.assign(4 * n, 0);                                          // create large enough vector of zeroes
		build(1, 0, n - 1);
	}
	long long int rs(long long int i, long long int j) { 
		return rs(1, 0, n - 1, i, j); 
	}
	long long int rangeUpdate(long long int L, long long int R, long long int val) {
		divide(1, 0, n - 1, L, R, val);
	}
	void find_median(long long int i, long long int j, long long int eltNo, pair<long long int, long long int>& sum ) {
		find_median(1, 0, n - 1, i, j, eltNo, sum);
	}
};


int main(void) {
	long long int t;
	scanf("%lld", &t);
	for(long long int i = 0; i < t; i++) {
		long long int n, q;
		scanf("%lld%lld", &n, &q);
		long long int ar[n];
		for(long long int j = 0; j < n; j++) {
			scanf("%lld", &ar[j]);
		}
		vi A(ar, ar + n);
		SegmentTree modefinder(A);
		SegTreeSum medianfinder(A);
		for(long long int j = 0; j < q; j++) {
			long long int type, q1, q2;
			scanf("%lld%lld%lld", &type, &q1, &q2);
			if(type == 1) {
				long long int index_mode = modefinder.rmq(q1 - 1, q2 - 1);
				long long int sum = medianfinder.rs(q1 - 1, q2 - 1);
				long long int val = sum / 2;
				long long int median = 0; 
				pair<long long int , long long int> values;
				values.first = 0;  
				values.second = -1;
				if(sum % 2 == 1)
					medianfinder.find_median(q1 - 1, q2 - 1, val + 1, values);
				else
					medianfinder.find_median(q1 - 1, q2 - 1, val, values);
				printf("%lld\n", lcm(index_mode + 1, values.second + 1));
			}
			else {
				modefinder.rangeUpdate(q1 - 1, q1 - 1, q2);
				medianfinder.rangeUpdate(q1 - 1, q1 - 1, q2);
			}
		}
	}
}