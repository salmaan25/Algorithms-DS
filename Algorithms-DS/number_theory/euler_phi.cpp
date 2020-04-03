#define MX 122000
int phi[MX+5], isprime[MX+5];
void prec() {
    phi[1]=1;
    for(int i=2 ; i<=MX; i++) {
        phi[i]=i;
        isprime[i]=1;
    }
    for(int i=2 ; i<=MX; i++) {
        if(isprime[i]==1) {
            phi[i]-=phi[i]/i;
            for(int j=2 ; i*j<=MX ; j++) {
                isprime[i*j]=0;
                phi[i*j]-=phi[i*j]/i;
            }
        }
    }
}