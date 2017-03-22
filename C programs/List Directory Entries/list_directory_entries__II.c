#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

static int one (const struct dirent *unused){
	return 1;
}

int main(int argc, char *argv[]) {
	
	struct dirent **eps;
	struct stat   buf;
	int n;
	char filename[200];
	char* dir = "/Users/vianneyyao/Desktop";
	
	n = scandir(dir, &eps, one, alphasort);
	
	if (n >= 0){
		int cnt;
		for (cnt = 0; cnt < n; cnt++){

			strcpy(filename, dir);
			strcat(filename, "/");
			strcat(filename, eps[cnt]->d_name);
			puts(filename);

			if (stat(filename, &buf) == 0){
				if (S_ISREG(buf.st_mode))
					printf("regular file\n");
				if (S_ISDIR(buf.st_mode))
					printf("directory\n");
			}
		}
	}
	
	else {
		perror ("Couldn't open the directory");
	}
	
	return 0;
	
}