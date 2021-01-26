#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Surface.h"
#include <cmath> 
#include <iostream>
using namespace std;

const int SSize = 32;

Surface::~Surface()
{
}

int Surface::getX()
{
	return x;
}

int Surface::getY()
{
	return y;
}

int Surface::get_x_size()
{
	return x_size;
}
		
int Surface::get_y_size()
{
	return y_size;
}

Eau::Eau()
{
	x = y = x_size = y_size = hauteur = 0;
	type = EAU;
}
		
Eau::Eau(int new_x, int new_y, int new_x_size, int new_y_size)
{
	x = new_x;
	y = new_y;
	x_size = (new_x_size < 3)? 3: new_x_size;
	y_size = (new_y_size < 3)? 3: new_y_size;
	hauteur = 0; 
	type = EAU;

}
		
Eau::Eau(Eau const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = autre.hauteur;
	type = EAU;
}
		
Eau::~Eau()
{

}
		
void Eau::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceEau = IMG_Load("Ressources/Water1.png");
	SDL_Surface* SurfaceEauHG = IMG_Load("Ressources/EauHG.png");
	SDL_Surface* SurfaceEauH = IMG_Load("Ressources/EauH.png");
	SDL_Surface* SurfaceEauHD = IMG_Load("Ressources/EauHD.png");
	SDL_Surface* SurfaceEauD = IMG_Load("Ressources/EauD.png");
	SDL_Surface* SurfaceEauBD = IMG_Load("Ressources/EauBD.png");
	SDL_Surface* SurfaceEauB = IMG_Load("Ressources/EauB.png");
	SDL_Surface* SurfaceEauBG = IMG_Load("Ressources/EauBG.png");
	SDL_Surface* SurfaceEauG = IMG_Load("Ressources/EauG.png");
	SDL_Rect EauPosition;
	
	
	for(int i=x+1; i<x+x_size;i++){
		for(int j=y+1; j<y+y_size;j++){
			EauPosition.x = (i+((ecran->w/SSize)/2))*SSize;
			EauPosition.y = (j+((ecran->h/SSize)/2))*SSize;
			SDL_BlitSurface(SurfaceEau, NULL, ecran, &EauPosition);}}
			
	EauPosition.x = (x+((ecran->w/SSize)/2))*SSize;
	EauPosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceEauHG, NULL, ecran, &EauPosition);	
	EauPosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	EauPosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceEauHD, NULL, ecran, &EauPosition);	
	EauPosition.x = (x+((ecran->w/SSize)/2))*SSize;
	EauPosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceEauBG, NULL, ecran, &EauPosition);	
	EauPosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	EauPosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceEauBD, NULL, ecran, &EauPosition);
	
	for(int i = x+1; i<x+x_size; i++){
		EauPosition.x = (i+((ecran->w/SSize)/2))*SSize;
		EauPosition.y = (y+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceEauH, NULL, ecran, &EauPosition);}

	for(int i = x+1; i<x+x_size; i++){
		EauPosition.x = (i+((ecran->w/SSize)/2))*SSize;
		EauPosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceEauB, NULL, ecran, &EauPosition);}
	
	for(int j = y+1; j<y+y_size; j++){
		EauPosition.x = (x+((ecran->w/SSize)/2))*SSize;
		EauPosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceEauG, NULL, ecran, &EauPosition);}

	for(int j = y+1; j<y+y_size; j++){
		EauPosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
		EauPosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceEauD, NULL, ecran, &EauPosition);}
			
	SDL_Flip(ecran);
	SDL_FreeSurface(SurfaceEau);
	SDL_FreeSurface(SurfaceEauHG);
	SDL_FreeSurface(SurfaceEauH);
	SDL_FreeSurface(SurfaceEauHD);
	SDL_FreeSurface(SurfaceEauD);
	SDL_FreeSurface(SurfaceEauBD);
	SDL_FreeSurface(SurfaceEauB);
	SDL_FreeSurface(SurfaceEauBG);
	SDL_FreeSurface(SurfaceEauG);
}

