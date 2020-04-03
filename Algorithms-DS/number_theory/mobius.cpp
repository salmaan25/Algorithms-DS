#define MX 122000
int mu[MX+5], isprime[MX+5];

void preprocess() {
    for(int i=1; i<=MX; i++) {
        mu[i]=1;
        isprime[i]=1;
    }
    isprime[1]=0;
    for(int i=2; i<=MX; i++) {
        if(isprime[i]==1) {
            mu[i]=-mu[i];
            for(int j=2; i*j<=MX; j++) {
                isprime[i*j]=0;
                if(j%i==0) mu[i*j]=0;
                else mu[i*j]=-mu[i*j];
            }   
        }   
    }
}