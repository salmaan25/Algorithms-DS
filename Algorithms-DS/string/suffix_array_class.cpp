#define MAXN 65536 //ONLY CHANGE THIS ACCORDING TO PROBLEM
#define MAXLG 25

struct entry {
	int nr[2], p;
};

int cmp(struct entry a, struct entry b) {
	return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);
}

class suffixArray {
private:
	string A;
	entry L[MAXN];
	int P[MAXLG][MAXN], N, stp, cnt;
	vii sufar; //pos in the sorted order, starting index in the string
	//P[k][x] shows the position of the string in sorted order, starting at position k and of length x
public:
	suffixArray(string& s) {
		N = s.length();
		A = s;
		for(int i = 0; i < N; i++)
			P[0][i] = A[i] - 'a';
		for(stp = 1, cnt = 1; cnt >> 1 < N; stp++, cnt <<= 1) {
			for(int i = 0; i < N; i ++) { 
				L[i].nr[0] = P[stp - 1][i];
				L[i].nr[1] = i + cnt < N ? P[stp - 1][i + cnt] : -1;
				L[i].p = i; 
			}
			sort(L, L + N, cmp);
			for(int i = 0; i < N; i++) P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
		}
		sufar.assign(N, {0, 0});
		for(int i = 0; i < N; i++)
			sufar[i] = {P[stp-1][i], i};
		sort(sufar.begin(), sufar.end());
	}
	int lcp(int x, int y)
	{
		// x and y are the index of the starting character of the suffix in the string
		int k, ret = 0; 
		if (x == y) return N - x;
		for (k = stp - 1; k >= 0 && x < N && y < N; k--) {
			if (P[k][x] == P[k][y]) { x += 1 << k; y += 1 << k; ret += 1 << k; }
		}
		return ret;
		//return length of the longest comon prefix
	} 
	void print() {
		for(int i = 0; i < N; i++) {
			cout<<P[stp-1][i]<<"  = position of the suffix in the sorted suffix array, starting at position "<<i<<" in the original string "<<endl;
		}
	}
};

int main(void)
{
	// IOS;
	string s;
	s = "hello";
	cout<<s<<endl;
	suffixArray sf(s);
	sf.print();
	time();
	return 0;
}