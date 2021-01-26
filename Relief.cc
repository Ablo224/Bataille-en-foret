#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Relief.h"
#include <cmath> 
#include <iostream>
using namespace std;

const int SSize = 32;

Relief::~Relief()
{
}

int Relief::getX()
{
	return x;
}

int Relief::getY()
{
	return y;
}

int Relief::get_x_size()
{
	return x_size;
}
		
int Relief::get_y_size()
{
	return y_size;
}

int Relief::get_hauteur()
{
	return hauteur;
}

Coline::Coline()
{
	x = 0;
	y = 0;
	x_size = 0;
	y_size = 0;
	hauteur = 2;
	type = COLINE;
}
	
Coline::Coline(int new_x, int new_y, int new_x_size, int new_y_size)
{
	x = new_x;
	y = new_y;
	x_size = (new_x_size < 4)? 4: new_x_size;
	y_size = (new_y_size < 4)? 4: new_y_size;
	hauteur = 2;
	type = COLINE;
}
	
Coline::Coline(Coline const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = autre.hauteur;
	type = COLINE;
}
	
Coline::~Coline()
{
	
}
	
void Coline::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceColineBO = IMG_Load("Ressources/ColineB0.png");
	SDL_Surface* SurfaceColineB1 = IMG_Load("Ressources/ColineB1.png");
	SDL_Surface* SurfaceColineBD = IMG_Load("Ressources/ColineBD.png");
	SDL_Surface* SurfaceColineBG = IMG_Load("Ressources/ColineBG.png");
	SDL_Surface* SurfaceColineDO = IMG_Load("Ressources/ColineD0.png");
	SDL_Surface* SurfaceColineD1 = IMG_Load("Ressources/ColineD1.png");
	SDL_Surface* SurfaceColineH = IMG_Load("Ressources/ColineH.png");
	SDL_Surface* SurfaceColineGO = IMG_Load("Ressources/ColineG0.png");
	SDL_Surface* SurfaceColineG1 = IMG_Load("Ressources/ColineG1.png");
	SDL_Surface* SurfaceColineHD = IMG_Load("Ressources/ColineHD.png");
	SDL_Surface* SurfaceColineHG = IMG_Load("Ressources/ColineHG.png");
	SDL_Surface* SurfaceHerbe = IMG_Load("Ressources/Grass1.png");
	SDL_Rect ColinePosition;
	
	ColinePosition.x = (x+((ecran->w/SSize)/2))*SSize;
	ColinePosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceColineHG, NULL, ecran, &ColinePosition);	
	ColinePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	ColinePosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceColineHD, NULL, ecran, &ColinePosition);	
	ColinePosition.x = (x+((ecran->w/SSize)/2))*SSize;
	ColinePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceColineBG, NULL, ecran, &ColinePosition);
	ColinePosition.y = ColinePosition.y - SSize;
	SDL_BlitSurface(SurfaceColineGO, NULL, ecran, &ColinePosition);	
	ColinePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize-1;
	ColinePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceColineBD, NULL, ecran, &ColinePosition);
	ColinePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	ColinePosition.y = ColinePosition.y - SSize;
	SDL_BlitSurface(SurfaceColineDO, NULL, ecran, &ColinePosition);
	
	for(int j = y+1; j<y+y_size-1; j++){
		ColinePosition.x = (x+((ecran->w/SSize)/2))*SSize;
		ColinePosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceColineG1, NULL, ecran, &ColinePosition);}
	
	for(int j = y+1; j<y+y_size-1; j++){
		ColinePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
		ColinePosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceColineD1, NULL, ecran, &ColinePosition);}
	
	for(int i = x+1; i<x+x_size; i++){
		ColinePosition.x = (i+((ecran->w/SSize)/2))*SSize;
		ColinePosition.y = (y+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceColineH, NULL, ecran, &ColinePosition);}
	
	for(int i = x+1; i<x+x_size; i++){
		ColinePosition.x = (i+((ecran->w/SSize)/2))*SSize;
		ColinePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceColineBO, NULL, ecran, &ColinePosition);}	
	
	for(int i = x+1; i<x+x_size; i++){
		ColinePosition.x = (i+((ecran->w/SSize)/2))*SSize;
		ColinePosition.y = ((y+y_size-1)+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceColineB1, NULL, ecran, &ColinePosition);}		
	
	SDL_FreeSurface(SurfaceHerbe);
	SDL_FreeSurface(SurfaceColineBO);
	SDL_FreeSurface(SurfaceColineB1);
	SDL_FreeSurface(SurfaceColineBD);
	SDL_FreeSurface(SurfaceColineBG);
	SDL_FreeSurface(SurfaceColineDO);
	SDL_FreeSurface(SurfaceColineD1);
	SDL_FreeSurface(SurfaceColineGO);
	SDL_FreeSurface(SurfaceColineG1);
	SDL_FreeSurface(SurfaceColineHD);
	SDL_FreeSurface(SurfaceColineH);
	SDL_FreeSurface(SurfaceColineHG);
}
	
