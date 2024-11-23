#include "../cub3d.h"

void verLine(int x, int drawStart, int drawEnd, unsigned char r, unsigned char g, unsigned char b, t_data *data)
{
    int y;
    int bpp = 32;
    char *img_data = data->addr;

    y = drawStart;
    while (y < drawEnd) {
        int pixel_index = (x + y * data->screenWidth) * (bpp / 8);
        img_data[pixel_index] = r;   // Red
        img_data[pixel_index + 1] = g;   // Green
        img_data[pixel_index + 2] = b;       // Blue
        y++;
    }

}

void draw_ceiling(int x, int drawStart, t_data *data)
{
    int y;
    int bpp = 32;
    char *img_data = data->addr;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    r = 0;  
    g = 255; 
    b = 0;

    y = 0;
    while (y < drawStart)
    {
        int pixel_index = (x + y * data->screenWidth) * (bpp / 8);
        img_data[pixel_index] = r;   // Red
        img_data[pixel_index + 1] = g;   // Green
        img_data[pixel_index + 2] = b;       // Blue
        y++;
    }
}


void draw_floor(int x, int drawEnd, t_data *data)
{
    int y;
    int bpp = 32;
    char *img_data = data->addr;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    r = 0;  
    g = 255; 
    b = 0;

    y = drawEnd;
    while (y < data->screenHeight)
    {
        int pixel_index = (x + y * data->screenWidth) * (bpp / 8);
        img_data[pixel_index] = r;   // Red
        img_data[pixel_index + 1] = g;   // Green
        img_data[pixel_index + 2] = b;       // Blue
        y++;
    }
}
