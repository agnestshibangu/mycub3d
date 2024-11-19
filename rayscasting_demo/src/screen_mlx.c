#include "../cub3d.h"

// double getTicks() {
// 	struct timeval tv;
// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0); // Returns time in milliseconds
// }

int set_screen(const char* title, t_data *data)
{
	int bpp = 24;
	int size_line;
	int endian;

	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, data->screenWidth, data->screenHeight, (char *)title);
	data->img = mlx_new_image(data->mlx, data->screenWidth, data->screenHeight);
	data->addr = mlx_get_data_addr(data->img, &bpp, &size_line, &endian);
	if (data->mlx == NULL || data->window == NULL || data->img == NULL || data->addr == NULL)
		return (0);
	return (1);
}


// void cleanup() {
// 	mlx_destroy_image(mlx_ptr, img_ptr);
// 	// mlx_destroy_window(mlx_ptr, win_ptr);
// }

void render(t_data *data) 
{
	// clearScreen();
	// cleanup();
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
