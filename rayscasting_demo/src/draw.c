#include "../cub3d.h"

void verLine(int x, int drawStart, int drawEnd, t_data *data, int textureIndex)
{
    int y;
    int bpp = 32;  // Bits par pixel
    char *img_data = data->addr;

    y = drawStart;
    while (y < drawEnd) {
        // Récupérer le pixel à la position y dans la texture (data->wall[textureIndex])
        unsigned int pixel = data->wall[textureIndex][y - drawStart];  // Assurez-vous que l'index est correct pour la texture

        // Extraire les composants RGB
        unsigned char red = (pixel >> 16) & 0xFF;
        unsigned char green = (pixel >> 8) & 0xFF;
        unsigned char blue = pixel & 0xFF;

        // Calculer l'index de pixel dans l'image à afficher
        int pixel_index = (x + y * data->screenWidth) * (bpp / 8);

        // Affecter les couleurs RGB dans l'image de sortie
        img_data[pixel_index] = red;   // Rouge
        img_data[pixel_index + 1] = green;   // Vert
        img_data[pixel_index + 2] = blue;    // Bleu

        y++;
    }
}
// void verLine(int x, int drawStart, int drawEnd, unsigned char r, unsigned char g, unsigned char b, t_data *data)
// {
//     int y;
//     int bpp = 32;
//     char *img_data = data->addr;

//     y = drawStart;
//     while (y < drawEnd) {
//         int pixel_index = (x + y * data->screenWidth) * (bpp / 8);
//         img_data[pixel_index] = r;   // Red
//         img_data[pixel_index + 1] = g;   // Green
//         img_data[pixel_index + 2] = b;       // Blue
//         y++;
//     }

// }

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
