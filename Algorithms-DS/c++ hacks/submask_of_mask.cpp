// mask goes till 2^n
for(int mask = 0; mask < (1<<n); mask++) {
	for (int submask=mask; ; submask=(submask-1)&mask) {
		// MY CODE
		if (submask==0) break;
	}
}