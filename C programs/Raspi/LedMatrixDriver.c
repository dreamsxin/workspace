#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
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


void pinMode(uint8_t pin, uint8_t mode){

	//Input Mode
	* (gpio + (pin/10)) &= ~(7 << (( pin%10) * 3));

	//Ouput Mode
	if (mode == ouputMode){
		* (gpio + (pin/10)) |= (1 << ((pin%10) * 3));
	}
}

void digitalWrite(uint8_t pin, uint8_t value){
	if (pin <= 53){

		if (value == 0){
			* (gpio + GPCLR_OFFSET + (pin/32)) =  1<<(pin%32);
		}

		else{
			* (gpio + GPSET_OFFSET + (pin/32)) =  1<<(pin%32);
		}
	}
}

void display(gsl_matrix* data){

	uint8_t row, column;
	uint8_t bitPos;
	uint8_t bitDepth = 8;

	uint8_t R, G, B;

	while(1){

		for (row = 0; row < 16; row++){
			for (bitPos = 0; bitPos < bitDepth; bitPos++){
				for (column = 0; column < 64; column++){

					digitalWrite(CLK, 0);

					R = ( (uint32_t) gsl_matrix_get(data, row, column) & 0xFF0000 ) >> 16;
					G = ( (uint32_t) gsl_matrix_get(data, row, column) & 0x00FF00 ) >>  8;
					B = ( (uint32_t) gsl_matrix_get(data, row, column) & 0x0000FF )      ;

					digitalWrite(R1, (R >> bitPos) & 0x1);
					digitalWrite(G1, (G >> bitPos) & 0x1);
					digitalWrite(B1, (B >> bitPos) & 0x1);

					R = ( (uint32_t) gsl_matrix_get(data, row+16, column) & 0xFF0000 ) >> 16;
					G = ( (uint32_t) gsl_matrix_get(data, row+16, column) & 0x00FF00 ) >>  8;
					B = ( (uint32_t) gsl_matrix_get(data, row+16, column) & 0x0000FF )      ;

					digitalWrite(R2, (R >> bitPos) & 0x1);
					digitalWrite(G2, (G >> bitPos) & 0x1);
					digitalWrite(B2, (B >> bitPos) & 0x1);

					digitalWrite(CLK, HIGH);
				}

				digitalWrite(OE, HIGH);

				digitalWrite(ADD_A, (row & 0x1)     );
				digitalWrite(ADD_B, (row & 0x2) >> 1);
				digitalWrite(ADD_C, (row & 0x4) >> 2);
				digitalWrite(ADD_D, (row & 0x8) >> 3);

				digitalWrite(LAT, HIGH);
				digitalWrite(LAT, LOW);

				digitalWrite(OE, LOW);

				for (uint32_t i = 0; i < pow(2, bitPos)*3; i++){}

				// sleep(1);

			}
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
