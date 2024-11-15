#include "../inc/cub3d.h"


int	main(int ac, char **av)
{
	t_map_data  map_data;
	
	if (ac != 2)
	{
		ft_printf("Error: wrong number of arguments\n");
        return (0);
	}
	if (!check_extension_file_name(av[1]))
    {
        ft_printf("Error: invalid file extension\n");
        return (0);
    }
	map_data.map_file = av[1];
    if (does_file_exist(map_data.map_file))
	{
		ft_printf("Error: the file does not exist\n");
        return (0);
	}

	// routine to check floodfill
	create_map_for_game(&map_data);
	display_map_data(&map_data);
	
	define_check_pos(&map_data);
	printf("\n");
	
	check_flood_fill(&map_data);
	display_map_data(&map_data);

	init_images_walls(&map_data);
	// check_allowed_caracters(&map_data);
	map_free_after_flood_fill(&map_data);

	create_map_for_game(&map_data);
	// display_map_data(&map_data);




	// printf("NO : %s\n", map_data.no );
	// printf("SO : %s\n", map_data.so);
	// printf("WE : %s\n", map_data.we);
	// printf("EA : %s\n", map_data.ea);
	// printf("C : %s\n", data.map_data.cc);
	// printf("F : %s\n", data.map_data.cf);
	// while (i < 14)
	// {
	// 	printf("ligne %d : %s\n", i, data.map_data.map[i]);
	// 	i++;
	// } 
	// init_win(&data);
	// init_map(&data);
	// mlx_loop_hook(data.mlx, set_minimap, &data);
	// mlx_loop(data.mlx);
	// if (data.map_data.map[0] != NULL)
	// 	free_array(data.map_data.map);
	// free_char_option(&data);

	//return (0);

	//display_map(&data);
	//mlx_key_hook(data.mlx_win, handle_events, &data);
	//mlx_hook(data.mlx_win, 17, 0, close_window, &data);
	//mlx_loop(data.mlx);
}