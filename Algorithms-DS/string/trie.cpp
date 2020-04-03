#include <stdio.h>
//#include <stdbool.h>
#include <stdlib.h>
#include <vector>
using namespace std;
typedef struct trie trie;
struct trie
{
	bool isEnd;
	trie* trie_pnt;
};

typedef struct head head;
struct head
{
	trie* head_trie;
	long long int arCount;
};

void init(trie* node_pnt, int size)
{
	for(int i = 0; i < size; i++)
	{
		node_pnt[i].trie_pnt = NULL;
		node_pnt[i].isEnd = false;
	}
}

int add(head* header, const vector<int>& ar, int size)
{
	trie* tmp_trie = header->head_trie;
	for(int i = 0; i < size; i++)
	{
		if(i == size - 1)
		{
			if(tmp_trie[ar[i]].isEnd != true)
			{
				tmp_trie[ar[i]].isEnd = true;
				header->arCount += 1;
				if(header->arCount == 9000000000000000000)
					header->arCount = header->arCount % 1000000007;
				return 1;
			}
			else
				return 0;
		}
		else if(tmp_trie[ar[i]].trie_pnt == NULL)
		{
			trie* cur_trie = (trie*)malloc(101 * sizeof(trie));
			init(cur_trie, 101);
			tmp_trie[ar[i]].trie_pnt = cur_trie;
			tmp_trie = cur_trie;
		}
		else if(tmp_trie[ar[i]].trie_pnt != NULL)
		{
			tmp_trie = tmp_trie[ar[i]].trie_pnt;
		}
	}
}

void newArray(head* header, vector<int>& ar, int end_ind)
{
	for(int start_ind = 0; start_ind < end_ind; start_ind++)
	{
		if(end_ind - start_ind == 1)
		{
			if(ar[end_ind] > 0 && ar[start_ind] > 0)
			{
				//int* tmp_ar = malloc((end_ind + 2) * sizeof(int));
				/*int tmp_ar[end_ind + 2];
				for(int i = 0; i <= end_ind; i++)
					tmp_ar[i] = ar[i];
				tmp_ar[end_ind + 1] = 1;
				tmp_ar[end_ind] -= 1;
				tmp_ar[end_ind - 1] -= 1;*/
				ar.push_back(1);
				ar[end_ind] = ar[end_ind] - 1;
				ar[end_ind - 1] = ar[end_ind] - 1;
				int ans = add(header, ar, end_ind + 2);
				if(ans == 1)
					newArray(header, ar, end_ind + 1);
				ar[end_ind + 1] = 0;
				ar[end_ind] = ar[end_ind] + 1;
				ar[end_ind - 1] = ar[end_ind] + 1;
			}
		}
		else
		{
			if(ar[start_ind] > 0 && ar[start_ind + 1] > 0)
			{
				//int* tmp_ar = malloc((end_ind + 1) * sizeof(int));
				/*int tmp_ar[end_ind + 1];
				for(int i = 0; i <= end_ind; i++)
						tmp_ar[i] = ar[i];
				tmp_ar[start_ind] -= 1;
				tmp_ar[start_ind + 1] -= 1;
				tmp_ar[start_ind + 2] += 1; */
				ar[start_ind] = ar[start_ind] - 1;
				ar[start_ind + 1] = ar[start_ind] - 1;
				ar[start_ind + 2] = ar[start_ind] + 1;
				int ans = add(header, ar, end_ind + 1);
				if(ans == 1)
					newArray(header, ar, end_ind);
				ar[start_ind] = ar[start_ind] + 1;
				ar[start_ind + 1] = ar[start_ind] + 1;
				ar[start_ind + 2] = ar[start_ind] - 1;
			}
		}
	}
}

int main(void)
{
	int t;
	scanf("%d", &t);
	while(t > 0)
	{
		int n;
		scanf("%d", &n);
		vector<int> v;
		for(int i = 0; i < n; i++)
		{
			int tmp;
			scanf("%d", &tmp);
			v.push_back(tmp);
		}
		trie top[51];
		init(top, 51);
		head header;
		header.arCount = 0;
		header.head_trie = top;
		int a = add(&header, v, n);
		if(a == 1)
		{
			newArray(&header, v, n - 1);
		}
		printf("%lld\n", header.arCount % 1000000007);
		t--;
	}
	return 0;
}