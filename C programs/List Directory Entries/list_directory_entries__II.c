#include <stdio.h>
#include <dirent.h>

static int one (const struct dirent *unused){
	return 1;
}

int main(int argc, char *argv[]) {
	
	struct dirent **eps;
	int n;
	
	n = scandir("/Users/vianneyyao/Desktop", &eps, one, alphasort);
	
	if (n >= 0){
		int cnt;
		for (cnt = 0; cnt < n; cnt++){
			puts(eps[cnt]->d_name);
		}
	}
	
	else {
		perror ("Couldn't open the directory");
	}
	
	return 0;
	
}