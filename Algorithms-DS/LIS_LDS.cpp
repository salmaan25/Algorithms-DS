#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
void findmaxLIS(int i, vi& num, vi& LIS) {
	int max = 1;
	for(int j = i+1; j < (int)LIS.size(); j++) {
		if(num[j] > num[i]) {
			if((LIS[j]+1) >= max)
				max = LIS[j]+1;
		}
	}
	LIS[i] = max;
}

void findmaxLDS(int i, vi& num, vi& LDS) {
	int max = 1;
	for(int j = i+1; j < (int)LDS.size(); j++) {
		if(num[i] > num[j]) {
			if((LDS[j]+1) >= max) 
				max=LDS[j]+1;
		} 
	}
	LDS[i] = max;
}
int main(void) {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		vi num(n);
		for(int i = 0; i < n; i++)
			scanf("%d", &num[i]);
		if(n == 0)
			printf("0\n");
		else if(n == 1)
			printf("1\n");
		else {
			vi LDS(n);
			vi LIS(n);
			LIS[n-1] = 1;
			LDS[n-1] = 1;
			for(int i = n-2; i >= 0; i--) {
				findmaxLIS(i, num, LIS);
				findmaxLDS(i, num, LDS);
			}
			int max = 0;
			for(int i = 0; i < n; i++) {
				if(max <= (LDS[i]+LIS[i]-1))
					max = (LDS[i]+LIS[i]-1);
			}
			printf("%d\n", max);
		}
	}
	return 0;
}