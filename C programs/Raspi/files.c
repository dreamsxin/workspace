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





/*
 * Function:  _isImg 
 * -----------------
 * check if a filename is a supported image filenamei:
 *
 *  file: filename to check
 *
 *  returns: 1 if match
 *.          0 otherwise
 *        
 */
int _isImg(const char* file){
  
  regex_t reg;
  const char* reg_str = ".*\\.png";
  
  if (!regcomp(&reg, reg_str, REG_ICASE)){
    
    if (!regexec(&reg, file, 0, NULL, 0))
      return 1;
  }
  
  else{
    printf("RegEx compilation error");
  }

  return 0;
}




/*
 * Function:  get_img_filesnames 
 * -----------------------------
 * scan a directory and sub-directories for images filenemas:
 *
 *  files_lst: list to contain the filenames
 *
 *  returns: return 0 if no eroor
 *           return -1 otherwise
 *        
 */
int get_img_filesnames(DList* files_lst){
  
  //Array of pointers to structures of type struct dirent which describe all 
  //selected directory entries and which is allocated using malloc
  struct dirent ** _eps;
  
  int _Nentries;                //the number of images filenames
  char* _filename;              
  char* _folder = "./Images";   //default image folder
  
  //scan directory and get filenames in sorted order
  _Nentries = scandir(_folder, &_eps, one, alphasort);
  
  if (_Nentries >= 0){

      for (int cnt = 0; cnt < _Nentries; cnt++){
        _filename = (char*) malloc(200 * sizeof(char));
        
        strcpy(_filename, _folder);
        strcat(_filename, "/");
        strcat(_filename, _eps[cnt]->d_name);
        
        //check if filename is an image filename
        if (_isImg(_filename))
          dlist_ins_next(files_lst, files_lst->tail, _filename);
      }
      
      return 0;
  }
    
  else {
    perror ("Couldn't open the directory");
    return -1;
  }

}

