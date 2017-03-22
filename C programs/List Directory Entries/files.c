#define _GNU_SOURCE

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

int get_img_filenames(char*** filenames, int size_tab){
  
  regex_t reg;
  const char* reg_str = ".*\\.png";
  
  if (!regcomp(&reg, reg_str, REG_ICASE)){

    for (int i = 0; i < size_tab; i++){
      if (!regexec(&reg, (*filenames)[i], 0, NULL, 0))
        printf("%s\n", (*filenames)[i]);
    }
  }

  
  return 0;
}

int get_filesnames(char* folder, char*** filenames){
  
  struct dirent **eps;
  struct stat   buf;
  int f_entries;
  char filename[200];
  
  
  f_entries = scandir(folder, &eps, one, alphasort);
  
  *filenames = (char**) malloc(f_entries * sizeof(char*));
  for (int i = 0; i < f_entries; i++){
    (*filenames)[i] = (char*) malloc(200 * sizeof(char));
  }
  
  if (f_entries >= 0){
      int cnt;
      for (cnt = 0; cnt < f_entries; cnt++){

        strcpy(filename, folder);
        strcat(filename, "/");
        strcat(filename, eps[cnt]->d_name);

        strcpy((*filenames)[cnt], filename);
      }
    }
    
    else {
      perror ("Couldn't open the directory");
    }

  return f_entries;
}
