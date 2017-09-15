#ifndef MATRIXGFX
#define MATRIXGFX

#include <stdint.h>
#include <gsl/gsl_matrix.h>

gsl_matrix* openImg(const char* filename);


/*
 * Function:  saveImg
 * -----------------------------
 * save data in a gsl_matrix as an image
 *
 *  data: data matrix to save
 *  filename: filename of the new image
 *
 *  returns: return 0 if no eroor
 *           return -1 otherwise
 *
 */
void        saveImg(const gsl_matrix* data, const char* filename);

/*
 * Function:  drawLine
 * -----------------------------
 * draw a line in a matrix buffer
 *
 *  data: data matrix to write on
 *  x0, y0: first  point coordinates
 *	x1, y1: second point coordinates
 *
 */
void        drawLine(gsl_matrix* data, double x0, double y0, double x1, double y1);


void        drawMandelbrot(gsl_matrix* imgMatrix);

#endif
