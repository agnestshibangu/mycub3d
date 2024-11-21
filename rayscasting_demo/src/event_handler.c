#include "../cub3d.h"


int close_window(t_data *data)
{
    printf("ESC");    
	mlx_destroy_window(data->mlx, data->window);
    return (0);
}


int	controls_working(int keysym, t_data *data)
{
	if (keysym == XK_d)
		rotate(data, 0.1, -1); 
	else if (keysym == XK_a)
		rotate(data, 0.1, 1);
	else if (keysym == XK_w)
		move_up(data, 0.1);
	else if (keysym == XK_s)
		move_down(data, 0.1);
	else if (keysym == XK_Escape)
		close_window(data);
	return (1);
}

int rerendering(int keysym, t_data *data)
{
	ft_bzero(data->addr, data->screenWidth * data->screenHeight * sizeof(int));
	controls_working(keysym, data);
	cast_rays_and_render(data);
	return (0);

}

void	event_handler(t_data *data)
{
	mlx_key_hook(data->window, rerendering, data);
	mlx_hook(data->window, 17, 0, close_window,  data);
}