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

//mode = 1 -> Output
//mode = 0 -> input
void pinMode(uint8_t pin, uint8_t mode){
	// uint32_t offset = (pin / 10) * 0x4;
	// printf("%8x", offset);
	* (gpio + (pin/10)) &= ~(7 << (( pin%10) * 3));
	// printf("%8x\n", * (gpio + pin/10));
	if (mode == ouputMode){
		* (gpio + (pin/10)) |= (1 << ((pin%10) * 3));
	}
//	printf("%x\n", 1<<(pin - pin/10*10)*3);
//	printf("%8x\n", * (gpio + pin/10));
}

void digitalWrite(uint8_t pin, uint8_t value){
	if (pin <= 53){
		if (value == 0){
			* (gpio + GPCLR_OFFSET + (pin/32)) =  1<<(pin%32);
//			printf("CLR\n");
//			printf("%x\n",    (gpio + GPCLR_OFFSET + (pin/32)));
//			printf("%8x\n", * (gpio + GPCLR_OFFSET + (pin/32)));
		}

		else{
			* (gpio + GPSET_OFFSET + (pin/32)) =  1<<(pin%32);
//			printf("SET\n");
//			printf("%x\n",    (gpio + GPSET_OFFSET + (pin/32)));
//			printf("%8x\n", * (gpio + GPSET_OFFSET + (pin/32)));
		}
	}
}

void display(gsl_matrix* data){

	uint8_t row, column;
	uint8_t val = 2;

	printf("%8x %8x\n", (gpio + 0), * (gpio + 0));
	printf("%8x %8x\n", (gpio + 1), * (gpio + 1));
	printf("%8x %8x\n", (gpio + 2), * (gpio + 2));


	while(1){
		puts("Ok");
		for (row = 0; row < 16; row++){
			for (column = 0; column < 64; column++){

				digitalWrite(CLK, 0);

				digitalWrite(R1, 1);
				digitalWrite(G1, 0);
				digitalWrite(B1, 1);

				digitalWrite(R2, 1);
				digitalWrite(G2, 0);
				digitalWrite(B2, 1);

				digitalWrite(CLK, 1);
			}


			digitalWrite(OE, 1);

			digitalWrite(ADD_A, (row & 0x1)     );
			digitalWrite(ADD_B, (row & 0x2) >> 1);
			digitalWrite(ADD_C, (row & 0x4) >> 2);
			digitalWrite(ADD_D, (row & 0x8) >> 3);
	
			digitalWrite(LAT, 1);
			digitalWrite(LAT, 0);

			digitalWrite(OE, 0);

			printf("%d %d %d %d %d\n", row, (row & 0x1) >> 0, (row & 0x2) >> 1, (row & 0x4) >> 2, (row & 0x8) >> 3);
			puts("Sleep");

			sleep(1);

		}
	}
}

void LedMatrixDriver_init(void){
	setup_io();

	pinMode(R1, ouputMode);
	pinMode(G1, ouputMode);
	pinMode(B1, ouputMode);
	pinMode(R2, ouputMode);
	pinMode(G2, ouputMode);
	pinMode(B2, ouputMode);

	pinMode(OE,  ouputMode);
	pinMode(CLK, ouputMode);
	pinMode(LAT, ouputMode);

	pinMode(ADD_A, ouputMode);
	pinMode(ADD_B, ouputMode);
	pinMode(ADD_C, ouputMode);
	pinMode(ADD_D, ouputMode);

}


//void setup_io();

//void MatrixBuffer_init (MatrixBuffer* buf, uint8_t rows, uint8_t columns){
//		buf->data  = gsl_matrix_uint_alloc (rows, columns);
//		buf->rows = rows;
//		buf->columns = columns;
//		gsl_matrix_uint_fprintf(stdout, buf->data, "%d");
//}

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
