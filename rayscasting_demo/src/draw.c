#include "../cub3d.h"

// bool	set_screen(t_data *data)
// {
// 	data->mlx = mlx_init();
// 	data->window = mlx_new_window(data->mlx, data->screenWidth, data->screenHeight, "Cub3D");
// 	data->img = mlx_new_image(data->mlx, data->screenWidth, data->screenHeight);
// 	// data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
// 	// 	&data->size_line, &data->endian);
// 	if (data->mlx == NULL || data->window == NULL || data->img == NULL )
// 		return (false);
// 	return (true);
// }

void verLine(int x, int drawStart, int drawEnd, ColorRGB color) {
	for (int y = drawStart; y < drawEnd; y++) {
		int pixel_index = (x * bpp / 8) + (y * size_line);
		img_data[pixel_index] = color.b; // Blue
		img_data[pixel_index + 1] = color.g; // Green
		img_data[pixel_index + 2] = color.r; // Red
	}
}