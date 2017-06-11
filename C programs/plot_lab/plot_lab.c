
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <png.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_vector.h>
#include "plot_lab.h"

#define SCREEN_WDTH 600
#define SCREEN_HGHT 400


int _save_matrix(char* filename, gsl_matrix_ulong* mat){
	
	printf("%s\n", filename);
	
	// Specify an output image size
	int height = mat->size1;
	int width = mat->size2;
	uint64_t color_value;
	uint8_t color_byte_red;
	uint8_t color_byte_green;
	uint8_t color_byte_blue;
	
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;
	char* title = "Image";
	
	png_bytep* buffer = (png_bytep*)malloc(sizeof(png_bytep) * height);
		for (int y=0; y<height; y++)
			buffer[y] = (png_byte*) malloc(3 * width * sizeof(png_byte));
				
	for (int i=0; i<mat->size1; i++){
		for (int j=0; j<mat->size2; j++){
			color_value = gsl_matrix_ulong_get(mat, i, j);
			buffer[i][3*j    ] = (png_byte) (color_value >> 16) & 0xFF;
			buffer[i][3*j + 1] = (png_byte) (color_value >>  8) & 0xFF;
			buffer[i][3*j + 2] = (png_byte) (color_value      ) & 0xFF;
//			printf("%3.0hhu", buffer[i][j]);
		}
//		printf("\n");
	}
	
	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		goto finalise;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);


	// Write image data
	int x;
	for (int y=0 ; y<height ; y++) {
		png_write_row(png_ptr, buffer[y]);
	}

	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	
	return 0;
}

uint8_t _rescale_plot_value(gsl_vector_ulong* _dst_val, gsl_vector* _src_val, double _min_value, double _max_value){
	
	double _alpha = (_max_value - _min_value) / (gsl_vector_max(_src_val) - gsl_vector_min(_src_val));
	double _beta  = _min_value - _alpha*gsl_vector_min(_src_val);
	
	gsl_vector* _dst_double_val = gsl_vector_alloc(_src_val->size);
	
	gsl_vector_memcpy(_dst_double_val, _src_val);
	
	gsl_vector_scale(_dst_double_val, _alpha);
	gsl_vector_add_constant(_dst_double_val, _beta);
	
	for (uint32_t i=0; i<_dst_double_val->size; i++){
		gsl_vector_ulong_set(_dst_val, i, gsl_vector_get(_dst_double_val, i));
	}
	
	return 0;
}

uint8_t plot(gsl_vector* x_array, gsl_vector* y_array){
	
	gsl_vector_ulong* _x_val = gsl_vector_ulong_alloc(x_array->size);
	gsl_vector_ulong* _y_val = gsl_vector_ulong_alloc(y_array->size);
	
	_rescale_plot_value(_x_val, x_array, 0, SCREEN_WDTH-1);
	_rescale_plot_value(_y_val, y_array, 0, SCREEN_HGHT-1);
	
	gsl_matrix_ulong* buffer = gsl_matrix_ulong_alloc (SCREEN_HGHT, SCREEN_WDTH);
	gsl_matrix_ulong_set_all(buffer, 0x000000);
	
	
	
	for (uint32_t i=0; i<_x_val->size; i++){
//			printf("%Lf %Lf\n", gsl_vector_long_double_get(y_array, i), gsl_vector_long_double_get(x_array, i));
			draw_pixel(buffer, gsl_vector_ulong_get(_x_val, i), gsl_vector_ulong_get(_y_val, i), 0xFFFFFF);
	}
	
//	for (uint32_t i=0; i<_x_val->size-2; i++){
//			draw_line(buffer, gsl_vector_ulong_get(_x_val, i),   gsl_vector_ulong_get(_y_val, i),
//												gsl_vector_ulong_get(_x_val, i+1), gsl_vector_ulong_get(_y_val, i+1), 0xFFFFFF);
//	}

//	draw_line(buffer, gsl_vector_ulong_get(_x_val, 10),   gsl_vector_ulong_get(_y_val, 10),
//										gsl_vector_ulong_get(_x_val, 11), gsl_vector_ulong_get(_y_val, 11), 0xFFFFFF);
//	draw_line(buffer, 0 , 0, SCREEN_WDTH/2, SCREEN_HGHT/2, 0xFFFFFF);
																																
	_save_matrix("img.png", buffer);
	gsl_matrix_ulong_free(buffer);
	
	return 0;
}

uint8_t draw_pixel(gsl_matrix_ulong * buffer, uint32_t x, uint32_t y, uint32_t color){
	
	gsl_matrix_ulong_set(buffer, (buffer->size1 - 1) - y, x, color);
	
	return 0;
}

uint8_t draw_line(gsl_matrix_ulong * buffer, const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1, const uint32_t color){
	
	double dy = ((double)y1 - y0) / (x1 - x0);
	double x_unit_var = (x1 - x0) / fabs((double)x1 - x0);
	double y = y0;
	
	for (long long x=x0; x!=x1; x += x_unit_var){
		draw_pixel(buffer, x, y, color);
		y += dy;
	}
	return 0;
}



int draw_sinus(){
	
	printf("Computing...\n");
	gsl_matrix_ulong * m = gsl_matrix_ulong_alloc (1000, 1000);
	gsl_matrix_ulong_set_all(m, 0xFFFFFF);
	
	for (double j=0; j<m->size2; j++){
			
			gsl_matrix_ulong_set(m, 0.5*(sin(2 * M_PI * 4 * (j / m->size2)) + 1)*(m->size1-1), j, 0x000000);
			printf("sin(%f) %f\n", j, 0.5*(sin(2 * M_PI * 4 * (j / m->size2)) + 1)*(m->size1-1));
			
	}
	
	_save_matrix("img.png", m);
	
	return 0;
}



