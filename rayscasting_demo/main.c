
#include "cub3d.h"

int main(int ac, char **av)
{
	(void)av;
	(void)ac;
	t_data *data;

	// ColorRGB RGB_Red = {255, 105, 180};
	// ColorRGB RGB_Green = {255, 105, 180};
	// ColorRGB RGB_Blue = {255, 105, 180};
	// ColorRGB RGB_White = {255, 105, 180};
	// ColorRGB RGB_Yellow = {255, 105, 180};

	// void *mlx_ptr;
	// void *win_ptr;
	// void *img_ptr; // For the image buffer
	// char *img_data; // Pointer to the image data
	// int bpp; // Bits per pixel
	// int size_line; // Size of a line in bytes
	// int endian; // Endianness

	int worldMap[24][24]; 

	//double posX = 22;
	// double posY = 12;
	// double dirX = -1;
	// double dirY = 0;
	// double planeX = 0;
	// double planeY = 0.66;
	// double time = 0;
	// double oldTime = 0;
	//screen(screenWidth, screenHeight, 0, "Raycaster");

	print_ok();
	data = NULL; // 
	data = malloc(1 * sizeof(t_data)); // 
	if (!data) // 
		printf("error memory alloc failed for data"); // 
	// init param();
	// set_screen(data);
	// cast_rays_and_render(data);
	// event_handler(data);
	// mlx_loop(data->mlx);
	// //cleanup();
	return (0);
}
