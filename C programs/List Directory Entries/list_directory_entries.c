#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
	DIR *dp = NULL;
	struct dirent *ep;	
	
	char* path = "/Users/vianneyyao/Documents";
	char* buf = (char*) malloc(100*sizeof(char));
	
	printf("%s\n", getcwd(buf, 100));
	
	dp = opendir(path);
	
	if (dp != NULL){
		
		while((ep = readdir(dp))){
			fputs(ep->d_name, stdout);
			fputs("\n", stdout);
		}
		(void) closedir(dp);
	}
	else{
		perror ("Couldn't open the directory");
	}
	
	free(buf);
	
	return 0;
	
}