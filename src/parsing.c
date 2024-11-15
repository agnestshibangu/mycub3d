#include "../inc/cub3d.h"

int	check_extension_file_name(char *name)
{
	int			i;
	int			y;
	const char	*needle;

	i = 0;
	y = 0;
	needle = ".cub";
	while (name[i])
	{
		if (name[i] == needle[y])
			y++;
		i++;
	}
	if (y == 4 && name[i] == '\0')
		return (1);
	return (0);
}

int	does_file_exist(char *name)
{
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("the file does not exist\n");
		return (1);
	}
	else
	{
		return (0);
	}
}

int	check_allowed_caracters(t_map_data  *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width - 1)
		{
			if (map_data->map[y][x] != '1' && map_data->map[y][x] != '0' &&
				map_data->map[y][x] != 'N' && map_data->map[y][x] != 'S' &&
				map_data->map[y][x] != 'W' && map_data->map[y][x] != 'E')
			{
				printf("bad characters ERROR \n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
