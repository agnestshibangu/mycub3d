#include <math.h>
#include <stdio.h>
#include <stdbool.h> // For using bool type
#include <sys/time.h>
// #include <SDL.h> // Assuming you are using SDL for input and graphics
#include "minilibx/mlx.h"

// Define your constants and structures here
#define screenWidth 800
#define screenHeight 600
#define w screenWidth
#define h screenHeight

void *mlx_ptr;
void *win_ptr;
void *img_ptr; // For the image buffer
char *img_data; // Pointer to the image data
int bpp; // Bits per pixel
int size_line; // Size of a line in bytes
int endian; // Endianness

typedef struct {
    unsigned char r, g, b;
} ColorRGB;

double getTicks() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0); // Returns time in milliseconds
}

void screen(int width, int height, int flags, const char* title) {
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, width, height, (char *)title);
    img_ptr = mlx_new_image(mlx_ptr, width, height);
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
}

void verLine(int x, int drawStart, int drawEnd, ColorRGB color) {
    for (int y = drawStart; y < drawEnd; y++) {
        int pixel_index = (x * bpp / 8) + (y * size_line);
        img_data[pixel_index] = color.b; // Blue
        img_data[pixel_index + 1] = color.g; // Green
        img_data[pixel_index + 2] = color.r; // Red
    }
}

bool done() {
    // In MiniLibX, you'll typically handle closing the window in the main loop.
    return false; // Modify as needed to handle closing
}

void cleanup() {
    mlx_destroy_image(mlx_ptr, img_ptr);
    mlx_destroy_window(mlx_ptr, win_ptr);
}

ColorRGB RGB_Red = {255, 0, 0};
ColorRGB RGB_Green = {0, 255, 0};
ColorRGB RGB_Blue = {0, 0, 255};
ColorRGB RGB_White = {255, 255, 255};
ColorRGB RGB_Yellow = {255, 255, 0};

// Your world map definition
int worldMap[24][24]; // Adjust size as needed

// Function declarations
void screen(int width, int height, int flags, const char* title);
bool done();
void verLine(int x, int drawStart, int drawEnd, ColorRGB color);
double getTicks();
// void print(double fps);
void readKeys();
bool keyDown(int key);

int main(int ac, char **av) {
    double posX = 22; // x start position
    double posY = 12; // y start position
    double dirX = -1; // initial direction vector X
    double dirY = 0; // initial direction vector Y
    double planeX = 0; // the 2D ray
    double planeY = 0.66; // the 2D raycaster version of camera plane
    double time = 0; // time of current frame
    double oldTime = 0; // time of previous frame

    screen(screenWidth, screenHeight, 0, "Raycaster");
    while (!done()) {
        int x = 0;
        while (x < w) {
            double cameraX = 2 * x / (double)w - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            int mapX = (int)posX; // Cast to int
            int mapY = (int)posY; // Cast to int
            double sideDistX;
            double sideDistY;
            double deltaDistX;
            double deltaDistY;

            deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

            double perpWallDist;
            int stepX;
            int stepY;
            int hit = 0;
            int side;

            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }

            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            // Perform DDA
            while (hit == 0) {
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }

                if (worldMap[mapX][mapY] > 0) {
                    hit = 1;
                }
            }

            if (side == 0) {
                perpWallDist = (sideDistX - deltaDistX);
            } else {
                perpWallDist = (sideDistY - deltaDistY);
            }

            int lineHeight = (int)(h / perpWallDist);
            int drawStart = -lineHeight / 2 + h / 2;
            if (drawStart < 0) {
                drawStart = 0;
            }
            int drawEnd = lineHeight / 2 + h / 2;
            if (drawEnd >= h) {
                drawEnd = h - 1;
            }

            ColorRGB color;
            switch (worldMap[mapX][mapY]) {
                case 1: color = RGB_Red; break;
                case 2: color = RGB_Green; break;
                case 3: color = RGB_Blue; break;
                case 4: color = RGB_White; break;
                default: color = RGB_Yellow; break;
            }
            if (side == 1) {
                color.r /= 2;
                color.g /= 2;
                color.b /= 2;
            }
            verLine(x, drawStart, drawEnd, color);
            x++;
		mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
    	mlx_do_sync(mlx_ptr);
		}


        oldTime = time;
        time = getTicks();
        double frameTime = (time - oldTime) / 1000.0;
        // print(1.0 / frameTime);
        mlx_clear_window(mlx_ptr, win_ptr);

        double moveSpeed = frameTime * 5.0;
        double rotSpeed = frameTime * 3.0;
        // readKeys();
        // if (keyDown(SDLK_UP)) {
        //     if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == false) {
        //         posX += dirX * moveSpeed;
        //     }
        //     if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == false) {
        //         posY += dirY * moveSpeed;
        //     }
        // }
        // Move backwards if no wall behind you
        // if (keyDown(SDLK_DOWN)) {
        //     if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == false) {
        //         posX -= dirX * moveSpeed;
        //     }
        //     if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == false) {
        //         posY -= dirY * moveSpeed;
        //     }
        // }
        // Rotate to the right
        // if (keyDown(SDLK_RIGHT)) {
        //     double oldDirX = dirX;
        //     dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        //     dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        //     double oldPlaneX = planeX;
        //     planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        //     planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        // }
        // // Rotate to the left
        // if (keyDown(SDLK_LEFT)) {
        //     double oldDirX = dirX;
        //     dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        //     dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        //     double oldPlaneX = planeX;
        //     planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        //     planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        // }
    }
	cleanup();
    return 0;
}
