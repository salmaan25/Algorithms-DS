#define MX 200000
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