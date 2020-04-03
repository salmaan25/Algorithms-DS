#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct trieblock node;

struct trieblock 
{
	char alphabet;
	char reply[4];//store y+ or y-
	char plus;
	char minus;
	node* pnt;
};
typedef node *node_pnt;

typedef struct 
{
	node_pnt first;
	int count;
}head;

void load(char plusORminus, char* dict, head* header, int len);
void init(node_pnt pointer);
void check(node_pnt cur_node, char* ar, int j);
char CheckEnd(node_pnt cur_node);
void checkspell(head* header, char key[], int len);

int main(void)
{
	head* header = malloc(sizeof(head));
	(*header).count = 0;
	(*header).first = NULL;
	int n;
	scanf("%d", &n);
	char plusORminus;
	char name[100];
	int i;
	//int length;
	for(i = 0; i < n; i++)
	{
		scanf(" %c", &plusORminus);
		scanf(" %s", name);
		//length = strlen(name);
		//printf("%d\n", length);
		//printf("r\n");
		//printf("%s\n", name);
		//printf("%c\n", plusORminus);
		load(plusORminus, name, header, strlen(name));
		//printf("rg\n");
	}
	char checker[100];
	scanf("%s", checker);
	checkspell(header, checker, strlen(checker));
	node_pnt t = (*header).first;
	printf("%c", (t['c' - 'a']).alphabet);
	char ar[300000];
	check((*header).first, ar, 0);
	/*for (i = 0; i < 6; i++)
	{
		printf("%c", ar[i]);
	}*/
	return 0;
}

void load(char plusORminus, char* dict, head* header, int len)
{
	node_pnt current_node = NULL;
	node_pnt head_node = NULL;
	node_pnt temp_node = NULL;
	char temp_char;
	int i = 0;
	temp_char = dict[i];
	//printf("%c\n", temp_char);
	i++;
	char prev_char = temp_char;
	head_node = malloc(26 * sizeof(node));
	init(head_node);
	(*header).first = head_node;
	current_node = head_node;
	prev_char = temp_char;
	temp_char = dict[i];

		while(i < len)
		{
			if((current_node[prev_char - 'a']).pnt == NULL)
			{
				temp_node = malloc(26 * sizeof(node));
				init(temp_node);
				(current_node[prev_char - 'a']).pnt = temp_node;
				if (plusORminus == '+')
					(current_node[prev_char - 'a']).plus = '+';
				else
					(current_node[prev_char - 'a']).minus = '-';
				current_node = temp_node;
			}
			else
			{
				current_node = (current_node[prev_char - 'a']).pnt;
			}
			prev_char = temp_char;
			temp_char = dict[i];
			i++;
		}
		if(plusORminus == '+')
			strcpy((current_node[prev_char - 'a']).reply, "y+");
		else
			strcpy((current_node[prev_char - 'a']).reply, "y-");
}


void init(node_pnt pointer)
{
	int i;
	for(i = 0; i < 26; i++)
	{
		(pointer[i]).alphabet = (char)('a' + i);
		(pointer[i]).pnt = NULL;
	}
}

char CheckEnd(node_pnt cur_node)
{
	if(strcmp(cur_node->reply, "y+") == 0)
	{
		return '+'; 
	}
	else if(strcmp(cur_node->reply, "y-") == 0)
	{
		return '-';
	}
	else
	{
		return 'n';
	}
}

void check(node_pnt cur_node, char* ar, int j)
{
	int i = 0;
	while(i != 26)
	{
		if((cur_node[i]).plus == '+' && (cur_node[i]).minus == '-')
		{
			if(CheckEnd(&cur_node[i]) == 'n')
			{
				ar[j] = (cur_node[i]).alphabet;
				j++;
				check((cur_node[i]).pnt, ar, j);
			}
			else if(CheckEnd(&cur_node[i]) == '-')
			{
				printf("-1\n");
				break;    
			}
			else
			{
				ar[j] = cur_node[i].alphabet;
				j++;
				check((cur_node[i]).pnt, ar, j);
			}
		}
		else if((cur_node[i]).plus != '+' && (cur_node[i]).minus == '-')
		{
			ar[j] = cur_node[i].alphabet;
			i++;
		}
		else if((cur_node[i]).plus == '+' && (cur_node[i]).minus != '-')
		{
			i++;
		}
		else
		{
			i++;
		}
	}
}









void checkspell(head* header, char key[], int len)
{
	int i;
	node_pnt start = NULL;
	start = header->first; 
	for(i = 0; i < len; i++)
	{
		char cha = key[i];
		if(i != len - 1)
		{
			if((start[cha - 'a']).pnt == NULL)
			{
				printf("mis-spelled\n");
				break;
			}
			else
			{
				start = (start[cha - 'a']).pnt;
			}
		}
		else
		{
			if(strcmp(((start[cha - 'a']).reply), "y-") == 0 || strcmp(((start[cha - 'a']).reply), "y+") == 0)
			{
				printf("correctly spelled\n");
				break;
			}
			else
			{
				printf("mis-spelled\n");
			}
		}
	}
}