#include "../cub3d.h"

int close_window(t_data *data)
{
    printf("ESC\n");
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode < 256)
        data->keys[keycode] = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode < 256)
        data->keys[keycode] = 0; 
    return (0);
}

int handle_events(t_data *data)
{
    if (data->keys[XK_w])
        move_up(data, 0.1);
    if (data->keys[XK_s])
        move_down(data, 0.1);
    if (data->keys[XK_a])
        rotate(data, 0.01, 1);
    if (data->keys[XK_d])
        rotate(data, 0.01, -1);
    ft_bzero(data->addr, data->screenWidth * data->screenHeight * sizeof(int));
    cast_rays_and_render(data);

    return (0);
}

void event_handler(t_data *data)
{
    mlx_hook(data->window, KeyPress, KeyPressMask, key_press, data);
    mlx_hook(data->window, KeyRelease, KeyReleaseMask, key_release, data);
    mlx_loop_hook(data->mlx, handle_events, data);
    mlx_hook(data->window, 17, 0, close_window, data);
}
