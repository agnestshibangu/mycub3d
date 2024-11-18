#include "../cub3d.h"

void move_up(double *posX, double *posY, double dirX, double dirY, double moveSpeed) {
	if (worldMap[(int)(*posX + dirX * moveSpeed)][(int)(*posY)] == 0) {
		*posX += dirX * moveSpeed;
	}
	if (worldMap[(int)(*posX)][(int)(*posY + dirY * moveSpeed)] == 0) {
		*posY += dirY * moveSpeed;
	}
}

void move_down(double *posX, double *posY, double dirX, double dirY, double moveSpeed) {
	if (worldMap[(int)(*posX - dirX * moveSpeed)][(int)(*posY)] == 0) {
		*posX -= dirX * moveSpeed;
	}
	if (worldMap[(int)(*posX)][(int)(*posY - dirY * moveSpeed)] == 0) {
		*posY -= dirY * moveSpeed;
	}
}

void rotate(double *dirX, double *dirY, double *planeX, double *planeY, double rotSpeed, int direction) {
	double oldDirX = *dirX;
	double oldPlaneX = *planeX;

	*dirX = *dirX * cos(rotSpeed * direction) - *dirY * sin(rotSpeed * direction);
	*dirY = oldDirX * sin(rotSpeed * direction) + *dirY * cos(rotSpeed * direction);

	*planeX = *planeX * cos(rotSpeed * direction) - *planeY * sin(rotSpeed * direction);
	*planeY = oldPlaneX * sin(rotSpeed * direction) + *planeY * cos(rotSpeed * direction);
}

void key_press()
{
	XEvent event;
	while (XPending(mlx_ptr)) {
	XNextEvent(mlx_ptr, &event);
		if (event.type == KeyPress) {
			int keysym = XLookupKeysym(&event.xkey, 0);
			if (keysym == XK_w) {
				move_up(&posX, &posY, dirX, dirY, 0.1);
			} 
			else if (keysym == XK_s) {
				move_down(&posX, &posY, dirX, dirY, 0.1);
			} 
			else if (keysym == XK_d) {
				rotate(&dirX, &dirY, &planeX, &planeY, 0.1, -1); 
			} 
			else if (keysym == XK_a) {
				rotate(&dirX, &dirY, &planeX, &planeY, 0.1, 1);
			} 
			else if (keysym == XK_Escape) {
				cleanup();
				return 0;
			}
		}
	}
}

int rerendering(int keycode, )
{
	
	key_press(keycode);
	cast_rays_and_render();
	return (0);
}

void	event_handler(t_param *param)
{
	mlx_hook(param->window, 2, 1L << 0, rerendering, param);
	mlx_hook(param->window, 17, 0, close_window, param);
}