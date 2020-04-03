#include <stdio.h>

int main(void)
{
	int t;
	scanf("%d", &t);
	while(t > 0)
	{
	int n;
	scanf("%d", &n);
	long long int prmar[n];
	int i = 0;
	for(i = 0; i < n; i++)
		scanf("%lld", &prmar[i]);
	if(n == 1)
	{
		printf("2\n");
		printf("%lld 0 1\n",  1000000007 - prmar[0]);
	}
	else if(n == 2)
	{
		long long int p = prmar[0];
		long long int q = prmar[1];
		printf("4\n");
		long long int c;
		if(p > q)	
			c = (p - q);
		else
			c = q - p;
		c = c % 1000000007;
		c = c * c;
		c = c % 1000000007;
		long long int b = (p % 1000000007) + (q % 1000000007);
		b = b * 2;
		b = b % 1000000007;
		b = 1000000007 - b;
		printf("%lld 0 %lld 0 1\n", c, b);
	}
	else if(n == 3)
	{
		long long int p = prmar[0];
		long long int q = prmar[1];
		long long int r = prmar[2];
		long long int b = (4 * ((p + q + r) % 1000000007)) % 1000000007;
		b = 1000000007 - b;
		long long int c = ((6 * ((((p * p) % 1000000007) + ((q * q) % 1000000007) + ((r * r) % 1000000007)))) % 1000000007 + (4 * (((p * q) % 1000000007) + ((q * r) % 1000000007) + ((r * p) % 10000000071))) % 1000000007) % 1000000007; 
		long long int p2 = (p * p) % 1000000007, q2 = (q * q) % 1000000007, r2 = (r * r) % 1000000007;
		long long int lastpart = (10 * (((p * q) % 1000000007) * r) % 1000000007) % 1000000007;
		long long int firstpart = (((p2 * p) % 1000000007) + ((q2 * q) % 1000000007) + ((r2 * r) % 1000000007)) % 1000000007;
		long long int middlepart = (((p2 * ((r + q)  % 1000000007)) % 1000000007) + ((q2 * ((r + p)  % 1000000007)) % 1000000007) + ((r2 * ((p + q)  % 1000000007)) % 1000000007)) % 1000000007;
		long long int d = (firstpart - middlepart + lastpart) % 1000000007;
		if(d < 0)
			d = d * -1;
		d = (d * 4) % 1000000007;
		d = 1000000007 - d;
		long long int e = (((p * p) % 1000000007) + ((q * q) % 1000000007) + ((r * r) % 1000000007) - ((2 * (((p * q) % 1000000007) + ((q * r) % 1000000007) + ((r * p) % 1000000007)) % 1000000007) % 1000000007)) % 1000000007;
		e = (e * e) % 1000000007;
		printf("8\n");
		printf("%lld 0 %lld 0 %lld 0 %lld 0 1\n", e, d, c, b);
	}
	else 
		printf("0\n 0\n");
	t--;
	}
	return 0;
}