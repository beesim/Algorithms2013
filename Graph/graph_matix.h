#ifndef _GRAPH_MATRIX_H_
#define _GRAPH_MATRIX_H_

typedef struct _graph_matrix {
	int** M;
	int r;
} GM;


void output_graph_matrix (GM* p)
{
	int i, j, r;
	r = p->r;
	printf (" \t");
	for (i = 0; i < r; i++) {
		printf ("%d\t", i);
	}
	for (i = 0; i < r; i++) {
		printf ("\n%d\t", i);
		for (j = 0; j < r; j++) {
			printf ("%d\t", p->M[i][j]);
		}
	}
	printf ("\n");
}


















#endif
