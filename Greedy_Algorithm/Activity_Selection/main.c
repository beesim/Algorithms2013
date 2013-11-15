#include <stdio.h>
#include <stdlib.h>

typedef int time;
typedef struct activity{
	int No;
	time start;
	time end;
} Activity;
int comp(const void* a1, const void* a2)
{
	return ((Activity*)a1)->end - ((Activity*)a2)->end;
}


int Greedy_Activity_Selection(Activity* AL, int n)
{
//	printf("%2d [%2d-%2d]\n", AL[0].No, AL[0].start, AL[0].end);
	int i, k = 0;
	for (i = 1; i < n; i++) {
		if (AL[i].start >= AL[k].end) {
			printf("%2d [%2d-%2d]\n", AL[i].No, AL[i].start, AL[i].end);
			k = i;
		}
	}
}



int main()
{
	Activity* AL; // Activity List
	int n = 0;
	scanf ("%d", &n);
	AL = (Activity*) malloc ((n + 1) * sizeof(Activity));
	AL[0].No = 0;
	AL[0].start = 0;
	AL[0].end = 0;

	int i;
	for (i = 1; i <= n; i++) {
		AL[i].No = i;
		scanf("%d %d", &AL[i].start, &AL[i].end);
	}

	qsort(AL, n + 1, sizeof(Activity), comp);

	Greedy_Activity_Selection(AL, n + 1);

	free(AL);
	return 0;
}
