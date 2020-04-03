#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

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
			st[p] = (A[p1] <= A[p2]) ? p1 : p2;
	} }
	long long int rmq(long long int p, long long int L, long long int R, long long int i, long long int j) {                          // O(log n)
		if (i > R || j < L) return -1;                                    // current segment outside query range i.e completely to the right or left resp.
		if (L >= i && R <= j) return st[p];                               // inside query range
		                                                                  // compute the min position in the left and right part of the long long interval
		long long int p1 = rmq(left(p) , L , (L+R) / 2, i, j);
		long long int p2 = rmq(right(p), (L+R) / 2 + 1, R , i, j);
		if (p1 == -1) return p2;                                          // if we try to access segment outside query
		if (p2 == -1) return p1;                                          // same as above
		return (A[p1] <= A[p2]) ? p1 : p2;                                // as in build routine
	}
	void update(long long int p, long long int L, long long int R, long long int i, long long int j) {
		if (A[st[left(p)]] <= A[st[right(p)]])
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
};

void print( list<int> l){
    for(list<int>::iterator it=l.begin(); it!=l.end() ; ++it)
            cout << " " << *it;
    cout<<endl;
}
void subset(long long int size,long long int left,long long int index, list<long long int> &l){
    if(left==0){
        print(l);
        return;
    }
    for(long long int i=index; i<size;i++){
        l.push_back(i);
        subset(size,left-1,i+1,l);
        l.pop_back();
    }

}     

void FindGood(SegmentTree s1, SegTreeSum s2, long long int n) { //i is size of numbe rof elements to be removed
	for(long long int i = 1; i < n; i++) {
		vector<long long int> subsetIndices;
		//+for(long long int j = 0; j < i; j++)
		list<long long int> lt;
		subset(n, i, 0, lt);
		long long int prev = 0;
		long long int cur = 0;
		/*for(list<long long int>::iterator it = lt.begin(), it != lt.end(), it++) {
			if(it == it.begin()) {

			}
			else if(it == it.end()) {

			}
			else {

			}
		}*/

	}
}

int main(void) {
	int t;
	scanf("%d", &t);
	for(int i = 0; i < t; i++) {
		long long int n;
		scanf("%lld", &n);
		long long int a[n];
		long long int b[n];
		for(int j = 0; j < n; j++)
			scanf("%lld %lld", &a[j], &b[j]);
		vector<long long int> A(a, a + n);
		vector<long long int> B(b, b + n);
		SegmentTree st1(A);
		SegTreeSum st2(B);
		//vector<long long int> subsetIndices;
		FindGood(st1, st2, n);
	}
	return 0;
}