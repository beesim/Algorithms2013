#include <stdio.h>

int mergesort(int A[], int num)
{
	if (num <= 1) {
		return 0:
	}
	
	mergesort(A, num / 2);
	mergesort(A + num / 2, num - num / 2);
	merge(A, num / 2, A + num / 2, num - num / 2);
	return 0;
}
