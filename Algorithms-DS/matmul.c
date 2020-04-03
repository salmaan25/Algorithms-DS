	#include <stdio.h>

	void prod(int n, int arr[][n], int arr1[][n], int arr2[][n], int cr1c, int cr1r, int cr2c, int cr2r); // cr1s are coordinates of first array, cr2s are coordinates of 2nd array
	void AddMat(int size, int n, int arr[][size], int a[][n], int b[][n], int c[][n], int d[][n], int e[][n], int f[][n], int g[][n], int h[][n]);
	void printmat(int size, int arr[][size]);
	int main(void)
	{
		int n;
		scanf("%d", &n);
		int arr1[n][n];
		int i, j;
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
				scanf("%d", &arr1[i][j]);
		} 
		//printmat(n, arr1);
		int arr2[n][n];
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
				scanf("%d", &arr2[i][j]);
		}
		//printmat(n, arr2);
		int a[n][n];
		prod(n, a, arr1, arr2, 0, 0, 0, 0);
		printmat(n, a);
		return 0;
	}
	void prod(int n, int arr[][n], int arr1[][n], int arr2[][n], int cr1c, int cr1r, int cr2c, int cr2r)
	{
		if(n == 1)
		{
	 		arr[0][0] = (arr1[cr1r][cr1c] * arr2[cr2r][cr2c]);
	 		//return;
		}
		else
		{
			int a[n / 2][n / 2];
			prod(n / 2, a, arr1, arr2, cr1c, cr1r, cr2c, cr2r);
			printmat(n / 2, a);
			printf("%d %d %d %d\n", cr1c, cr1r, cr2c, cr2r);
			int b[n / 2][n / 2];
			prod(n / 2, b, arr1, arr2, cr1c + ((n - 1) / 2) + 1, cr1r, cr2c, cr2r + ((n - 1) / 2) + 1);
			printmat(n / 2, b);
			printf("%d %d %d %d\n", cr1c + ((n - 1) / 2) + 1, cr1r, cr2c, cr2r + ((n - 1) / 2) + 1);
			int c[n / 2][n / 2]; 
			prod(n / 2, c, arr1, arr2, cr1c, cr1r, cr2c + ((n - 1) / 2) + 1, cr2r);
			printmat(n / 2, c);
			printf("%d %d %d %d\n", cr1c, cr1r, cr2c + ((n - 1) / 2) + 1, cr2r);
			int d[n / 2][n / 2];
			prod(n / 2, d, arr1, arr2, cr1c + ((n - 1) / 2) + 1, cr1r, cr2c + ((n - 1) / 2) + 1, cr2r + ((n - 1) / 2) + 1);
			printmat(n / 2, d);
			printf("%d %d %d %d\n", cr1c + ((n - 1) / 2) + 1, cr1r, cr2c + ((n - 1) / 2) + 1, cr2r + ((n - 1) / 2) + 1);
			int e[n / 2][n / 2];
			prod(n / 2, e, arr1, arr2, cr1c, cr1r + ((n - 1) / 2) + 1, cr2c, cr2r);
			printmat(n / 2, e);
			printf("%d %d %d %d\n", cr1c, cr1r + ((n - 1) / 2) + 1, cr2c, cr2r);
			int f[n / 2][n / 2];
			prod(n / 2, f, arr1, arr2, cr1c + ((n - 1) / 2) + 1, cr1r + ((n - 1) / 2) + 1, cr2c, cr2r + ((n - 1) / 2) + 1);
			printmat(n / 2, f);
			printf("%d %d %d %d\n", cr1c + ((n - 1) / 2) + 1, cr1r + ((n - 1) / 2) + 1, cr2c, cr2r + ((n - 1) / 2) + 1);
			int g[n / 2][n / 2];
			prod(n / 2, g, arr1, arr2, cr1c, cr1r + ((n - 1) / 2) + 1, cr2c + ((n - 1) / 2) + 1, cr2r);
			printmat(n / 2, g);
			printf("%d %d %d %d\n", cr1c, cr1r + ((n - 1) / 2) + 1, cr2c + ((n - 1) / 2) + 1, cr2r);
			int h[n / 2][n / 2];
			prod(n / 2, h, arr1, arr2, cr1c + ((n - 1) / 2) + 1, cr1r + ((n - 1) / 2) + 1, cr2c + ((n - 1) / 2) + 1, cr2r + ((n - 1) / 2) + 1);
			printmat(n / 2, h);
			printf("%d %d %d %d\n", cr1c + ((n - 1) / 2) + 1, cr1r + ((n - 1) / 2) + 1, cr2c + ((n - 1) / 2) + 1, cr2r + ((n - 1) / 2) + 1);
			AddMat(n, n / 2, arr, a, b, c, d, e, f, g, h);
		}
	}


	void AddMat(int size, int n, int arr[][size], int a[][n], int b[][n], int c[][n], int d[][n], int e[][n], int f[][n], int g[][n], int h[][n])
	{
		int i;
		int j;
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				arr[i][j] = a[i][j] + b[i][j];
				arr[i][n + j] = c[i][j] + d[i][j];
				arr[n + i][j] = e[i][j] + f[i][j];
				arr[n + i][n + j] = g[i][j] + h[i][j];  
			}
		}
	}


	void printmat(int size, int arr[][size])
	{
		int i, j;
		for(i = 0; i < size; i++)
		{
			for(j = 0; j < size; j++)
			{
				printf("%d ", arr[i][j]);
			}
			printf("\n");
		}
	}