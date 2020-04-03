int xor_func(int num){
	if (num%4==0) return num;
	else if (num%4==1) return 1;
	else if (num%4==2) return num+1;
	else return 0;
}
int XOR(int l, int r) {return (xor_func(r)^xor_func(l-1));}