#include <bits/stdc++.h>

using namespace std;
typedef struct block block;
struct block
{
	block* next_block;
	//while((getchar()) != '\n');
	int smallestWordNum[2]; //which words contain this alphabet at this place
	bool isEnd;
};
void insertWord(char* word, block* head, int wordNum);
void initialize(block* alphaset);
void checkLCP(block* head,char*  word,int range);
int findLeast(block* cur_block, int range);
void print(block* start, vector<char>& prefix, int range);

int main(void) {
	int n;
	scanf("%d", &n);
	block head[26];
	initialize(head);
	for(int i = 0; i < n; i++) {
		char word[20];
		while((getchar()) != '\n');
		scanf("%s", word);
		insertWord(word, head, i + 1);
	}
	/*block* printer = head;
	printf("%d %d\n", printer[0].smallestWordNum, (int)printer[0].isEnd);
	printer = printer[0].next_block;
	printf("%d %d\n", printer[1].smallestWordNum, (int)printer[1].isEnd);
	printer = printer[1].next_block;
	printf("%d %d\n", printer[2].smallestWordNum, (int)printer[2].isEnd);
	printer = printer[2].next_block;
	printf("%d %d\n", printer[3].smallestWordNum, (int)printer[3].isEnd);
	printf("%d %d\n", printer[24].smallestWordNum, (int)printer[24].isEnd);*/
	int q = 0;
	scanf("%d", &q);
	for(int i = 0; i < q; i++) {
		int range;
		char word[20];
		scanf("%d", &range);
		while((getchar()) != ' ');
		scanf("%s", word);
		checkLCP(head, word, range);
	}
	return 0;
}

void initialize(block* alphaset) {
	for(int i = 0; i < 26; i++) {
		alphaset[i].next_block = NULL;
		alphaset[i].isEnd = false;
		alphaset[i].smallestWordNum[0] = 0;
		alphaset[i].smallestWordNum[1] = 0;
	}
}

void insertWord(char* word, block* head, int wordNum) {
	block* curBlock = head;
	block* alphaset = NULL;
	int length = (int)strlen(word);
	//printf("length = %d\n", length);
	for (int i = 1; i <= length; i++) {
		if(i == length) {
			curBlock[(int)word[i - 1] - 'a'].isEnd = true; //check and complete this
			if(curBlock[(int)word[i - 1] - 'a'].smallestWordNum[1] == 0)
				curBlock[(int)word[i - 1] - 'a'].smallestWordNum[1] = wordNum;
			if(curBlock[(int)word[i - 1] - 'a'].smallestWordNum[0] == 0)
				curBlock[(int)word[i - 1] - 'a'].smallestWordNum[0] = wordNum;
			//printf("Word Inserted\n");
		}
		else if(curBlock[(int)(word[i - 1]) - 'a'].next_block == NULL) {
			//change vector alphanum
			alphaset = (block*)malloc(26 * sizeof(block));
			initialize(alphaset);
			if(curBlock[(int)word[i - 1] - 'a'].smallestWordNum[0] == 0)
				curBlock[(int)word[i - 1] - 'a'].smallestWordNum[0] = wordNum;
			curBlock[(int)(word[i - 1]) - 'a'].next_block = alphaset;
			curBlock = alphaset;
			//printf("%d Letter Inserted\n", i);
		}
		else{
			//change vector alphanum
			if(curBlock[(int)word[i - 1] - 'a'].smallestWordNum[0] == 0)
				curBlock[(int)word[i - 1] - 'a'].smallestWordNum[0] = wordNum;
			curBlock = curBlock[(int)(word[i - 1] - 'a')].next_block;
			//printf("%d already present\n", i);
		}
	}
}



void checkLCP(block* head, char*  word, int range) {
	int len = (int)strlen(word);
	block* cur_block = head;
	vector<char> ans;
	block* prev_block = cur_block; 
	//printf("pass 0\n");
	int i = 0;
	for(i = 0; i < len; i++) {
		if(cur_block == NULL) {
			print(prev_block, ans, range);
			break;
		}
		else if(cur_block[(int)word[i] - 'a'].smallestWordNum[0] == 0) {
			//printf("going in\n");
			//printf("%d\n", i);
			print(prev_block, ans, range);
			break;
		}
		else if(cur_block[(int)word[i] - 'a'].smallestWordNum[0] > range) {
			print(prev_block, ans, range);
			break;
		}
		else {
			prev_block = cur_block;
			ans.push_back(word[i]);
			cur_block = cur_block[(int)word[i] - 'a'].next_block;
		}
		//printf("pass %d\n", i);
	}
	if(i == len)
		print(prev_block, ans, range);
	//printf("pass final\n");
}

void print(block* start, vector<char>& prefix, int range) {
	//check whether word ends there word in start is alreadyb present in the vector
	block* cur_block = start;
	int len = (int)prefix.size();
	//printf("%d       ", len);
	char curAlpha;
	if(len != 0)
		curAlpha  = prefix[len - 1];
	else {
		curAlpha = (char)(findLeast(cur_block, range) + (int)'a');
		prefix.push_back(curAlpha);
	}

	//printf("%c\n", curAlpha);
	while(true) {
		if(cur_block == NULL)
			break;
		if(cur_block[(int)curAlpha - 'a'].isEnd == true && cur_block[(int)curAlpha - 'a'].smallestWordNum[0] <= range && cur_block[(int)curAlpha - 'a'].smallestWordNum[1] <= range)
			break;
		else {
			cur_block = cur_block[(int)curAlpha - 'a'].next_block;
			int j = findLeast(cur_block, range);
			if(j == -1)
				break;
			else {
				curAlpha = (char)(j + (int)'a');
				prefix.push_back(curAlpha);
			}
		}
	}
	for(int i = 0; i < (int)prefix.size(); i++)
		printf("%c", prefix[i]);
	printf("\n");
}

int findLeast(block* cur_block, int range) {
	for(int i = 0; i < 26; i++) {
		if(cur_block[i].smallestWordNum[0] != 0 && cur_block[i].smallestWordNum[0] <= range)
			return i;
	}
	return -1;
}