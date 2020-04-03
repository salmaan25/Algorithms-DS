// CALCULATION OF NUMBER OF INVERSION

#include <stdio.h>
// last, first are all indices
int SortCountInv(int arr[], int first, int last);
int MergeCountSplitInv(int ar[], int start, int mid, int end);
//mid is on the left hand's side
int main(void)
{
	int n;
	scanf("%d", &n);
	int arr[n];
	int i;
	for(i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	int x = SortCountInv(arr, 0, n - 1);
	printf("%d", x);
	return 0;
}

int SortCountInv(int arr[], int first, int last)
{
	if(last - first + 1 == 1)
	{
		return 0;
	}
	else
	{
		/*int leftArray[(last - first) / 2 + 1];
		int rightArray[last - first - ((last - first) / 2)];
		int i;
		for(i = first; i < last - first + 1; i++)
		{
			if(i <= (last - first) / 2 )
			{
				leftArray[i] = arr[i];
			}
			else
			{
				rightArray[i - ((last - first) / 2) - 1] = arr[i];
			}
		}*/
		int i;

		int x = SortCountInv(arr, first, first + ((last - first) / 2));
		//printf("left half: %d\n", x);
		
		/*for(i = 0; i <= (last - first) / 2; i++)
			printf("%d  ", leftArray[i]);*/

		int y = SortCountInv(arr, last - ((last - first) / 2), last);
		//printf("right half: %d\n", y);
		/*printf("                  ");
		for(i = 0; i <= (last - first) / 2; i++)
			printf("%d  ", rightArray[i]);*/
		int z = MergeCountSplitInv(arr, first, last - ((last - first) / 2) - 1, last);
		//printf("split inv%d\n", z);
		/*for(i = 0; i < last - first + 1; i++)
		{
			arr[i] = mergedArray[i];
		}
		return x + y + z;*/
		return x + y + z;
	}
}


int MergeCountSplitInv(int ar[], int start, int mid, int end)
{
	int CountInv = 0;
    int kar[end - start + 1];
    int i, j, k; // i for left half, j for right half, k for kar 
    for(i = start, j = (mid + 1), k = 0;;)
    {
        if(i <= mid && j <= end)
        {
            if(ar[i] > ar[j])
            {
                kar[k] = ar[j];
                CountInv += mid - i + 1;
                j++;
                k++;
            }
            else if(ar[i] < ar[j])
            {
                kar[k] = ar[i];
                i++;
                k++;
            }
            else
            {
                kar[k] = ar[i];
                k++;
                kar[k] = ar[i];
                k++;
                i++;
                j++;
            }
        }
        else if(i > mid && j <= end)
        {
            kar[k] = ar[j];
            j++; 
            k++;
        }
        else if(j > end && i <= mid)
        {
            kar[k] = ar[i];
            i++;
            k++;
        }
        else if(i > mid && j > end)
        {
            break;
        }
    }
    
    for(i = 0; (i < (end - start + 1)) ; i++)
    {
        ar[start + i] = kar[i];
    }
    return CountInv;
}
 

