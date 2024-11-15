#ifndef CUB3D_H
# define CUB3D_H

/* Library */

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <math.h>
/* Structure */


//#define M_PI       3.14159265358979323846;
#define TILE 8;

typedef struct s_coord{
	int	x;
	int	y;
}	t_coord;

typedef struct s_pos{
	float	x;
	float	y;
}	t_pos;

typedef struct s_player{
	t_pos	ppos;
	float	angle;
}	t_player;

typedef struct s_arrow{
	t_pos head;
	t_pos left;
	t_pos right;
}	t_arrow;

typedef struct s_map_data{
	char			**map;
	unsigned int	nb_column;
	unsigned int	nb_row;
	int				p_count;
	int				width;
	int				height;
	t_player		player;
	int				player_pos_x;
	int				player_pos_y;
	int				check_pos_x;
	int				check_pos_y;
	int				map_error;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*cc;
	char			*cf;
	int				count_line;
	char	*map_file;
}	t_map_data;

typedef struct s_data{
	void			*mlx;
	void			*mlx_win;
	t_map_data		map_data;
}	t_data;

/* Fonctions */

/* minimap/map_pos.c */
t_pos	create_pos(float x, float y);
t_coord	create_coord(int x, int y);
/* utils/ft_error.c */


/* utils/ft_utils.c */


/* raycast/minimap.c */


/* raycast/pos.c */

/* raycast/mlxinit.c */


/* raycast/draw.c */

/*src/init.c*/
int	if_temp_null(t_map_data  *map_data, char **temp);
char	**manage_temp(t_map_data  *map_data, char *line);
int	save_line_in_map(t_map_data  *map_data, char *line);
int	create_map(t_map_data  *map_data);
int	create_map_for_game(t_map_data  *map_data);
void init_images_walls(t_map_data  *map_data);
int	define_player_pos(t_map_data  *map_data);
int	define_check_pos(t_map_data  *map_data);

/*src/parsing.c*/
int	check_extension_file_name(char *name);
int	does_file_exist(char *name);
void display_map_data(t_map_data  *map_data);
int	check_walls_horizontal(t_map_data  *map_data);
int	check_walls_vertical(t_map_data  *map_data);
int	check_allowed_caracters(t_map_data  *map_data);


/*src/floodfill.c*/
// void flood_map(t_map_data  *map_data, int x, int y);
void	flood_map(t_map_data  *map_data, int x, int y);
int	check_flood_fill(t_map_data  *map_data);
int	map_free_after_flood_fill(t_map_data *map_data);

#endif