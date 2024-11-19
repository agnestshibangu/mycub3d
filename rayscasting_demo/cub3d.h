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
	int			worldMap[24][24];
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}	t_data;


	// ColorRGB RGB_Red = {255, 105, 180};
	// ColorRGB RGB_Green = {255, 105, 180};
	// ColorRGB RGB_Blue = {255, 105, 180};
	// ColorRGB RGB_White = {255, 105, 180};
	// ColorRGB RGB_Yellow = {255, 105, 180};

typedef struct {
	unsigned char r, g, b;
} ColorRGB;


// Function declarations
void print_ok();
int	init_param(t_data *data);
bool done();
// void verLine(int x, int drawStart, int drawEnd, ColorRGB color);
// void verLine(int x, int drawStart, int drawEnd, ColorRGB color, int image_width);
// void verLine(int x, int drawStart, int drawEnd, ColorRGB color, t_data *data);
void verLine(int x, int drawStart, int drawEnd, unsigned char r, unsigned char g, unsigned char b, t_data *data);

// void verLine(int x, int drawStart, int drawEnd, ColorRGB color, int image_width, t_data data);
double getTicks();
// void print(double fps);
void readKeys();

// void key_press(double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY);
void	cast_rays_and_render(t_data *data);
void key_press(t_data *data, double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY, int worldMap[24][24]);
// void key_press( t_data *data, int posX, int posY, int dirY, int dirX, int planeY, int planeX, int worldMap[24][24]);
bool keyDown(int key);
void move_up(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int worldMap[24][24]);
void move_down(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int worldMap[24][24]);
void rotate(double *dirX, double *dirY, double *planeX, double *planeY, double rotSpeed, int direction);
int set_screen(const char* title, t_data *data);



#endif