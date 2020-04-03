#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;





class UnionFind {
	private:
		vi p, rank, setCount;
		int NumSets;
	public:
		UnionFind(int N) {
			NumSets = N;
			rank.assign(N, 0);
			setCount.assign(N, 1);
			p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; 
		}
		int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
		bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
		void unionSet(int i, int j) {
			if (!isSameSet(i, j)) {
				int x = findSet(i), y = findSet(j);
				NumSets--;
				if (rank[x] > rank[y]) {
					p[y] = x;
					setCount[x] += setCount[y]; }
				else { 
					p[x] = y;
					setCount[y] += setCount[x];
					if (rank[x] == rank[y]) rank[y]++; }
			} 
		}
		int SizeOfSet(int i) { return setCount[findSet(i)]; }
		int NumDisjointSets(){ return NumSets;} 
};

int main(void)
{
	UnionFind u(20);
	u.unionSet(0, 10);
	u.unionSet(3, 5);
	u.unionSet(7, 10);
	bool ans;
	ans = u.isSameSet(0, 7);
	if(ans == true)
		printf("1\n");
	else
		printf("0\n");
	printf("%d\n", u.SizeOfSet(10));
	printf("%d\n", u.NumDisjointSets());
	return 0;
}