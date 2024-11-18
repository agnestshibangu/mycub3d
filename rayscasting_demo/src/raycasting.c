#include "../cub3d.h"

void	cast_rays_and_render(t_data *data)
{
	int x = 0;
		while (x < w) {
			double cameraX = 2 * x / (double)w - 1;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			int mapX = (int)posX; // Cast to int
			int mapY = (int)posY; // Cast to int
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

			if (rayDirX < 0) {
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			} else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}

			if (rayDirY < 0) {
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			} else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			// Perform DDA
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

				if (worldMap[mapX][mapY] > 0) {
					hit = 1;
				}
			}

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

			ColorRGB color;
			switch (worldMap[mapX][mapY]) {
				case 1: color = RGB_Red; break;
				case 2: color = RGB_Green; break;
				case 3: color = RGB_Blue; break;
				case 4: color = RGB_White; break;
				default: color = RGB_Yellow; break;
			}
			if (side == 1) {
				color.r /= 2;
				color.g /= 2;
				color.b /= 2;
			}
			verLine(x, drawStart, drawEnd, color);
			x++;
		}
}