
#include "../cub3d.h"

int main(int ac, char **av)
{
	(void)av;
	(void)ac;
	t_data *data;

	// int worldMap[24][24]; 

	// double time = 0;
	// double oldTime = 0;
	//screen(screenWidth, screenHeight, 0, "Raycaster");

	const char *title = "raycast";

	data = NULL;
	data = malloc(1 * sizeof(t_data)); 
	if (data) 
		printf("data okay\n"); 
	if (init_param(data))
		printf("init param okay\n"); 
	if (set_screen(title, data))
		printf("setting screen okay\n");
	init_texture(data);
	printf("init texture okay\n");
	cast_rays_and_render(data);
	event_handler(data);
	mlx_loop(data->mlx);
	// //cleanup();
	return (0);
}
