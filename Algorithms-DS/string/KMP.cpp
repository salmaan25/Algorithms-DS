#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100010
char T[MAX_N], P[MAX_N]; // T = text, P = pattern
int b[MAX_N], n, m; // b = back table, n = length of T, m = length of P
bool flag = false;
void kmpPreprocess() { // call this before calling kmpSearch()
	int i = 0, j = -1; b[0] = -1; // starting values
	while (i < m) { // pre-process the pattern string P
		while (j >= 0 && P[i] != P[j]) j = b[j]; // different, reset j using b
		i++; j++; // if same, advance both pointers
		b[i] = j; // observe i = 8, 9, 10, 11, 12, 13 with j = 0, 1, 2, 3, 4, 5
	} 
} // in the example of P = "SEVENTY SEVEN" above

void kmpSearch() { // this is similar as kmpPreprocess(), but on string T
	int i = 0, j = 0; // starting values
	while (i < n) { // search through string T
		while (j >= 0 && T[i] != P[j]) j = b[j]; // different, reset j using b
		i++; j++; // if same, advance both pointers
		if (j == m) { // a match found when j == m
			//printf("P is found at index %d in T\n", i - j);
			flag = true;
			break;
			j = b[j]; // prepare j for the next possible match
		} 
	} 
}

int main(void) {
	char s[100010];
	scanf("%s", s);
	int ind = 0;
	for(int i = 0; i < strlen(s); i++) {
		// if(s[i] == 'A' || s[i] == 'B') {
			T[ind] = s[i];
			ind++;
		// }
	}
	n = strlen(s);
	cout<<n<<endl;
	m = 3;
	P[0] = 'f';
	P[1] = 'i';
	P[2] = 'x';
	// P[3] = 'A';
	kmpPreprocess();
	kmpSearch();
	for(int i = 0; i < 3; i++)
		cout<<b[i]<<" ";
	cout<<endl;
	// if(flag  == false) {
	// P[0] = 'B';
	// P[1] = 'A';
	// P[2] = 'A';
	// P[3] = 'B';
	// kmpPreprocess();
	// kmpSearch();
	// }
	if(flag == false)
		printf("NO\n");
	else 
		printf("YES\n");
	return 0;
}