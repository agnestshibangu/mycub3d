#include "../cub3d.h"

void move_up(t_data *data, double moveSpeed)
{
    if (data->worldMap[(int)(data->posX + data->dirX * moveSpeed)][(int)(data->posY)] == 0) {
		printf ("%f\n", data->posX);
        data->posX += data->dirX * moveSpeed;
		printf ("%f\n", data->posX);
    }
    if (data->worldMap[(int)(data->posX)][(int)(data->posY + data->dirY * moveSpeed)] == 0) {
		data->posY += data->dirY * moveSpeed;
    }
}

void move_down(t_data *data, double moveSpeed)
{
    if (data->worldMap[(int)(data->posX - data->dirX * moveSpeed)][(int)(data->posY)] == 0) {
        data->posX -= data->dirX * moveSpeed;
    }
    if (data->worldMap[(int)(data->posX)][(int)(data->posY - data->dirY * moveSpeed)] == 0) {
        data->posY -= data->dirY * moveSpeed;
    }
}

void rotate(t_data *data, double rotSpeed, int direction) {
    double oldDirX = data->dirX;
    double oldPlaneX = data->planeX;

    data->dirX = data->dirX * cos(rotSpeed * direction) - data->dirY * sin(rotSpeed * direction);
    data->dirY = oldDirX * sin(rotSpeed * direction) + data->dirY * cos(rotSpeed * direction);

    data->planeX = data->planeX * cos(rotSpeed * direction) - data->planeY * sin(rotSpeed * direction);
    data->planeY = oldPlaneX * sin(rotSpeed * direction) + data->planeY * cos(rotSpeed * direction);
}

