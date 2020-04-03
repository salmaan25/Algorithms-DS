mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//GIVES A RANDOM NUMBER BETWEEN [l,r] BOTH INCLUSIVE.
int getRand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

/*FOR SHUFFLE*/
shuffle(permutation.begin(), permutation.end(), rng);

/*FOR SWAP ON PERMUTATION ARRAY*/
// Gives a number between [0,i] both included
swap(permutation[i], permutation[uniform_int_distribution<int>(0, i)(rng)]);