#include "../cub3d.h"

// double getTicks() {
// 	struct timeval tv;
// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0); // Returns time in milliseconds
// }

void screen(int width, int height, int flags, const char* title)
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, height, (char *)title);
	img_ptr = mlx_new_image(mlx_ptr, width, height);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
}


void cleanup() {
	mlx_destroy_image(mlx_ptr, img_ptr);
	// mlx_destroy_window(mlx_ptr, win_ptr);
}

void render() {
	// clearScreen();
	// cleanup();
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
}