TypeSurface Eau::getType()
{
	return EAU;
}

Sable::Sable()
{
	x = y = x_size = y_size = hauteur = 0;
	type = SABLE;
}
		
Sable::Sable(int new_x, int new_y, int new_x_size, int new_y_size)
{
	x = new_x;
	y = new_y;
	x_size = (new_x_size < 3)? 3: new_x_size;
	y_size = (new_y_size < 3)? 3: new_y_size;
	hauteur = 0; 
	type = SABLE;

}
		
Sable::Sable(Sable const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = autre.hauteur;
	type = SABLE;
}
		
Sable::~Sable()
{

}
		
void Sable::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceSable = IMG_Load("Ressources/Sand1.png");
	SDL_Surface* SurfaceSableHG = IMG_Load("Ressources/SableHG.png");
	SDL_Surface* SurfaceSableH = IMG_Load("Ressources/SableH.png");
	SDL_Surface* SurfaceSableHD = IMG_Load("Ressources/SableHD.png");
	SDL_Surface* SurfaceSableD = IMG_Load("Ressources/SableD.png");
	SDL_Surface* SurfaceSableBD = IMG_Load("Ressources/SableBD.png");
	SDL_Surface* SurfaceSableB = IMG_Load("Ressources/SableB.png");
	SDL_Surface* SurfaceSableBG = IMG_Load("Ressources/SableBG.png");
	SDL_Surface* SurfaceSableG = IMG_Load("Ressources/SableG.png");
	SDL_Rect SablePosition;
	
	
	for(int i=x+1; i<x+x_size;i++){
		for(int j=y+1; j<y+y_size;j++){
			SablePosition.x = (i+((ecran->w/SSize)/2))*SSize;
			SablePosition.y = (j+((ecran->h/SSize)/2))*SSize;
			SDL_BlitSurface(SurfaceSable, NULL, ecran, &SablePosition);}}
			
	SablePosition.x = (x+((ecran->w/SSize)/2))*SSize;
	SablePosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceSableHG, NULL, ecran, &SablePosition);	
	SablePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	SablePosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceSableHD, NULL, ecran, &SablePosition);	
	SablePosition.x = (x+((ecran->w/SSize)/2))*SSize;
	SablePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceSableBG, NULL, ecran, &SablePosition);	
	SablePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	SablePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceSableBD, NULL, ecran, &SablePosition);
	
	for(int i = x+1; i<x+x_size; i++){
		SablePosition.x = (i+((ecran->w/SSize)/2))*SSize;
		SablePosition.y = (y+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceSableH, NULL, ecran, &SablePosition);}

	for(int i = x+1; i<x+x_size; i++){
		SablePosition.x = (i+((ecran->w/SSize)/2))*SSize;
		SablePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceSableB, NULL, ecran, &SablePosition);}
	
	for(int j = y+1; j<y+y_size; j++){
		SablePosition.x = (x+((ecran->w/SSize)/2))*SSize;
		SablePosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceSableG, NULL, ecran, &SablePosition);}

	for(int j = y+1; j<y+y_size; j++){
		SablePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
		SablePosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceSableD, NULL, ecran, &SablePosition);}
			
	SDL_Flip(ecran);
	SDL_FreeSurface(SurfaceSable);
	SDL_FreeSurface(SurfaceSableHG);
	SDL_FreeSurface(SurfaceSableH);
	SDL_FreeSurface(SurfaceSableHD);
	SDL_FreeSurface(SurfaceSableD);
	SDL_FreeSurface(SurfaceSableBD);
	SDL_FreeSurface(SurfaceSableB);
	SDL_FreeSurface(SurfaceSableBG);
	SDL_FreeSurface(SurfaceSableG);
}

TypeSurface Sable::getType()
{
	return SABLE;
}

Boue::Boue()
{
	x = y = x_size = y_size = hauteur = 0;
	type = BOUE;
}
		
