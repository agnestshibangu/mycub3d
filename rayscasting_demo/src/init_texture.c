#include "../cub3d.h"

void init_images_walls(t_data *data, int i)
{
	void *img;
	int width, height;

    data->texture[i].path = "./assets/img1.xpm";
	data->texture[i].bits_per_pixels = 32;
	data->texture[i].endian = 0;
    img = mlx_xpm_file_to_image(data->mlx, data->texture[i].path, &width, &height);
    if (!img) {
        printf("Failed to load image\n");
    }
	data->texture[i].width = width;
	data->texture[i].height = height;
	data->texture[i].line_length = data->texture[i].width * (data->texture[i].bits_per_pixels / 8);
    data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->texture[i].path,
    	&(data->texture[i].width), &(data->texture[i].height));
    data->texture[i].addr = (unsigned int *)mlx_get_data_addr(data->texture[i].img, &(data->texture[i].bits_per_pixels),
    	&(data->texture[i].line_length), &(data->texture[i].endian));
}

void allocate_wall(t_data *data) {
    int i = 0;

    data->wall = malloc(sizeof(unsigned int *));
    if (data->wall == NULL) {
        printf("Memory allocation failed for wall array!\n");
        return;
    }
    int num_pixels = data->texture[i].width * data->texture[i].height;
	printf("num pixels %d\n", num_pixels);
    data->wall[i] = (unsigned int *)malloc(num_pixels * sizeof(unsigned int));
    if (data->wall[i] == NULL) {
        printf("Memory allocation failed for wall[%d]!\n", i);
        return;
    }
    printf("Memory allocation OK\n");
}

void printAllPixels(t_data *data, int i) {
    unsigned int *addr = data->texture[i].addr;
    int width = data->texture[i].width;
    int height = data->texture[i].height;
    unsigned int text_i = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned int pixel = addr[y * width + x];
            
            unsigned char red = (pixel >> 16) & 0xFF;
            unsigned char green = (pixel >> 8) & 0xFF;
            unsigned char blue = pixel & 0xFF;
            unsigned int packedPixel = (red << 16) | (green << 8) | blue;

            data->wall[i][text_i] = packedPixel;
            text_i++;
        }
    }
}

void init_texture(t_data *data)
{
    int i;

	i = 0;
    // while (i < 4)
	// {
	init_images_walls(data, i);
	allocate_wall(data);
	printAllPixels(data, i);
	//mlx_destroy_image(data->mlx, data->texture[i].img);
	// 	i++;
	// }
}
