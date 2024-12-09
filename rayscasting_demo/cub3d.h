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


# define TILE_SIZE 		64
# define SCR_WIDTH 		1900
# define SCR_HEIGHT 	1000
# define PI 	3.14159

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

typedef struct s_texture
{
	void	*img;
	// char	*addr;
	unsigned int *addr;  // 1D array of pixels
	int		bits_per_pixels;
	int		line_length;
	int		endian;
	int		height;
	int		width;
	char	*path;
}	t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			screenWidth;
	int			screenHeight;
	t_texture	texture[4];
	int			worldMap[24][24];
	char		keys[256];
	unsigned int **wall;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}	t_data;

typedef struct {
	int	r;
	int	g;
	int	b;
} ColorRGB;


// Function declarations
void print_ok();
int	init_param(t_data *data);
bool done();

// int	key_release(int keycode, t_data *data);
void draw_ceiling(int x, int drawStart, t_data *data);
void draw_floor(int x, int drawEnd, t_data *data);

void verLine(int x, int drawStart, int drawEnd, t_data *data, int textureIndex, int textureX);
// void verLine(int x, int drawStart, int drawEnd, t_data *data, int textureIndex);
// void verLine(int x, int drawStart, int drawEnd, unsigned char r, unsigned char g, unsigned char b, t_data *data);
void	cast_rays_and_render(t_data *data);
// int	rerendering(t_data *data);
int rerendering(int keysym, t_data *data);
// void key_press(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
void move_up(t_data *data, double moveSpeed);
void move_down(t_data *data, double moveSpeed);
void rotate(t_data *data, double rotSpeed, int direction);
// void key_press(t_data *data);
void	event_handler(t_data *data);
int set_screen(const char* title, t_data *data);

// texture 
void	display_wall(t_data *data, int ray, int drawEnd, int drawStart);
double	normalize_angle(double angle);
int	get_texture(t_data *data);
void	get_text_x(t_data *data);
void	draw_wall(t_data *data, int top_pix, int bottom_pix, int ray);

// 
void init_images_walls(t_data *data, int i);
void allocate_wall(t_data *data);
void printAllPixels(t_data *data, int i);
void init_texture(t_data *data);

#endif