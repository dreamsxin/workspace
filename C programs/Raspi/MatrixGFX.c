#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <png.h>
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

uint8_t saveImg(const gsl_matrix* data, const char* filename){
	
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	
	uint16_t height = data->size1;
	uint16_t width  = data->size2;	
	png_bytep row;
	
	char* _filename = (char*) malloc(100 * sizeof(char));
	strcpy(_filename, filename);
	strcat(_filename, ".png");
	puts(_filename);
	
	FILE* f = fopen(_filename, "wb");
	if (f == NULL){
		printf("Erreur");
	}
	puts("ok1");
		
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		fclose(f);
	}
	
	puts("ok2");
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fprintf(stderr, "Could not allocate info struct\n");
		fclose(f);
	}
	
	puts("ok3");

	png_init_io(png_ptr, f);
	
	puts("ok4");
	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
			
	puts("ok5");
	png_text title_text;
	title_text.compression = PNG_TEXT_COMPRESSION_NONE;
	title_text.key = "Title";
	title_text.text = "title";
	png_set_text(png_ptr, info_ptr, &title_text, 1);
	png_write_info(png_ptr, info_ptr);
	
	puts("ok6");
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));
	
	puts("ok6");

	uint16_t x, y;
	for (y=0; y<height; y++){
		for (x=0 ; x<width ; x++) {
				printf("%d %d\n", y, x);
				row[x*3    ] = ( (uint32_t) gsl_matrix_get(data, y, x) & 0xFF0000 ) >> 16;
				row[x*3 + 1] = ( (uint32_t) gsl_matrix_get(data, y, x) & 0xFF00   ) >> 8 ; 
				row[x*3 + 2] = ( (uint32_t) gsl_matrix_get(data, y, x) & 0xFF     )      ;
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);
	
	return 1;
}









