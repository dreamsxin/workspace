#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "list.h"

int main(int argc, char const *argv[]) {
  
  int n_files = 0;
  
  DList idx_files;
  dlist_init (&idx_files, NULL);
  
  n_files = get_filesnames("/Users/vianneyyao/Documents/Images", &idx_files);
  
  get_img_filenames(&idx_files);
  
  DListElmt *e = idx_files.head;
  while(e != NULL ){
    printf("%s\n", e->data);
    e = e->next;
  }
  
  while(idx_files.head != NULL){
    dlist_remove(&idx_files, idx_files.head, NULL);
  }
  
  return 0;
}
