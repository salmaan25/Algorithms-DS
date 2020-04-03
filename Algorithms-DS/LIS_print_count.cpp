#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll findPOS(ll start, ll end, ll index, vi& LIS, vi& v) {
	ll mid = (start+end)/2;
	if(start==end) {
		return start;
	}
	else {
		if(v[LIS[mid]] < v[index]) {
			return findPOS(mid+1, end, index, LIS, v);
		}
		else{
			return findPOS(start, mid, index, LIS, v);
		}
	}
}

void findLIS(vi& v, vi& parent, vi& LIS) { //GETS INDICES OF THE LIS. TO MAKE IT INTO LONGEST NONDECREASING SUBSEQ CHANGE 27 TO <=
	ll len = (ll)v.size();
	LIS.push_back(0);
	parent[0] = 0;
	for(ll i = 1; i < len; i++) {
		if(v[LIS[(ll)LIS.size()-1]] < v[i]) {
			parent[i] = LIS[(ll)LIS.size()-1];
			LIS.push_back(i);
		}
		else if(v[LIS[(ll)LIS.size()-1]] >= v[i]) { //CAN REPLACE LAST ELEMENT AS WELL
			ll ind = findPOS(0, (ll)LIS.size()-1, i, LIS, v);
			if(ind == 0) {
				parent[i] = i;
				LIS[ind] = i;
			}
			else {
				parent[i] = LIS[ind-1];
				LIS[ind] = i;
			}
		}
	}
	if((ll)LIS.size() == 1)
		LIS[0] = (ll)v.size()-1;
}

//REVERSE OF THE ANSWER IS GIVEN. REVERSE IT TO GET THE CORRECT ORDER.
int main(void) {
	vi v;
	while(1) {
		ll tmp;
		int breaker = scanf("%lld", &tmp);
		if (breaker!=1)
			break;
		v.push_back(tmp);
	}
	if((ll)v.size() == 0)
		printf("0\n-\n");
	else {
		vi parent((ll)v.size());
		vi LIS;
		findLIS(v, parent, LIS);
		printf("%lld\n-\n", (ll)LIS.size());
		vi revans;
		ll i = LIS[(ll)LIS.size()-1];
		while(1) {
			if(parent[i] == i) {
				revans.push_back(v[i]);
				break;
			}
			else {
				revans.push_back(v[i]);
				i = parent[i];
			}
		}
		for(ll j = (ll)LIS.size()-1; j >= 0; j--) {
			printf("%lld\n", revans[j]);
		}
	}	
	return 0;
}