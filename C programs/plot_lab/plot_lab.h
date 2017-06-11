#ifndef PLOT_LAB
#define PLOT_LAB

int     _save_matrix(char* filename, gsl_matrix_ulong* mat);
uint8_t _rescale_plot_value(gsl_vector_ulong* _dst_val, gsl_vector* _src_val, double _min_value, double _max_value);
uint8_t plot(gsl_vector* x_array, gsl_vector* y_array);
uint8_t draw_pixel(gsl_matrix_ulong * buffer, uint32_t x, uint32_t y, uint32_t color);
uint8_t draw_line(gsl_matrix_ulong * buffer, const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1, const uint32_t color);
int     draw_sinus();


#endif
