#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>

int main(){
	int h;
	int w;
	int depth;
	int bpp;
	int clrtype;	
	png_bytep* row_ptr;
	
	
	FILE* f = fopen("output.png", "rb");
	if (f == NULL){
		printf("Erreur");
	}
	
	unsigned char sig[8];
	if ( fread(sig, 1, sizeof(sig), f) < 8){
		printf("Erreur");
		fclose(f);
	}
	
	if (png_sig_cmp(sig, 0, 8)){
			printf("Erreur");
			fclose(f);
		}
		
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png == NULL) {
		printf("Erreur");
		fclose(f);
	}

	png_infop info = png_create_info_struct(png);
	if (info == NULL) {
		png_destroy_read_struct(&png, NULL, NULL);
		printf("Erreur");
		fclose(f);
	}
	
	png_init_io(png, f);
	
	png_set_sig_bytes(png, sizeof(sig));
	
	png_read_info(png, info);
	
	h = png_get_image_height(png, info);
	w = png_get_image_width(png, info);
	depth = png_get_bit_depth(png, info);
	bpp = png_get_rowbytes(png, info);
	clrtype = png_get_color_type(png, info);
		
	printf("height:%d width:%d depth:%d\n", h, w, depth);
	printf("bpp:%d\n", bpp);
	
	png_read_update_info(png, info);
	
	row_ptr = (png_bytep*)malloc(sizeof(png_bytep) * h);
	for (int y=0; y<h; y++)
			row_ptr[y] = (png_byte*) malloc(png_get_rowbytes(png,info));
			
	png_read_image(png, row_ptr);
	
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			for (int k = 0; k < 3; k++){
				printf("%d ", row_ptr[i][3*j+k]);
			}
			printf("\n");
		}
	}
	
	
	for (int y=0; y<h; y++)
			free(row_ptr[y]);
	free(row_ptr);
	fclose(f);
		
	return 0;
}
