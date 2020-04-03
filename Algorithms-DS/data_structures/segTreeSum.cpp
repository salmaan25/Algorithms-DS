#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SegTreeSum {
private:
	vi st, A;
	int n;
	int left(int p) {return p << 1;}
	int right(int p) {return (p << 1) + 1;}
	void build(int p, int L, int R) {
		if(L == R)
			st[p] = A[L];
		else {
			build(left(p), L, (L+R) / 2);
			build(right(p), ((L+R) / 2) + 1, R);
			st[p] = st[left(p)] + st[right(p)];
		}
	}
	int rs(int p, int L, int R, int i, int j) {
		if (j < L || i > R)
			return -1;
		if (L >= i && R <= j)
			return st[p];
		else {
			int s1 = rs(left(p), L, (L+R) / 2, i, j);
			int s2 = rs(right(p), (L+R) / 2 + 1, R, i, j);
			if (s1 == -1)
				return s2;
			if (s2 == -1)
				return s1;
			else
				return (s1 + s2);			
		}
	}
	void update(int p, int L, int R, int i, int j) {
		st[p] = st[left(p)] + st[right(p)];
	}
	void divide(int p, int L, int R, int i, int j, int val) {
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
		A = _A; n = (int)A.size();                                    // copy content for local usage
		st.assign(4 * n, 0);                                          // create large enough vector of zeroes
		build(1, 0, n - 1);
	}
	int rs(int i, int j) { 
		for(int k = 0; k < 13; k++)
			printf("%d ", st[k]);
		printf("\n");
		return rs(1, 0, n - 1, i, j); 
	}
	int rangeUpdate(int L, int R, int val) {
		divide(1, 0, n - 1, L, R, val);
	}
};

int main(void) {
	int arr[] = { 18, 17, 13, 19, 15, 11, 20 };                           // the original array
	vi A(arr, arr + 7);
	SegTreeSum st(A);                                                   //it means the name of the variable of data type SegTreeSum is st and A is passed to it as there is also a function with name SegTreeSum.hese  
	//vi lazyArray;
	//lazyArray.assign((int)A.size(), 0);
	printf("RMQ(1, 3) = %d\n", st.rs(1, 3));                             // answer = index 2
	printf("RMQ(4, 6) = %d\n", st.rs(4, 6)); 
	printf("RS(5, 5) = %d\n", st.rs(5, 5));                            // answer = index 5
	st.rangeUpdate(1, 3, 5);
	for(int i = 3; i <= 5; i++) {
		A[i] = 1;
	}					
	printf("\n");						  // add 5 to entries from 1 to 
	printf("RS(1, 3) = %d\n", st.rs(1, 3));                             // answer = index 2
	printf("RS(4, 6) = %d\n", st.rs(4, 6));
	printf("RS(2, 2) = %d\n", st.rs(2, 2));
	for(vi::iterator it = A.begin(); it != A.end(); it++)
		printf("%d ", *it);
	return 0;
}



/*st in line 71 while defining a class of type SegTreeSum: it means the name of the variable of data type SegTreeSum is st and A is passed to it as there is also a function 
with name SegTreeSum. These functions are called constructors and they have the same name as the class. copy this to diary.
