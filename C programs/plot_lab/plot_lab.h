#ifndef PLOT_LAB
#define PLOT_LAB

int     _save_matrix(char* filename, gsl_matrix_ulong* mat);
uint8_t _rescale_plot_value(gsl_vector* _dst_val, gsl_vector* _src_val, double _min_value, double _max_value);
uint8_t plot(gsl_vector* x_array, gsl_vector* y_array);
uint8_t draw_pixel(gsl_matrix_ulong * buffer, uint32_t x, uint32_t y, uint32_t color);
uint8_t draw_line(gsl_matrix_ulong * buffer, double x0, double y0, double x1, double y1, uint32_t color, uint8_t thickness);
int     draw_sinus();


#endif
