#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <regex.h>
#include <sys/stat.h>
#include <string.h>
#include <png.h>
#include "files.h"
#include "dlist.h"

static int one (const struct dirent *unused){
  return 1;
}


int _isImg(const char* file){
  
  regex_t reg;
  const char* reg_str = ".*\\.png";
  
  if (!regcomp(&reg, reg_str, REG_ICASE)){
    
    if (!regexec(&reg, file, 0, NULL, 0))
      return 1;
    else 
      return 0;
  }
  
  else{
    printf("RegEx compilation error");
  }

  return 0;
}

int get_dir_filesnames(DList* files_lst){
  
  struct dirent **eps;
  struct stat   buf;
  int f_entries;
  char* filename;
  char* folder = "./Images";
  
  f_entries = scandir(folder, &eps, one, alphasort);
  
  if (f_entries >= 0){

      for (int cnt = 0; cnt < f_entries; cnt++){
        filename = (char*) malloc(200 * sizeof(char));
        
        strcpy(filename, folder);
        strcat(filename, "/");
        strcat(filename, eps[cnt]->d_name);
        
        if (_isImg(filename))
          dlist_ins_next(files_lst, files_lst->tail, filename);
      }
  }
    
  else {
    perror ("Couldn't open the directory");
  }

  return f_entries;
}