Boue::Boue(int new_x, int new_y, int new_x_size, int new_y_size)
{
	x = new_x;
	y = new_y;
	x_size = (new_x_size < 3)? 3: new_x_size;
	y_size = (new_y_size < 3)? 3: new_y_size;
	hauteur = 0; 
	type = BOUE;

}
		
Boue::Boue(Boue const& autre)
{
	x = autre.x;
	y = autre.y;
	x_size = autre.x_size;
	y_size = autre.y_size;
	hauteur = autre.hauteur;
	type = BOUE;
}
		
Boue::~Boue()
{
}
		
void Boue::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceBoue = IMG_Load("Ressources/Ground1.png");
	SDL_Surface* SurfaceBoueHG = IMG_Load("Ressources/BoueHG.png");
	SDL_Surface* SurfaceBoueH = IMG_Load("Ressources/BoueH.png");
	SDL_Surface* SurfaceBoueHD = IMG_Load("Ressources/BoueHD.png");
	SDL_Surface* SurfaceBoueD = IMG_Load("Ressources/BoueD.png");
	SDL_Surface* SurfaceBoueBD = IMG_Load("Ressources/BoueBD.png");
	SDL_Surface* SurfaceBoueB = IMG_Load("Ressources/BoueB.png");
	SDL_Surface* SurfaceBoueBG = IMG_Load("Ressources/BoueBG.png");
	SDL_Surface* SurfaceBoueG = IMG_Load("Ressources/BoueG.png");
	SDL_Rect BouePosition;
	
	
	for(int i=x+1; i<x+x_size;i++){
		for(int j=y+1; j<y+y_size;j++){
			BouePosition.x = (i+((ecran->w/SSize)/2))*SSize;
			BouePosition.y = (j+((ecran->h/SSize)/2))*SSize;
			SDL_BlitSurface(SurfaceBoue, NULL, ecran, &BouePosition);}}
			
	BouePosition.x = (x+((ecran->w/SSize)/2))*SSize;
	BouePosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceBoueHG, NULL, ecran, &BouePosition);	
	BouePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	BouePosition.y = (y+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceBoueHD, NULL, ecran, &BouePosition);	
	BouePosition.x = (x+((ecran->w/SSize)/2))*SSize;
	BouePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceBoueBG, NULL, ecran, &BouePosition);	
	BouePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
	BouePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
	SDL_BlitSurface(SurfaceBoueBD, NULL, ecran, &BouePosition);
	
	for(int i = x+1; i<x+x_size; i++){
		BouePosition.x = (i+((ecran->w/SSize)/2))*SSize;
		BouePosition.y = (y+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceBoueH, NULL, ecran, &BouePosition);}

	for(int i = x+1; i<x+x_size; i++){
		BouePosition.x = (i+((ecran->w/SSize)/2))*SSize;
		BouePosition.y = ((y+y_size)+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceBoueB, NULL, ecran, &BouePosition);}
	
	for(int j = y+1; j<y+y_size; j++){
		BouePosition.x = (x+((ecran->w/SSize)/2))*SSize;
		BouePosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceBoueG, NULL, ecran, &BouePosition);}

	for(int j = y+1; j<y+y_size; j++){
		BouePosition.x = ((x+x_size)+((ecran->w/SSize)/2))*SSize;
		BouePosition.y = (j+((ecran->h/SSize)/2))*SSize;
		SDL_BlitSurface(SurfaceBoueD, NULL, ecran, &BouePosition);}
			
	SDL_Flip(ecran);
	SDL_FreeSurface(SurfaceBoue);
	SDL_FreeSurface(SurfaceBoueHG);
	SDL_FreeSurface(SurfaceBoueH);
	SDL_FreeSurface(SurfaceBoueHD);
	SDL_FreeSurface(SurfaceBoueD);
	SDL_FreeSurface(SurfaceBoueBD);
	SDL_FreeSurface(SurfaceBoueB);
	SDL_FreeSurface(SurfaceBoueBG);
	SDL_FreeSurface(SurfaceBoueG);
}

TypeSurface Boue::getType()
{
	return BOUE;
}
