#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "list.h"

int main(int argc, char const *argv[]) {
  
  char** filenames = NULL;
  int n_files = 0;
  List l;
  list_init (&l, &destroy_Elmt);
  
  int a = 2;
  int b = 3;
  int c = 5;
  
  
  list_ins_next(&l, NULL, &a);
  list_ins_next(&l, NULL, &b);
  list_ins_next(&l, NULL, &c);
  
  ListElmt *e = l.head;
  
  while(e != NULL ){
    printf("%d\n", *(int*)(e->data));
    e = e->next;
  }
  
  n_files = get_filesnames("/Users/vianneyyao/Documents/Images", &filenames);
  
//  for (int i = 0; i < n_files; i++){
//    printf("%s\n", filenames[i]);
//  }
  
  get_img_filenames(&filenames, n_files);
  
  for (int i = 0; i < n_files; i++){
    free(filenames[i]);
  }
  
  free(filenames);
  
  return 0;
}
