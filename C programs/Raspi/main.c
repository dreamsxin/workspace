#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <gsl/gsl_matrix_ulong.h>
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

  gsl_matrix* imgMatrix = gsl_matrix_alloc(100, 200);
  gsl_matrix_set_identity(imgMatrix);
  gsl_matrix_scale(imgMatrix, 255);

  DList idx_files;
  dlist_init (&idx_files, NULL);

  if (!get_img_filesnames(&idx_files)){


    DListElmt *e = idx_files.head;
  //  imgMatrix = openImg(e->data);
    while(e != NULL ){
      printf("%s\n", e->data);
  //    openImg(e->data);
      e = e->next;
    }
  }
  
  saveImg(imgMatrix, "img");

//  gsl_matrix_fprintf(stdout, imgMatrix, "%f");
//  display(imgMatrix);


//  pinMode(14, 1);
//  while(1){
//    digitalWrite(14, 1);
//    sleep(1);
//    digitalWrite(14, 0);
//    sleep(1);
//    }
//  MatrixBuffer* buf = (MatrixBuffer*) malloc(sizeof(MatrixBuffer));
//  MatrixBuffer_init(buf, 2, 2);
//
//  printf("height: %zu, width: %zu\n", buf->data->size1, buf->data->size2);
//
//  int n_files = 0;
//  DList idx_files;
//  dlist_init (&idx_files, NULL);
//
//  n_files = get_dir_filesnames(&idx_files);
//
//  get_img_filenames(&idx_files);
//
//  DListElmt *e = idx_files.head;
//  while(e != NULL ){
//    printf("%s\n", e->data);
//    e = e->next;
//  }



  return 0;

} // main
