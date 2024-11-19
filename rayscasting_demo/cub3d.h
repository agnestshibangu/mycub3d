#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include "../libft/libft.h" 
# include <stdio.h>


#include <math.h>
#include <stdio.h>
#include <stdbool.h> 
#include <sys/time.h>
# include <X11/keysym.h>
# include <X11/X.h>
#include <X11/Xlib.h>

// # include <unistd.h>
// # include <stdlib.h>
// # include <errno.h>
// # include <readline/readline.h>
// # include <readline
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <sys/wait.h>
// # include <fcntl.h>
// # include <math.h>

typedef struct s_data
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			screenWidth;
	int			screenHeight;
	//int			bits_per_pixel;
	//int			fd;
	///int			*format;
	//char		**map;
	//char		*current_line;
	//int			map_y;
	//int			map_x;
	//double		fov;
	//t_vec		pos;
	//t_vec		plane;
	//t_vec		dir;
	//int			color_floor;
	//int			color_ceiling;
	//t_texture	*tex;
	//int			size_line;
	//int			endian;
	//t_ray		ray;
	//t_mini		mini;
}	t_data;

typedef struct {
	unsigned char r, g, b;
} ColorRGB;


// Function declarations
void print_ok();
bool done();
void verLine(int x, int drawStart, int drawEnd, ColorRGB color);
double getTicks();
// void print(double fps);
void readKeys();

// void key_press(double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY);

void key_press(t_data *data, double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY, int worldMap[24][24]);
// void key_press( t_data *data, int posX, int posY, int dirY, int dirX, int planeY, int planeX, int worldMap[24][24]);
bool keyDown(int key);
void move_up(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int worldMap[24][24]);
void move_down(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int worldMap[24][24]);
void rotate(double *dirX, double *dirY, double *planeX, double *planeY, double rotSpeed, int direction);
void screen(int width, int height, int flags, const char* title);




#endif