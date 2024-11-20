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
	{
		printf ("D\n");
		rotate(data, 0.1, -1); 
	}
	else if (keysym == XK_a)
	{
		printf ("A\n");
		rotate(data, 0.1, 1);
	}
	else if (keysym == XK_w)
	{
		printf ("W\n");
		move_up(data, 0.1);
	}
	else if (keysym == XK_s)
	{
		printf ("S\n");
		move_down(data, 0.1);
	}
	else if (keysym == XK_Escape)
	{
		close_window(data);
	}
	cast_rays_and_render(data);
	return (1);
}

void	event_handler(t_data *data)
{
	mlx_key_hook(data->window, controls_working, data);
	
	// mlx_key_hook(data->window, 2, 1L << 0, controls_working, data);
	mlx_hook(data->window, 17, 0, close_window,  data);
	mlx_loop(data->mlx);
}

// void	event_handler(t_data *data)
// {
// 	cast_rays_and_render(data);
// 	mlx_hook(data->window, 2, 1L << 0, rerendering, data);
// 	mlx_hook(data->window, 17, 0, close_window,  data);
// }