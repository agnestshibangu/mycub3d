#include "../inc/cub3d.h"

int	map_free_after_flood_fill(t_map_data *map_data)
{
	int		nbr_of_lines;

	nbr_of_lines = 0;
	if (map_data->map != NULL)
	{
		while (nbr_of_lines < map_data->height)
		{
			free(map_data->map[nbr_of_lines]);
			map_data->map[nbr_of_lines] = NULL;
			nbr_of_lines++;
		}
		free(map_data->map);
		// map_data->map = NULL;
	}
	return (1);
}


void flood_map(t_map_data *map_data, int x, int y)
{
    if (x < 0 || y < 0 || x >= map_data->width || y >= map_data->height)
    {
        map_data->map_error = 1;
        return;
    }
	
	if (map_data->map[y][x] == '0')
	{
		if ((x > 0 && map_data->map[y][x - 1] == ' ') ||
            (x < map_data->width - 1 && map_data->map[y][x + 1] == ' ') ||
            (y > 0 && map_data->map[y - 1][x] == ' ') ||
            (y < map_data->height - 1 && map_data->map[y + 1][x] == ' '))
        {
            map_data->map_error = 1;
            return;
        }

	}


    if (map_data->map[y][x] == '1' || map_data->map[y][x] == 'F')
        return;

    map_data->map[y][x] = 'F';

    flood_map(map_data, x, y + 1);
    flood_map(map_data, x, y - 1);
    flood_map(map_data, x + 1, y);
    flood_map(map_data, x - 1, y);
}

int check_flood_fill(t_map_data *map_data)
{
    int x;
    int y;

    map_data->map_error = 0;
    y = 0;
    while (y < map_data->height)
    {
        x = 0;
        while (x < map_data->width)
        {
            if (map_data->map[y][x] == '0')
            {
                flood_map(map_data, x, y);
                if (map_data->map_error == 1)
                {
                    printf("Error: map is not closed\n");
                    return 0;
                }

                x = 0;
                y = 0;
                break;
            }
            x++;
        }

        if (map_data->map_error == 1)
        {
            break;
        }
        y++;
    }
    return 1;
}







// void	flood_map(t_map_data  *map_data, int x, int y)
// {
// 	if (x < 0 || y < 0 || x >= map_data->width || y >= map_data->height)
//     {
// 		map_data->map_error = 1;
// 		printf("Error : map is invalid");
// 		return;
// 	}

// 	if (map_data->map[y][x] == '1' || map_data->map[y][x] == 'F')
// 		return ;

// 	map_data->map[y][x] = 'F';
	
// 	flood_map(map_data, x, y + 1);
// 	flood_map(map_data, x, y - 1);
// 	flood_map(map_data, x + 1, y);
// 	flood_map(map_data, x - 1, y);
// }

// int	check_flood_fill(t_map_data  *map_data)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < map_data->height)
// 	{
// 		x = 0;
// 		while (x < map_data->width - 1)
// 		{
// 			if (map_data->map[y][x] == '0')
// 			{
// 				flood_map(map_data, x, y);
// 				if (map_data->map_error == 1)
// 				{
// 					printf("map error");
// 					return (0);
// 				}
// 				x = 0;
// 				y = 0;
// 				break;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (1);
// }

// int	check_flood_fill_map(t_game *game, t_gamefile *gamefile)
// {
// 	if (!create_map(game, gamefile))
// 	{
// 		ft_printf("Error: Failed to create map\n");
// 		return (0);
// 	}
// 	if (!map_len(game))
// 		return (0);
// 	if (!check_map(game))
// 		return (0);
// 	if (!display_player_pos(game))
// 		return (0);
// 	flood_map(game, game->player_pos_x, game->player_pos_y);
// 	if (!check_flood_fill(game))
// 	{
// 		ft_printf("Error: Failed flood map\n");
// 		return (0);
// 	}
// 	if (!map_free_after_flood_fill(game))
// 	{
// 		ft_printf("Error: Failed to free map after flood fill\n");
// 		return (0);
// 	}
// 	return (1);
// }