#include <stdio.h>

int main()
{
	int a[5] = {5, 1, 3, 4, 0};
	int n = 5;

	for (int i = 1; i < n; i++)
	{
		int t = a[i];
		int j;
		for (j = i - 1; j >= 0 && t < a[j]; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}