#include <stdio.h>
#include <stdlib.h>
 
void sort(int ar[], int min, int max); //min and max indices of the array. Eg: to sort whole array min = 0  and max = n - 1 if array size is n
void merge(int ar[], int start, int mid, int end); // start is the index of the first element of left array mid is the index of the last element of the left array
                                                   // end is the index of the last element of the right array
 
int main(void)
{
    int len;
    scanf("%d", &len);
    int arr[len];
    int i;
    for(i = 0; i < len; i++)
        scanf("%d", &arr[i]);
    sort(arr, 0, len - 1);
    for(i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}










void sort(int ar[], int min, int max)
{
    if((max - min + 1) < 2)
        return ;
    else
    {
        if(((max - min + 1) % 2) == 1)
        {
            sort(ar, min, min - 1 + ((max - min + 1) / 2));
            sort(ar, min + ((max - min + 1) / 2), max);
            merge(ar, min, min - 1 + ((max - min + 1) / 2), max);
        }
        else
        {
            sort(ar, min, min - 1 + ((max - min + 1) / 2));
            sort(ar, min + ((max - min + 1) / 2), max);
            merge(ar, min, min - 1 + ((max - min + 1) / 2), max);
        }
    }
    return ;
}
 
 
void merge(int ar[], int start, int mid, int end)
{
    int kar[end - start + 1];
    int i, j, k; // i for left half, j for right half, k for kar 
    for(i = start, j = (mid + 1), k = 0;;)
    {
        if(i <= mid && j <= end)
        {
            if(ar[i] > ar[j])
            {
                kar[k] = ar[j];
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
}
 

