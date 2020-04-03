// #include <bits/stdc++.h>
// using namespace std;

#define MAXN 65536
#define MAXLG 17
char A[MAXN];
struct entry { 
	int nr[2], p;
} L[MAXN];
int P[MAXLG][MAXN], N, i, stp, cnt;

int cmp(struct entry a, struct entry b) {
	return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);
}

void make() {
	for(N = strlen(A), i = 0; i < N; i ++)
		P[0][i] = A[i] - 'a';
	for(stp = 1, cnt = 1; cnt >> 1 < N; stp++, cnt <<= 1) {
		for(i = 0; i < N; i ++) { 
			L[i].nr[0] = P[stp - 1][i];
			L[i].nr[1] = i + cnt < N ? P[stp - 1][i + cnt] : -1;
			L[i].p = i; 
		}
		sort(L, L + N, cmp);
		for(i = 0; i < N; i++) P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
 	}
}

int main(void)
{
	cin>>A;
	make();
 	//P[stp-1][i] gives the position of the suffix starting at position i, in the sorted suffix array in ascending order
 	// for(int i = 0; i < stp; i++) {
	 // 	for(int j = 0; j < N; j++)
	 // 		cout<<P[i][j]<<" ";
	 // 	cout<<endl;
 	// }
 
	return 0;
} 