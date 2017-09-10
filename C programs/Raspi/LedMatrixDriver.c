#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <gsl/gsl_matrix.h>
#include "LedMatrixDriver.h"

int  mem_fd;
void *gpio_map;
//
//// I/O access
volatile unsigned *gpio;

// Set up a memory regions to access GPIO
void setup_io(){
	
	/* open /dev/mem */
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
		printf("can't open /dev/mem \n");
		exit(-1);
	}

	/* mmap GPIO */
	gpio_map = mmap(
		NULL,             //Any adddress in our space will do
		BLOCK_SIZE,       //Map length
		PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
		MAP_SHARED,       //Shared with other processes
		mem_fd,           //File to map
		GPIO_BASE         //Offset to GPIO peripheral
	);

	close(mem_fd); //No need to keep mem_fd open after mmap

	if (gpio_map == MAP_FAILED) {
		printf("mmap error %d\n", (int)gpio_map);//errno also set!
		exit(-1);
	}

	// Always use volatile pointer!
	gpio = (volatile unsigned *)gpio_map;


} // setup_io

//mode = 1 -> Output
//mode = 0 -> input
void pinMode(uint8_t pin, uint8_t mode){
	* (gpio + pin/10) &= ~(7<<((pin - pin/10*10)*3));
//	printf("%8x\n", * (gpio + pin/10));
	if (mode == 1){
		* (gpio + pin/10) |= 1<<((pin - pin/10*10)*3);
	}
//	printf("%x\n", 1<<(pin - pin/10*10)*3);
//	printf("%8x\n", * (gpio + pin/10));
}

void digitalWrite(uint8_t pin, uint8_t value){
	if (pin <= 53){
		if (value == 1){
			* (gpio + GPSET_OFFSET + (pin/32)) |=  1<<(pin%32);
//			printf("SET\n");
//			printf("%x\n",    (gpio + GPSET_OFFSET + (pin/32)));
//			printf("%8x\n", * (gpio + GPSET_OFFSET + (pin/32)));
		}
			
		if (value == 0){
			* (gpio + GPCLR_OFFSET + (pin/32)) |=  1<<(pin%32);
//			printf("CLR\n");
//			printf("%x\n",    (gpio + GPCLR_OFFSET + (pin/32)));
//			printf("%8x\n", * (gpio + GPCLR_OFFSET + (pin/32)));
		}
	}
}

void display(gsl_matrix* data){
	
	while(1){
		puts("Ok");
		for (int row = 0; row < 16; row++){
			for (int column = 0; column < 64; column++){
//				digitalWrite(R1, 1);
//				digitalWrite(G1, 0);
//				digitalWrite(B1, 1);
//				
//				digitalWrite(R2, 1);
//				digitalWrite(G2, 0);
//				digitalWrite(B2, 1);
//				
//				digitalWrite(CLK, 0);
//				digitalWrite(CLK, 1);
//				digitalWrite(CLK, 0);
			}
			puts("Sleep");
			sleep(1);
			
//			digitalWrite(LAT, 0);
//			digitalWrite(OE, 0);
//			
//			digitalWrite(ADD_A, 1 && (row>>0));
//			digitalWrite(ADD_B, 1 && (row>>1));
//			digitalWrite(ADD_C, 1 && (row>>2));
//			digitalWrite(ADD_D, 1 && (row>>3));
//			
//			digitalWrite(OE, 1);
//			digitalWrite(LAT, 0);
			
		}
	}
}

void LedMatrixDriver_init(void){
	setup_io();
	
	pinMode(R1, 1);
	pinMode(G1, 1);
	pinMode(B1, 1);
	pinMode(R2, 1);
	pinMode(G2, 1);
	pinMode(B2, 1);
	
	pinMode(OE, 1);
	pinMode(CLK, 1);
	pinMode(LAT, 1);
	
	pinMode(ADD_A, 1);
	pinMode(ADD_B, 1);
	pinMode(ADD_C, 1);
	pinMode(ADD_D, 1);
	
}


//void setup_io();

//void MatrixBuffer_init (MatrixBuffer* buf, uint8_t rows, uint8_t columns){
//		buf->data  = gsl_matrix_uint_alloc (rows, columns);
//		buf->rows = rows;
//		buf->columns = columns;
//		gsl_matrix_uint_fprintf(stdout, buf->data, "%d");
//}




