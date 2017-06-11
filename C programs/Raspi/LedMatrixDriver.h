#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

#define GPIFSEL_OFFSET           0
#define GPSET_OFFSET             7
#define GPCLR_OFFSET             10


//
//
//// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
//#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
//#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
//#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
//
//#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
//#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
//
//#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
//
//#define GPIO_PULL *(gpio+37) // Pull up/pull down
//#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

//Matrix color pins
#define R1 5
#define G1 13
#define B1 6
#define R2 12
#define G2 16
#define B2 23

//Matrix adrress pins
#define ADD_A 22
#define ADD_B 26
#define ADD_C 27
#define ADD_D 20

//Matrix control pins
#define OE  4
#define CLK 17
#define LAT 21

//pinMode
#define inputMode 0
#define ouputMode 1

#include <stdint.h>
#include <gsl/gsl_matrix.h>


typedef struct MatrixBuffer_struct{
	uint8_t rows;
	uint8_t columns;
	gsl_matrix_uint* data;

}MatrixBuffer;


//void MatrixBuffer_init (MatrixBuffer* buf, uint8_t rows, uint8_t columns);
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
void display(gsl_matrix* data);
void setup_io();


