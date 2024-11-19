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
// // }

// void verLine(int x, int drawStart, int drawEnd, ColorRGB color, int image_width, t_data data)
// void verLine(int x, int drawStart, int drawEnd, ColorRGB color, t_data *data)
// {
    
// 	int bpp = 24;
// 	char *img_data = data->addr;

//     for (int y = drawStart; y < drawEnd; y++) {
//         int pixel_index = (x + y * data->screenWidth) * (bpp / 8);
// 		//int pixel_index = (x + y * image_width) * (bpp / 8);
//         img_data[pixel_index] = color.b; // Blue
//         img_data[pixel_index + 1] = color.g; // Green
//         img_data[pixel_index + 2] = color.r; // Red
//     }
// }


void verLine(int x, int drawStart, int drawEnd, unsigned char r, unsigned char g, unsigned char b, t_data *data)
{
    int bpp = 24;
    char *img_data = data->addr;

    for (int y = drawStart; y < drawEnd; y++) {
        int pixel_index = (x + y * data->screenWidth) * (bpp / 8);
        img_data[pixel_index] = b;       // Blue
        img_data[pixel_index + 1] = g;   // Green
        img_data[pixel_index + 2] = r;   // Red
    }
}
