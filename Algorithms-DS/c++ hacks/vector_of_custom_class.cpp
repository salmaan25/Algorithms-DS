// HERE WE CREATE A VECTOR OF CLASS SEGMENT TREE.

int main(void) {
	vector<SegmentTree> vs;
	vi a(n,0);
	for(int i = 0; i < 26; i++) {
		/*----------------IMPORTANT LINES--------------*/
		SegmentTree st(a);
		vs.pb(st);
		/*----------------IMPORTANT LINES--------------*/
	}
}