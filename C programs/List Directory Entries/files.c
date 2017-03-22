#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <regex.h>
#include <sys/stat.h>
#include <string.h>
#include "files.h"
#include "list.h"

static int one (const struct dirent *unused){
  return 1;
}

int get_img_filenames(DList* files_lst){
  
  regex_t reg;
  const char* reg_str = ".*\\.png";
  
  DListElmt* file = files_lst->head; 
  DListElmt* tmp;
  void *data = NULL;
  
  if (!regcomp(&reg, reg_str, REG_ICASE)){

    while(file != NULL){
      
      if (regexec(&reg, file->data, 0, NULL, 0)){
        
        if (!dlist_is_tail(file))
          file = file->next;
          
        dlist_remove(files_lst, file->prev, &data);
      }
      
      else 
        file = file->next;
        
    }
  }
  
  else{
    printf("RegEx compilation error");
  }

  return 0;
}

int get_filesnames(char* folder, DList* files_lst){
  
  struct dirent **eps;
  struct stat   buf;
  int f_entries;
  char* filename;
  
  f_entries = scandir(folder, &eps, one, alphasort);
  
  if (f_entries >= 0){

      for (int cnt = 0; cnt < f_entries; cnt++){
        filename = (char*) malloc(200 * sizeof(char));
        
        strcpy(filename, folder);
        strcat(filename, "/");
        strcat(filename, eps[cnt]->d_name);

        dlist_ins_next(files_lst, files_lst->tail, filename);
      }
  }
    
  else {
    perror ("Couldn't open the directory");
  }

  return f_entries;
}

