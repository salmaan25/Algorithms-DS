#include <bits/stdc++.h>

#define MX 2000000
int u[MX+5];
int p[MX+5]; //p[] stores list of prime numbers u[i] stores the smallest prime factor of i
int pn; //strores number of prime numbers

void sieve() {
	//p[1]=2; p[0]=0;
	for(int i = 2; i <= MX; i++) {
		if(!u[i]) {
			u[i]=p[++pn]=i;
		}
		for(int j = 1; i*p[j] <= MX; j++) {
			u[i*p[j]]=p[j];
			if(i%p[j]==0)
				break;
		}
	}	
}

void findFactors(vi& pr, vi& pp, int id, int num, vi& factor) {
	if(id >= sz(pr)) {
		factor.pb(num);
		return;
	}
	int cur=1;
	for(int i = 0; i <= pp[id]; i++) {
		findFactors(pr, pp, id+1, num*cur, factor);
		cur *= pr[id];
	}
}

vi factorise(int x) {
	vi pr,pp;
	while(x>1) {
		int prime = u[x], po=0;
		while(x%prime==0) {
			po++;
			x /= prime;
		}
		pr.pb(prime);
		pp.pb(po);
	}
	vi factor;
	findFactors(pr,pp,0,1,factor);
	sort(all(factor));
	return factor;
}

int main(void) {
	sieve();

	// EXAMPLE
	vi factors = factorise(24);
	for(int i: factors)
		cout<<i<<" ";
	cout<<endl;
}