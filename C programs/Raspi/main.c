#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include "dlist.h"
#include "files.h"
#include "LedMatrixDriver.h"
#include "MatrixGFX.h"
//#include "grapics.h"


int main(int argc, char **argv)
{
//  LedMatrixDriver_init();
//  display(NULL);


  printf("Hello world\n");

  gsl_matrix* imgMatrix = gsl_matrix_alloc(32, 64);
//  gsl_matrix_set_identity(imgMatrix);
//  gsl_matrix_scale(imgMatrix, 255);

  DList idx_files;
  dlist_init (&idx_files, NULL);

  if (!get_img_filesnames(&idx_files)){

    DListElmt *e = idx_files.head;

    while(e != NULL ){
      printf("%s\n", (char* )(e->data));
      e = e->next;
    }
  }

  drawMandelbrot(imgMatrix);

  // drawLine(imgMatrix, 0, 0, 50, 100);
  saveImg(imgMatrix, "img");

  LedMatrixDriver_init();
  display(imgMatrix);


  return 0;

} // main
