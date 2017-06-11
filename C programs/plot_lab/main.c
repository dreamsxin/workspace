#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <unistd.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include "plot_lab.h"

int main(int argc, char **argv)
{

	gsl_vector* x = gsl_vector_alloc(300);
	gsl_vector* y = gsl_vector_alloc(300);
		
		for (double j=0; j<x->size; j++){
				
				gsl_vector_set(x, j, j);
				gsl_vector_set(y, j, 0.5*(cos(2 * M_PI * 4 * (j / x->size)) + 1)*(x->size-1));
//				gsl_vector_set(y, j, 1/j);
//				printf("sin(%f) %f\n", j, 0.5*(sin(2 * M_PI * 4 * (j / x->size)) + 1)*(x->size-1));
				
		}
	
	printf("Hello world\n");
	plot(x, y);
//	draw_sinus();
	

	return 0;

} // main





