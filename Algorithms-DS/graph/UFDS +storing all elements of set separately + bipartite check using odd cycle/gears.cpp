//UFDS +storing all elements of a connected component separately + bipartite check using odd cycle

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int color[100005];
bool isBlocked[100005];

class UnionFind {                                                                             // OOP style
	private: 
		vi p, rank, setCount;
		int NumSets;                                                            // remember: vi is vector<int>
	public:																					  // setCount counts number of elements in a disjoint set
		UnionFind(int N) { 
			NumSets = N;
			rank.assign(N, 0);
			setCount.assign(N, 1);
			p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
		int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
		bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
		void unionSet(int i, int j) {
			if (!isSameSet(i, j)) {                                                           // if from different set
				int x = findSet(i), y = findSet(j);
				NumSets--;
				if (rank[x] > rank[y]) {
					p[y] = x;                                                                 // rank keeps the tree short
					setCount[x] += setCount[y]; }
				else { 
					p[x] = y;
					setCount[y] += setCount[x];
					if (rank[x] == rank[y]) rank[y]++; }
			} 
		}
		int SizeOfSet(int i) {
			return setCount[findSet(i)];
		}
		int NumDisjointSets(){
			return NumSets;
		}
		int rankret(int i) {
			return rank[findSet(i)];
		} 
};

void colorCheck(int node1, int node2, UnionFind& u, int n, vector<vi>& set) {
	if(isBlocked[u.findSet(node1)] == true || isBlocked[u.findSet(node2)] == true) {
		u.unionSet(node1, node2);
		isBlocked[u.findSet(node1)] = true;
	}
	else if(color[node1] == color[node2]) {
		if(u.isSameSet(node1, node2)){
			isBlocked[u.findSet(node1)] = true;
		}
		else {
 			int n1 = u.findSet(node1), n2 = u.findSet(node2);
 			if(u.rankret(n1) <= u.rankret(n2)) {
 				int tmp = n1;
				n1 = n2;
			 	n2 = tmp;
 			}
 			int len = (int)set[n2].size();
 			for(int i = 0; i < len; i++) {
				color[set[n2][0]] = 1-color[set[n2][0]];
				set[n1].push_back(set[n2][0]);
				set[n2].erase(set[n2].begin());
 			}
 			u.unionSet(node1, node2);
		}
	}
	else {
		if(!(u.isSameSet(node1, node2))) {
			int n1 = u.findSet(node1), n2 = u.findSet(node2);
 			if(u.rankret(node1) <= u.rankret(node2)) {
 				int tmp = n1;
				n1 = n2;
			 	n2 = tmp;
 			}
 			int len = (int)set[n2].size();
 			for(int i = 0; i < len; i++) {
				set[n1].push_back(set[n2][0]);
				set[n2].erase(set[n2].begin());
 			}
 			u.unionSet(node1, node2);
		}
	}
}
int main(void) {
	int m, n;
	scanf("%d%d", &n, &m);
	int teeth[n];
	vector<vi> set(n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &teeth[i]);
		isBlocked[i] = false;
		color[i] = 1;
		set[i].push_back(i);
	}
	int type = 0;
	UnionFind u(n);
	for(int i = 0; i < m; i++) {
		scanf("%d", &type);
		if(type == 1) {
			int l, m;
			scanf("%d%d", &l, &m);
			teeth[l - 1] = m;
		}
		else if(type == 2) {
			int l, m;
			scanf("%d%d", &l, &m);
			colorCheck(l - 1, m-1, u, n, set);
		}
		else {
			int l, m ,v;
			scanf("%d%d%d", &l, &m, &v);
			if(isBlocked[u.findSet(m-1)] == true){
				printf("0\n");
			}
			else {
				if(u.isSameSet(l-1, m-1)) {
					long long int num = (long long int)(teeth[l-1]) * (long long int)(v);
					long long int den = (long long int)teeth[m-1];
					long long int fac = __gcd(num, den);
					if(color[l-1] == color[m-1])
						printf("%lld/%lld\n", num/fac, den/fac);
					else
						printf("-%lld/%lld\n", num/fac, den/fac);
				}
				else
					printf("0\n");
			}
		}
	}
	return 0;
}