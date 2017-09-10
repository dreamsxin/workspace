#ifndef MATRIXGFX
#define MATRIXGFX

#include <stdint.h>
#include <gsl/gsl_matrix.h>

gsl_matrix* openImg(const char* filename);
uint8_t     saveImg(const gsl_matrix* data, const char* filename);

#endif