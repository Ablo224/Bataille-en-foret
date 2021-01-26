#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Obstacle.h"
#include "Personnage.h"
#include <cmath> 
#include <iostream>
using namespace std;

const int SSize = 32;

Obstacle::~Obstacle()
{
}

int Obstacle::getX()
{
	return x;
}

int Obstacle::getY()
{
	return y;
}

Dir Obstacle::getDir()
{
	return direction;
}

int Obstacle::get_x_size()
{
	return x_size;
}
		
int Obstacle::get_y_size()
{
	return y_size;
}

int Obstacle::get_hauteur()
{
	return hauteur;
}

int Obstacle::get_vie()
{
	return vie;
}

void Obstacle::set_vie(int new_vie)
{
	vie = new_vie;
}
// ARBRE

Arbre::Arbre()
{
	x = y = 0;
	x_size = y_size = 2;
	hauteur = 3;
	vie = 5;
	type = ARBRE;
}
		
Arbre::Arbre(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
	x_size = y_size = 2;
	hauteur = 3;
	vie = 5;
	type = ARBRE;
}
		
Arbre::Arbre(Arbre const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = 3;
	vie = autre.vie;
	type = ARBRE;
}

Arbre::~Arbre()
{
	
}

void Arbre::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceArbre = IMG_Load("Ressources/Arbre.png");
	SDL_Rect PositionArbre;
	
	PositionArbre.x = ((x+((ecran->w/SSize)/2))*SSize)-4;
	PositionArbre.y = ((y+((ecran->h/SSize)/2))*SSize)-19;
	SDL_BlitSurface(SurfaceArbre, NULL, ecran, &PositionArbre);	
		
	SDL_FreeSurface(SurfaceArbre);
}
		
TypeObstacle Arbre::getType()
{
	return type;
}

// PETIT ARBRE

Petit_Arbre::Petit_Arbre()
{
	x = y = 0;
	x_size = y_size = 1;
	hauteur = 2;
	vie = 3;
	type = PETIT_ARBRE;
}
		
Petit_Arbre::Petit_Arbre(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
	x_size = y_size = 1;
	hauteur = 2;
	vie = 3;
	type = PETIT_ARBRE;
}
		
Petit_Arbre::Petit_Arbre(Petit_Arbre const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = 2;
	vie = autre.vie;
	type = PETIT_ARBRE;
}

Petit_Arbre::~Petit_Arbre()
{
	
}

void Petit_Arbre::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfacePetit_Arbre = IMG_Load("Ressources/Petit_Arbre.png");
	SDL_Rect PositionPetit_Arbre;
	
	PositionPetit_Arbre.x = ((x+((ecran->w/SSize)/2))*SSize)-1;
	PositionPetit_Arbre.y = ((y-1+((ecran->h/SSize)/2))*SSize)+8;
	SDL_BlitSurface(SurfacePetit_Arbre, NULL, ecran, &PositionPetit_Arbre);	
		
	SDL_FreeSurface(SurfacePetit_Arbre);
}
		
TypeObstacle Petit_Arbre::getType()
{
	return type;
}

// ROCHER

Rocher::Rocher()
{
	x = y = 0;
	x_size = y_size = 2;
	hauteur = 2;
	vie = 8;
	type = ROCHER;
}
		
Rocher::Rocher(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
	x_size = y_size = 2;
	hauteur = 2;
	vie = 8;
	type = ROCHER;
}
		
Rocher::Rocher(Rocher const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = 2;
	vie = autre.vie;
	type = ROCHER;
}

Rocher::~Rocher()
{
	
}

void Rocher::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceRocher = IMG_Load("Ressources/Rocher.png");
	SDL_Rect PositionRocher;
	
	PositionRocher.x = ((x+((ecran->w/SSize)/2))*SSize);
	PositionRocher.y = ((y+((ecran->h/SSize)/2))*SSize);
	SDL_BlitSurface(SurfaceRocher, NULL, ecran, &PositionRocher);	
		
	SDL_FreeSurface(SurfaceRocher);
}
		
TypeObstacle Rocher::getType()
{
	return type;
}

// PETIT ROCHER

Petit_Rocher::Petit_Rocher()
{
	x = y = 0;
	x_size = y_size = 1;
	hauteur = 1;
	vie = 5;
	type = PETIT_ROCHER;
}
		
Petit_Rocher::Petit_Rocher(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
	x_size = y_size = 1;
	hauteur = 1;
	vie = 5;
	type = PETIT_ROCHER;
}
		
Petit_Rocher::Petit_Rocher(Petit_Rocher const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = 2;
	vie = autre.vie;
	type = PETIT_ROCHER;
}

Petit_Rocher::~Petit_Rocher()
{
	
}

void Petit_Rocher::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfacePetit_Rocher = IMG_Load("Ressources/Petit_Rocher.png");
	SDL_Rect PositionPetit_Rocher;
	
	PositionPetit_Rocher.x = ((x+((ecran->w/SSize)/2))*SSize);
	PositionPetit_Rocher.y = ((y+((ecran->h/SSize)/2))*SSize);
	SDL_BlitSurface(SurfacePetit_Rocher, NULL, ecran, &PositionPetit_Rocher);	
		
	SDL_FreeSurface(SurfacePetit_Rocher);
}
		
TypeObstacle Petit_Rocher::getType()
{
	return type;
}

// MURET

Muret::Muret()
{
	x = y = 0;
	x_size = y_size = 1;
	hauteur = 1;
	vie = 1;
	direction = HORIZONTAL;
	type = MURET;
}
		
Muret::Muret(int new_x, int new_y, Dir d)
{
	x = new_x;
	y = new_y;
	x_size = y_size = 1;
	hauteur = 1;
	vie = 1;
	direction = d;
	type = MURET;
}
		
Muret::Muret(Muret const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = 2;
	direction = autre.direction;
	vie = autre.vie;
	type = MURET;
}

Muret::~Muret()
{
	
}

void Muret::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceMuret = NULL;
	SDL_Rect PositionMuret;
	
	if(direction == HORIZONTAL){
		SurfaceMuret = IMG_Load("Ressources/MuretH.png");
		PositionMuret.x = ((x+((ecran->w/SSize)/2))*SSize);
		PositionMuret.y = ((y+((ecran->h/SSize)/2))*SSize);}
	else{
		SurfaceMuret = IMG_Load("Ressources/MuretV.png");
		PositionMuret.x = ((x+((ecran->w/SSize)/2))*SSize);
		PositionMuret.y = ((y+((ecran->h/SSize)/2))*SSize)-7;}

	SDL_BlitSurface(SurfaceMuret, NULL, ecran, &PositionMuret);	
		
	SDL_FreeSurface(SurfaceMuret);
}
		
TypeObstacle Muret::getType()
{
	return type;
}
