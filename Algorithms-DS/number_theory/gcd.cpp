long long Gcd( long long a, long long b )
{
	while( a != 0 && b != 0 ) {
		if( a > b ) {
			a %= b;
		} else {
			b %= a;
		}
	}
	return max( a, b );
}