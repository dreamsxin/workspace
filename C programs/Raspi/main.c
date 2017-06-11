#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <gsl/gsl_matrix_ulong.h>
#include "LedMatrixDriver.h"
#include "MatrixGFX.h"
#include "files.h"
#include "dlist.h"
#include "grapics.h"



//void printButton(int g)
//{
//  if (GET_GPIO(g)) // !=0 <-> bit is 1 <- port is HIGH=3.3V
//    printf("Button pressed!\n");
//  else // port is LOW=0V
//    printf("Button released!\n");
//}

int main(int argc, char **argv)
{
//  setup_io();
   
  
  printf("Hello world\n");
  draw_sinus();
  
//  gsl_matrix* imgMatrix = NULL; 
//  int n_files = 0;
//  
//  DList idx_files;
//  dlist_init (&idx_files, NULL);
//  
//  n_files = get_dir_filesnames(&idx_files);
//  
////  get_img_filenames(&idx_files);
//  
//  DListElmt *e = idx_files.head;
//  imgMatrix = openImg(e->data);
//  while(e != NULL ){
////    printf("%s\n", e->data);
//    openImg(e->data);
//    e = e->next;
//  }
  
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
  
  
//  int g,rep;
//
//  // Set up gpi pointer for direct register access
//  setup_io();
//
//  // Set GPIO pin 11 to output
//  INP_GPIO(18); // must use INP_GPIO before we can use OUT_GPIO
//  OUT_GPIO(18);
//
//  for (int i = 0; i < 9; i++){
//
//  GPIO_SET = 1<<18;
//  sleep(1);
// 
//  GPIO_CLR = 1<<18;
//  sleep(1);
//
//  }

  return 0;

} // main





