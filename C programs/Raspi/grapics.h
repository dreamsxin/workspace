#ifndef GRAPHICS
#define GRAPHICS

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#include <gsl/gsl_matrix_ulong.h>

int print(char* filename, gsl_matrix_ulong* buffer);
int draw_mandelbrot_set();
int draw_julia_set();
int draw_sinus();
extern const uint64_t palette_tab[1460];


#endif
