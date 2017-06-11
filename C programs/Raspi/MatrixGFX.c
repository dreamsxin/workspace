#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <png.h>
#include "MatrixGFX.h"


gsl_matrix* openImg(const char* filename){
	
	png_bytep* row_ptr;
	gsl_matrix* imgMatrix; 
	
	FILE* img = fopen(filename, "rb");
	if (img == NULL){
		printf("Erreur");
	}
	
	unsigned char sig[8];
	if ( fread(sig, 1, sizeof(sig), img) < 8){
		printf("Erreur");
		fclose(img);
	}
	
	if (png_sig_cmp(sig, 0, 8)){
			printf("Erreur");
			fclose(img);
		}
		
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png == NULL) {
		printf("Erreur");
		fclose(img);
	}

	png_infop info = png_create_info_struct(png);
	if (info == NULL) {
		png_destroy_read_struct(&png, NULL, NULL);
		printf("Erreur");
		fclose(img);
	}
	
	png_init_io(png, img);
	
	png_set_sig_bytes(png, sizeof(sig));
	
	png_read_info(png, info);
	
	uint8_t height = png_get_image_height(png, info);
	uint8_t width = png_get_image_width(png, info);
	uint8_t depth = png_get_bit_depth(png, info);
	
	imgMatrix = gsl_matrix_alloc (png_get_image_height(png, info),
	                         3 * png_get_image_width (png, info) );
	
	printf("%s\nheight:%d width:%d depth:%d\n", filename, height, width, depth);
	
	png_read_update_info(png, info);
		
	row_ptr = (png_bytep*)malloc(sizeof(png_bytep) * height);
	for (int y=0; y<height; y++)
			row_ptr[y] = (png_byte*) malloc(png_get_rowbytes(png,info));
			
	png_read_image(png, row_ptr);
	
	for (uint16_t i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			for (int k = 0; k < 3; k++){
//				printf("%d ", row_ptr[i][3*j+k]);
				gsl_matrix_set(imgMatrix, i, 3*j+k, row_ptr[i][3*j+k]);
//				printf("%f ", gsl_matrix_get(imgMatrix, i, 3*j+k));
//				printf("%d |", row_ptr[i][3*j+k]);
			}
//			printf("\n");
		}
	}
	
//	gsl_matrix_uint_fprintf(stdout, imgMatrix, "%d");
	
	
	for (int y=0; y<height; y++)
			free(row_ptr[y]);
	free(row_ptr);
	
	fclose(img);
	
	return imgMatrix;
}