TypeRelief Coline::getType()
{
	return COLINE;
}


Creux::Creux()
{
	x = 0;
	y = 0;
	x_size = 0;
	y_size = 0;
	hauteur = -2;
	type = CREUX;
}
	
Creux::Creux(int new_x, int new_y, int new_x_size, int new_y_size)
{
	x = new_x;
	y = new_y;
	x_size = (new_x_size < 4)? 4: new_x_size;
	y_size = (new_y_size < 4)? 4: new_y_size;
	hauteur = -2;
	type = CREUX;
}
	
Creux::Creux(Creux const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = autre.hauteur;
	type = CREUX;
}
	
Creux::~Creux()
{
	
}
	
void Creux::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceCreuxB = IMG_Load("Ressources/CreuxB.png");
	SDL_Surface* SurfaceCreuxBD = IMG_Load("Ressources/CreuxBD.png");
	SDL_Surface* SurfaceCreuxBG = IMG_Load("Ressources/CreuxBG.png");
	SDL_Surface* SurfaceCreuxDO = IMG_Load("Ressources/CreuxD0.png");
	SDL_Surface* SurfaceCreuxD1 = IMG_Load("Ressources/CreuxD1.png");
	SDL_Surface* SurfaceCreuxHO = IMG_Load("Ressources/CreuxH0.png");
	SDL_Surface* SurfaceCreuxH1 = IMG_Load("Ressources/CreuxH1.png");
	SDL_Surface* SurfaceCreuxGO = IMG_Load("Ressources/CreuxG0.png");
	SDL_Surface* SurfaceCreuxG1 = IMG_Load("Ressources/CreuxG1.png");
	SDL_Surface* SurfaceCreuxHD = IMG_Load("Ressources/CreuxHD.png");
	SDL_Surface* SurfaceCreuxHG = IMG_Load("Ressources/CreuxHG.png");
	SDL_Surface* SurfaceHerbe = IMG_Load("Ressources/Grass1.png");
	SDL_Rect CreuxPosition;
	
	
	CreuxPosition.x = (x+((ecran->w/SSize)/2))*SSize;
	CreuxPosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceCreuxHG, NULL, ecran, &CreuxPosition);	
	
	CreuxPosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	CreuxPosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceCreuxHD, NULL, ecran, &CreuxPosition);	
	
	CreuxPosition.x = (x+((ecran->w/SSize)/2))*SSize;
	CreuxPosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceCreuxBG, NULL, ecran, &CreuxPosition);
	
	CreuxPosition.y = CreuxPosition.y - SSize;
	SDL_BlitSurface(SurfaceCreuxGO, NULL, ecran, &CreuxPosition);	
	
	CreuxPosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	CreuxPosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceCreuxBD, NULL, ecran, &CreuxPosition);
	
	CreuxPosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	CreuxPosition.y = CreuxPosition.y - SSize;
	SDL_BlitSurface(SurfaceCreuxDO, NULL, ecran, &CreuxPosition);
	
	
	for(int j = y+1; j<y+y_size-1; j++){
		CreuxPosition.x = (x+((ecran->w/SSize)/2))*SSize;
		CreuxPosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceCreuxG1, NULL, ecran, &CreuxPosition);}

	for(int j = y+1; j<y+y_size-1; j++){
		CreuxPosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
		CreuxPosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceCreuxD1, NULL, ecran, &CreuxPosition);}
	
	for(int i = x+1; i<x+x_size; i++){
		CreuxPosition.x = (i+((ecran->w/SSize)/2))*SSize;
		CreuxPosition.y = (y+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceCreuxH1, NULL, ecran, &CreuxPosition);}
	
	for(int i = x+1; i<x+x_size; i++){
		CreuxPosition.x = (i+((ecran->w/SSize)/2))*SSize;
		CreuxPosition.y = (y+((ecran->h/SSize)/2)+1)*SSize;
		SDL_BlitSurface(SurfaceCreuxHO, NULL, ecran, &CreuxPosition);}
	
	for(int i = x+1; i<x+x_size; i++){
		CreuxPosition.x = (i+((ecran->w/SSize)/2))*SSize;
		CreuxPosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceCreuxB, NULL, ecran, &CreuxPosition);}
	
	SDL_FreeSurface(SurfaceHerbe);
	SDL_FreeSurface(SurfaceCreuxHO);
	SDL_FreeSurface(SurfaceCreuxH1);
	SDL_FreeSurface(SurfaceCreuxBD);
	SDL_FreeSurface(SurfaceCreuxBG);
	SDL_FreeSurface(SurfaceCreuxDO);
	SDL_FreeSurface(SurfaceCreuxD1);
	SDL_FreeSurface(SurfaceCreuxGO);
	SDL_FreeSurface(SurfaceCreuxG1);
	SDL_FreeSurface(SurfaceCreuxHD);
	SDL_FreeSurface(SurfaceCreuxB);
	SDL_FreeSurface(SurfaceCreuxHG);
}
	
TypeRelief Creux::getType()
{
	return CREUX;
}
