#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Personnage.h"
#include <cmath> 
#include <iostream>
using namespace std;

const int SSize = 32;

Personnage::Personnage()
{
	x = y = 0;
	dir = BAS;
	vie = 0;
}
		
Personnage::Personnage(int new_x, int new_y, Direction new_dir, int new_vie, Color new_c)
{
	x = new_x;
	y = new_y;
	dir = new_dir;
	vie = new_vie;
	c = new_c;
}
		
Personnage::Personnage(Personnage const &autre)
{
	x = autre.x;
	y = autre.y;
	dir = autre.dir;
	vie = autre.vie;
	c = autre.c;
}
		
Personnage::~Personnage()
{
}
		
int Personnage::get_x()
{
	return x;
}
		
int Personnage::get_y()
{
	return y;
}
		
int Personnage::get_dir()
{
	return dir;
}
		
int Personnage::get_vie()
{
	return vie;
}
		
void Personnage::set_x(int new_x)
{
	x = new_x;
}
		
void Personnage::set_y(int new_y)
{
	y = new_y;
}

void Personnage::set_dir(Direction new_dir)
{
	dir = new_dir;
}
		
void Personnage::set_vie(int new_vie)
{
	vie = new_vie;
}
		
void Personnage::deplacer(int new_x, int new_y, Direction new_dir)
{
	x = new_x;
	y = new_y;
	dir = new_dir;
}
	
void Personnage::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfacePlayer_H0 = IMG_Load("Ressources/PlayerH0.png");
	SDL_Surface* SurfacePlayer_B0 = IMG_Load("Ressources/PlayerB0.png");
	SDL_Surface* SurfacePlayer_D0 = IMG_Load("Ressources/PlayerD0.png");
	SDL_Surface* SurfacePlayer_G0 = IMG_Load("Ressources/PlayerG0.png");
	SDL_Surface* SurfaceRED_Player_H0 = IMG_Load("Ressources/RED_PlayerH0.png");
	SDL_Surface* SurfaceRED_Player_B0 = IMG_Load("Ressources/RED_PlayerB0.png");
	SDL_Surface* SurfaceRED_Player_D0 = IMG_Load("Ressources/RED_PlayerD0.png");
	SDL_Surface* SurfaceRED_Player_G0 = IMG_Load("Ressources/RED_PlayerG0.png");	
	
	SDL_Rect PositionPlayer;
	
	PositionPlayer.x = ((x+((ecran->w/SSize)/2))*SSize);
	PositionPlayer.y = ((y+((ecran->h/SSize)/2)-1)*SSize)+8;
	
	switch(dir)
	{
		case HAUT:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_H0, NULL, ecran, &PositionPlayer);	
			else
				SDL_BlitSurface(SurfacePlayer_H0, NULL, ecran, &PositionPlayer);
		break;
		
		case HAUT_DROITE:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_D0, NULL, ecran, &PositionPlayer);
			else
				SDL_BlitSurface(SurfacePlayer_D0, NULL, ecran, &PositionPlayer);			
		break;
		
		case DROITE:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_D0, NULL, ecran, &PositionPlayer);
			else
				SDL_BlitSurface(SurfacePlayer_D0, NULL, ecran, &PositionPlayer);			
		break;
		
		case BAS_DROITE:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_D0, NULL, ecran, &PositionPlayer);
			else	
				SDL_BlitSurface(SurfacePlayer_D0, NULL, ecran, &PositionPlayer);	
		break;
		
		case BAS:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_B0, NULL, ecran, &PositionPlayer);
			else
				SDL_BlitSurface(SurfacePlayer_B0, NULL, ecran, &PositionPlayer);	
		break;
		
		case BAS_GAUCHE:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_G0, NULL, ecran, &PositionPlayer);
			else
				SDL_BlitSurface(SurfacePlayer_G0, NULL, ecran, &PositionPlayer);	
		break;
		
		case GAUCHE:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_G0, NULL, ecran, &PositionPlayer);
			else
				SDL_BlitSurface(SurfacePlayer_G0, NULL, ecran, &PositionPlayer);
		break;
		
		case HAUT_GAUCHE:
			if(c == ROUGE)
				SDL_BlitSurface(SurfaceRED_Player_G0, NULL, ecran, &PositionPlayer);
			else
				SDL_BlitSurface(SurfacePlayer_G0, NULL, ecran, &PositionPlayer);
		break;
	}

	SDL_FreeSurface( SurfacePlayer_H0);
	SDL_FreeSurface( SurfacePlayer_B0);
	SDL_FreeSurface( SurfacePlayer_D0);
	SDL_FreeSurface( SurfacePlayer_G0);
	SDL_FreeSurface( SurfaceRED_Player_H0);
	SDL_FreeSurface( SurfaceRED_Player_B0);
	SDL_FreeSurface( SurfaceRED_Player_D0);
	SDL_FreeSurface( SurfaceRED_Player_G0);
}
