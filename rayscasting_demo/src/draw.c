#include "../cub3d.h"


void verLine(int x, int drawStart, int drawEnd, unsigned char r, unsigned char g, unsigned char b, t_data *data)
{
    int bpp = 32;
    char *img_data = data->addr;

    for (int y = drawStart; y < drawEnd; y++) {
        int pixel_index = (x + y * data->screenWidth) * (bpp / 8);
        img_data[pixel_index] = r;   // Red
        img_data[pixel_index + 1] = g;   // Green
        img_data[pixel_index + 2] = b;       // Blue
    }
}
