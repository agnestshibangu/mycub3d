#include "../cub3d.h"

void cast_rays_and_render(t_data *data)
{
    int w = data->screenWidth;
    int h = data->screenHeight;

	
	// 	// After initializing the values, you can add the following debug prints
	// printf("Screen Width: %d\n", data->screenWidth);
	// printf("Screen Height: %d\n", data->screenHeight);
	// printf("Player Position: (posX: %.2f, posY: %.2f)\n", data->posX, data->posY);
	// printf("Direction: (dirX: %.2f, dirY: %.2f)\n", data->dirX, data->dirY);
	// printf("Plane: (planeX: %.2f, planeY: %.2f)\n", data->planeX, data->planeY);


    int x = 0;
    while (x < w) 
    {
        double cameraX = 2 * x / (double)w - 1;  // Correction pour cameraX
        double rayDirX = data->dirX + (data->planeX) * cameraX;
        double rayDirY = data->dirY + (data->planeY) * cameraX;
        int mapX = (int)(data->posX);
        int mapY = (int)(data->posY);
        double sideDistX;
        double sideDistY;
        double deltaDistX;
        double deltaDistY;

        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist;
        int stepX;
        int stepY;
        int hit = 0;
        int side;

        // Calculer le pas et la distance
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = ((data->posX) - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - (data->posX)) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = ((data->posY) - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - (data->posY)) * deltaDistY;
        }

        // DDA
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (data->worldMap[mapX][mapY] > 0) {
                hit = 1;
            }
        }

        // Calculer la distance du mur
        if (side == 0) {
            perpWallDist = (sideDistX - deltaDistX);
        } else {
            perpWallDist = (sideDistY - deltaDistY);
        }

        int lineHeight = (int)(h / perpWallDist);
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h) {
            drawEnd = h - 1;
        }

        // Déterminer la couleur
        unsigned char r, g, b;
        switch (data->worldMap[mapX][mapY]) {
            case 1: r = 255; g = 0;   b = 0;   break; // Rouge
            case 2: r = 0;   g = 255; b = 0;   break; // Vert
            case 3: r = 0;   g = 0;   b = 255; break; // Bleu
            case 4: r = 255; g = 255; b = 255; break; // Blanc
            default: r = 255; g = 255; b = 0;   break; // Jaune
        }

        // Assombrir la couleur si le côté est 1
        if (side == 1) {
            r /= 2;
            g /= 2;
            b /= 2;
        }

        // Appeler verLine avec les composantes de couleur
        verLine(x, drawStart, drawEnd, r, g, b, data);

        x++;
    }
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}



// #include "../cub3d.h"

// void cast_rays_and_render(t_data *data)
// {
// 	unsigned char RGB_Red[] = {255, 0, 0};
//     unsigned char RGB_Green[] = {0, 255, 0};
//     unsigned char RGB_Blue[] = {0, 0, 255};
//     unsigned char RGB_White[] = {255, 255, 255};
//     unsigned char RGB_Yellow[] = {255, 255, 0};


//     int w = data->screenWidth;
//     int h = data->screenHeight;

//     int x = 0;
//     while (x < w) 
// 	{
//         double cameraX = 2 * x / (double)w - 1;  // Correcting the calculation for cameraX
//         double rayDirX = data->dirX + (data->planeX) * cameraX; // Dereference planeX
//         double rayDirY = data->dirY + (data->planeY) * cameraX; // Dereference planeY
//         int mapX = (int)(data->posX); // Dereference posX and cast to int
//         int mapY = (int)(data->posY); // Dereference posY and cast to int
//         double sideDistX;
//         double sideDistY;
//         double deltaDistX;
//         double deltaDistY;

//         deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//         deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

//         double perpWallDist;
//         int stepX;
//         int stepY;
//         int hit = 0;
//         int side;

//         if (rayDirX < 0) {
//             stepX = -1;
//             sideDistX = ((data->posX) - mapX) * deltaDistX; // Dereference posX
//         } else {
//             stepX = 1;
//             sideDistX = (mapX + 1.0 - (data->posX)) * deltaDistX; // Dereference posX
//         }

//         if (rayDirY < 0) {
//             stepY = -1;
//             sideDistY = ((data->posY) - mapY) * deltaDistY; // Dereference posY
//         } else {
//             stepY = 1;
//             sideDistY = (mapY + 1.0 - (data->posY)) * deltaDistY; // Dereference posY
//         }

//         // Perform DDA
//         while (hit == 0) {
//             if (sideDistX < sideDistY) {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//             } else {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//             }

//             if (data->worldMap[mapX][mapY] > 0) {
//                 hit = 1;
//             }
//         }

//         if (side == 0) {
//             perpWallDist = (sideDistX - deltaDistX);
//         } else {
//             perpWallDist = (sideDistY - deltaDistY);
//         }

//         int lineHeight = (int)(h / perpWallDist);
//         int drawStart = -lineHeight / 2 + h / 2;
//         if (drawStart < 0) {
//             drawStart = 0;
//         }
//         int drawEnd = lineHeight / 2 + h / 2;
//         if (drawEnd >= h) {
//             drawEnd = h - 1;
//         }


// 		unsigned char *color;
// 		switch (data->worldMap[mapX][mapY]) {
// 			case 1: color = RGB_Red; break;
// 			case 2: color = RGB_Green; break;
// 			case 3: color = RGB_Blue; break;
// 			case 4: color = RGB_White; break;
// 			default: color = RGB_Yellow; break;
// 		}

//         if (side == 1) {
//             color[0] /= 2;
//             color[1] /= 2;
//             color[2] /= 2;
//         }
// 		verLine(x, drawStart, drawEnd, data);
    

//         x++;
//     }
// }
