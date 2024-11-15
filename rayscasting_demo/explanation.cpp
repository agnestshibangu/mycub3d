ARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(int /*argc*/, char */*argv*/[])
{
  double posX = 22, posY = 12;  // position vector of the player
  double dirX = -1, dirY = 0; // direction of the player
  double planeX = 0, planeY = 0.66; // camera plane of the player

  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  screen(screenWidth, screenHeight, 0, "Raycaster");
  // the game loop starts, this loop draws the whole frame reads player's actions on each iterations
  while(!done())
  {
    for(int x = 0; x < w; x++) // raycasting logic happens for each (x) column
    {
		// ----------------------------------------------
    	double cameraX = 2 * x / (double)w - 1; // c'est la coordonnees x sur le sur le 
		// plan de la camera, x = 0 centre x = -1 gauche x = 1 droite 
		// for each vertical pixel column x calculate the ray's direction base on the camera's
		// view and position
    	double rayDirX = dirX + planeX * cameraX; // X direction of the ray 
    	double rayDirY = dirY + planeY * cameraX; // Y direction of the ray
    	// ----------------------------------------------
		// ----------------------------------------------
		// which box of the map the player is in
    	int mapX = int(posX);
    	int mapY = int(posY);
		// ----------------------------------------------
		// ----------------------------------------------
    	// decide which direction the ray will step in (negative or positive for both axes)
		// and calculate the initial distance to the next grid line
    	double sideDistX, sideDistY;
    	double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    	double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX, stepY;

		int hit = 0; // has the wall been hit ? 
		int side; // which side was hit ?
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		// ----------------------------------------------
		// ----------------------------------------------
		//perform DDA
		// 
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			}
			if(worldMap[mapX][mapY] > 0) hit = 1;
      	}

		//  calculating perpendicular Wall Distance :
		// this gives the true distance from the player to the wall, avoiding distortion
		if(side == 0)
		{
			perpWallDist = (sideDistX - deltaDistX);
		}
		else 
		{
			perpWallDist = (sideDistY - deltaDistY);
		}

		// now we calculate the wall height : the shorter the distance is from player to wall, the bigger it is
		// == inversely proportional
		int lineHeight = (int)(h / perpWallDist);

		// this calculates the highest and lowest point of the line the needs to be drawn within 
		// the boundaries of the screen, it determines the range of vertival pixels to be colored
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h) drawEnd = h - 1;

		//choose wall color
		ColorRGB color;
		switch(worldMap[mapX][mapY])
		{
		case 1:  color = RGB_Red;    break; //red
		case 2:  color = RGB_Green;  break; //green
		case 3:  color = RGB_Blue;   break; //blue
		case 4:  color = RGB_White;  break; //white
		default: color = RGB_Yellow; break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1) 
		{
			color = color / 2;
		}
		//draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, color);
		}
		// FPS, input movement handling, and rendering happen here
		// ----------------------------------------------
		// ----------------------------------------------
		// calcul du temps entre les frames
		oldTime = time;
		time = getTicks(); // recupere le temps reel en millisecondes
		double frameTime = (time - oldTime) / 1000.0; // calcul de frame time / 1000.0 == en secondes
		// ----------------------------------------------
		// ----------------------------------------------
		// calcul du Frame Per Seconds
		print(1.0 / frameTime); // afficher le nombre de frames par seconde
		// ----------------------------------------------
		// ----------------------------------------------
		// redraw and cleaning of the screen || redessin et nettoyage de l'ecran
		redraw();
		cls();
		// ----------------------------------------------
		// ----------------------------------------------
		// vitesse de deplacement et de rotation ajustee par le temps
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
		readKeys();
		// ----------------------------------------------
		// ----------------------------------------------
		// deplacement vers l'avant - move forward
		if(keyDown(SDLK_UP))
		{
			if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
				posX += dirX * moveSpeed;
			if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
				posY += dirY * moveSpeed;
		}
		//move backwards if no wall behind you
		if(keyDown(SDLK_DOWN))
		{
		if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		}
		// ----------------------------------------------
		// ----------------------------------------------
		// rotation a droite - rotate to right
		if(keyDown(SDLK_RIGHT))
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		// ----------------------------------------------
		// ----------------------------------------------
		// rotation a gauche - rotate to left 
		if(keyDown(SDLK_LEFT))
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		}
  }
}

// code improvements : calculate the orientation of the camera place according
// to the direction of the camera 