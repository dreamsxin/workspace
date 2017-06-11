#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>

int
main (void)
{
	double* t = (double*) calloc(4, sizeof(double));

	gsl_matrix * m = gsl_matrix_alloc (2, 2);
	m->data = t;
	gsl_matrix_set(m, 1, 0, 22);
	
	gsl_matrix_fprintf(stdout, m, "%f");
	
	return 0;
	
}