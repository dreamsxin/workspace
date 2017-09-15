#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <png.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include "MatrixGFX.h"


//gsl_matrix* openImg(const char* filename){
//
//	png_bytep* row_ptr;
//	gsl_matrix* imgMatrix;
//
//	//Ouverture fichier
//	FILE* img = fopen(filename, "rb");
//	if (img == NULL){
//		printf("Erreur");
//	}
//
//	//Verification de la signature PNG
//	unsigned char sig[8];
//	if ( fread(sig, 1, sizeof(sig), img) < 8){
//		printf("Erreur");
//		fclose(img);
//	}
//
//	if (png_sig_cmp(sig, 0, 8)){
//			printf("Erreur");
//			fclose(img);
//	}
//
//	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//	if (png == NULL) {
//		printf("Erreur");
//		fclose(img);
//	}
//
//	png_infop info = png_create_info_struct(png);
//	if (info == NULL) {
//		png_destroy_read_struct(&png, NULL, NULL);
//		printf("Erreur");
//		fclose(img);
//	}
//
//	png_init_io(png, img);
//
//	png_set_sig_bytes(png, sizeof(sig));
//
//	png_read_info(png, info);
//
//	uint8_t height = png_get_image_height(png, info);
//	uint8_t width = png_get_image_width(png, info);
//	uint8_t depth = png_get_bit_depth(png, info);
//
//	imgMatrix = gsl_matrix_alloc (height(png, info),
//	                         3 * width (png, info) );
//
//	printf("%s\nheight:%d width:%d depth:%d\n", filename, height, width, depth);
//
//	png_read_update_info(png, info);
//
//	row_ptr = (png_bytep*)malloc(sizeof(png_bytep) * height);
//	for (int y=0; y<height; y++)
//			row_ptr[y] = (png_byte*) malloc(png_get_rowbytes(png,info));
//
//	png_read_image(png, row_ptr);
//
//	for (uint16_t i = 0; i < height; i++){
//		for (int j = 0; j < width; j++){
//			for (int k = 0; k < 3; k++){
////				printf("%d ", row_ptr[i][3*j+k]);
//				gsl_matrix_set(imgMatrix, i, 3*j+k, row_ptr[i][3*j+k]);
////				printf("%f ", gsl_matrix_get(imgMatrix, i, 3*j+k));
////				printf("%d |", row_ptr[i][3*j+k]);
//			}
////			printf("\n");
//		}
//	}
//
////	gsl_matrix_uint_fprintf(stdout, imgMatrix, "%d");
//
//
//	for (int y=0; y<height; y++)
//			free(row_ptr[y]);
//	free(row_ptr);
//
//	fclose(img);
//
//	return imgMatrix;
//}





void saveImg(const gsl_matrix* data, const char* filename){

	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;

	uint16_t height = data->size1;
	uint16_t width  = data->size2;
	png_bytep row;

	char* _filename = (char*) malloc(100 * sizeof(char));
	strcpy(_filename, filename);
	strcat(_filename, ".png");
	puts(_filename);

	// Open file for writing (binary mode)
	FILE* f = fopen(_filename, "wb");
	if (f == NULL){
		fprintf(stderr, "Could not open file %s for writing\n", filename);
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		fclose(f);
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fprintf(stderr, "Could not allocate info struct\n");
		fclose(f);
	}


	png_init_io(png_ptr, f);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));


	uint16_t x, y;
	for (y=0; y<height; y++){
		for (x=0 ; x<width ; x++) {
				row[x*3    ] = ( ((uint32_t) gsl_matrix_get(data, y, x)) & 0xFF0000 ) >> 16;
				row[x*3 + 1] = ( ((uint32_t) gsl_matrix_get(data, y, x)) & 0xFF00   ) >> 8 ;
				row[x*3 + 2] = ( ((uint32_t) gsl_matrix_get(data, y, x)) & 0xFF     )      ;
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);
}



void drawLine(gsl_matrix* data, double x0, double y0, double x1, double y1){

	double tx, ty;
	double maxPoints = fmax( fabs(x0 - x1), fabs(y0 - y1));

//	printf("maxPoints:%f\n", maxPoints);
	for (double t = 0; t <= 1; t+= (1/(2*maxPoints))){
		tx = (1-t)*x0 + t*x1;
		ty = (1-t)*y0 + t*y1;
//		printf("tx:%f ty:%f t:%d\n", tx, ty, t);
		gsl_matrix_set(data, data->size2 - 1 - ty, tx, 0xFF);
	}
	gsl_matrix_set(data, data->size1 - 1 - y0, x0, 0xFF00);
	gsl_matrix_set(data, data->size1 - 1 - y1, x1, 0xFF00);
}


void drawMandelbrot(gsl_matrix* imgMatrix){

	uint16_t x, y;
	uint16_t iteration;
	uint16_t max_iteration = 255;

	for (y = 0; y < imgMatrix->size1; y++){
		for (x = 0; x < imgMatrix->size2; x++){

			gsl_complex z = gsl_complex_rect(0, 0);
			gsl_complex c = gsl_complex_rect((((double)y / imgMatrix->size1) * 2) - 1.5, (((double)x / imgMatrix->size2) * 2) - 1);
			iteration = 0;

			while (gsl_complex_abs(z) < 4 && iteration < max_iteration){

				z = gsl_complex_add(c, gsl_complex_mul(z,z));
				iteration++;
			}

			gsl_matrix_set(imgMatrix, y, x, iteration - iteration%10);
		}
	}
}
