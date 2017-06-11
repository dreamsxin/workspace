#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

void* thread_function(void *arg) {

	
	int* incoming = (int *) arg;
//	while (1) {
		printf("Thread %d\n", *incoming);
//	}

	return incoming; 
}

int main(void) {
	pthread_t thread_ID;
	pthread_t* ptab;
	void* exit_status; 
	int value;

	value = 42;
	ptab = (pthread_t*) malloc(10 * sizeof(pthread_t));
	int tab[10];
	
	for(int i = 0; i < 10; i++){
		tab[i] = i;
		pthread_create(&ptab[i] , NULL, thread_function , &tab[i]);
		pthread_join(ptab[i] , &exit_status );
//		printf("%f\n", *(double*)exit_status);
	}

	free(ptab);
	return 0 ; 
}