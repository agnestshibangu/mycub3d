#include "../inc/cub3d.h"

// allocating temp to size of map plus NULL
// while map, pass everything in temp
// pass new line in temp
// if temp NULL, free temp
// if strdup fails, free the already allocated memory
// free game
// pass content of temp in game->map
int	if_temp_null(t_map_data  *map_data, char **temp)
{
	int		y;

	if (!temp)
	{
		y = 0;
		while (y < map_data->height)
		{
			free(temp[y]);
			y++;
		}
		free(temp);
		return (0);
	}
	return (1);
}

char	**manage_temp(t_map_data  *map_data, char *line)
{
	char	**temp;
	int		i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (map_data->height + 1));
	if (!temp)
		return (0);
	temp[map_data->height - 1] = NULL;
	while (i < map_data->height - 1)
	{
		temp[i] = map_data->map[i];
		i++;
	}
	temp[i] = ft_strdup(line);
	if (!temp[i])
	{
		if_temp_null(map_data, temp);
		return (NULL);
	}
	return (temp);
}

int	save_line_in_map(t_map_data  *map_data, char *line)
{
	char	**temp;

	if (!line)
		return (0);
	map_data->height++;
	temp = manage_temp(map_data, line);
	if (map_data->map)
		free(map_data->map);
	map_data->map = temp;
	return (1);
}

int is_map_line(const char *line)
{
	int i = 0;

	if (strncmp(line, "NO", 2) == 0 || strncmp(line, "SO", 2) == 0 ||
		strncmp(line, "WE", 2) == 0 || strncmp(line, "EA", 2) == 0 ||
		strncmp(line, "F", 1) == 0 || strncmp(line, "C", 1) == 0)
	{
		return 0;
	}

	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '\n' && 
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			return 0;
		}
		i++;
	}
	return 1;
}

int	create_map(t_map_data  *map_data)
{
	int		fd;
	int		height;	
	char	*treated_line;
	int		width;
	int	i;

	height = 0;
	fd = open(map_data->map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	ft_memset(map_data, 0, sizeof(t_map_data));
	treated_line = get_next_line(fd);

	if (!treated_line)
		return (close(fd), 0);


	while (treated_line)
	{
		width = 0;
		i = 0;
		if (is_map_line(treated_line) && *treated_line != '\n')
		{
			while (treated_line[i] != '\n' && treated_line[i] != '\0')
			{
				if (treated_line[i] == '\t')
				{
					width += 4;
				}
				else
					width++;
				i++;
			}
			treated_line[i] = '\0';
			// y = 0;
			// while (treated_line[y])
			// {
			// 	printf("%c", treated_line[y]);
			// 	y++;
			// }
			// printf("\n width %d\n", width);
			if (map_data->width < width)
				map_data->width = width;
			save_line_in_map(map_data, treated_line);
			height++;
		}
		
		free(treated_line);
		treated_line = get_next_line(fd);
	}
	//printf("%d\n", map_data->height);
	//printf("%d\n", map_data->width);
	close(fd);
	return (1);
}


/*nb_column,	nb_row, p_count, width, height */
void display_map_data(t_map_data  *map_data)
{
	int x;
	int y;

	y = 0;
	if (map_data == NULL || map_data->map == NULL)
	{
		printf("Error: the map doesn't exist");
		return;
	}
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			if (map_data->map[y][x] == '1')
				printf("\033[31m%c\033[0m", map_data->map[y][x]);
			else if (map_data->map[y][x] == 'F')
				printf("\033[32m%c\033[0m", map_data->map[y][x]);
			else if (map_data->map[y][x] == 'N' || map_data->map[y][x] == 'W' 
					|| map_data->map[y][x] == 'E' || map_data->map[y][x] == 'S')
				printf("\033[1;35m%c\033[0m", map_data->map[y][x]);
			else
				printf("%c", map_data->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}	
}

int	create_map_for_game(t_map_data  *map_data)
{
	if (!create_map(map_data))
	{
		ft_printf("Error: Failed to create map\n");
		fflush(stdout);
		return (0);
	}
	// map_len(game);
	// if (!check_walls(game))
	// 	return (0);
	// if (!check_map(game))
	// 	return (0);
	else
	{
		//ft_printf("map created successfully\n");
		return (1);
	}
}

void init_images_walls(t_map_data  *map_data)
{
	map_data->no = "./assets/ea.png";
	map_data->so = "./assets/no.png";
	map_data->we = "./assets/so.png";
	map_data->ea = "./assets/we.png";
}


int	define_player_pos(t_map_data  *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width - 1)
		{
			if (map_data->map[y][x] == 'W' || map_data->map[y][x] == 'E'
				|| map_data->map[y][x] == 'S' || map_data->map[y][x] == 'N')
			{
				map_data->player_pos_x = x;
				map_data->player_pos_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	define_check_pos(t_map_data  *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width - 1)
		{
			if (map_data->map[y][x] == '0')
			{
				map_data->check_pos_x = x;
				map_data->check_pos_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}