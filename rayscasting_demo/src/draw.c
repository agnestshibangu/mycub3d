#include "../cub3d.h"

void verLine(int x, int drawStart, int drawEnd, t_data *data, int textureIndex)
{
    int y;
	int x;
    int bpp = 32;  // Bits per pixel
    char *img_data = data->addr;
    
    // Get the texture height and width
    // int textureWidth = data->texture[textureIndex].width;
    // int textureHeight = data->texture[textureIndex].height;

	while ()
    
    // Loop through each pixel in the vertical line (y from drawStart to drawEnd)
    for (y = drawStart; y < drawEnd; y++) {
     
        
        // Get the pixel color from the texture
        // unsigned int pixel = data->texture[textureIndex].pixels[textureY * textureWidth + textureX];
		unsigned int pixel = data->wall[textureIndex][y - drawStart];  // Assurez-vous que l'index est correct pour la texture
        // Extract RGB components
        unsigned char red = (pixel >> 16) & 0xFF;
        unsigned char green = (pixel >> 8) & 0xFF;
        unsigned char blue = pixel & 0xFF;

        // Calculate the pixel index in the final image (screen)
        int pixel_index = (x + y * data->screenWidth) * (bpp / 8);

        // Set the pixel colors in the image data (screen buffer)
        img_data[pixel_index] = red;      // Red
        img_data[pixel_index + 1] = green; // Green
        img_data[pixel_index + 2] = blue;  // Blue
    }
}


// void verLine(int x, int drawStart, int drawEnd, t_data *data, int textureIndex)
// {
//     int y;
//     int bpp = 32;  // Bits par pixel
//     char *img_data = data->addr;

//     y = drawStart;
//     while (y < drawEnd) {
//         unsigned int pixel = data->wall[textureIndex][y - drawStart];  // Assurez-vous que l'index est correct pour la texture

//         // Extraire les composants RGB
//         unsigned char red = (pixel >> 16) & 0xFF;
//         unsigned char green = (pixel >> 8) & 0xFF;
//         unsigned char blue = pixel & 0xFF;

//         // Calculer l'index de pixel dans l'image à afficher
//         int pixel_index = (x + y * data->screenWidth) * (bpp / 8);

//         // Affecter les couleurs RGB dans l'image de sortie
//         img_data[pixel_index] = red;   // Rouge
//         img_data[pixel_index + 1] = green;   // Vert
//         img_data[pixel_index + 2] = blue;    // Bleu

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
