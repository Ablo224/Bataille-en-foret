#ifndef Surface_h
#define Surface_h
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include <cmath> 
#include <iostream>
using namespace std;

enum TypeSurface
{
	BOUE,
	SABLE,
	EAU
};

class Surface
{
	protected:
		int x, y;
		int x_size, y_size;
		int hauteur;
		TypeSurface type;
	
	public:
		//destructeur virtuel
		virtual ~Surface() = 0;
		
		//accesseur
		virtual void afficher(SDL_Surface* ecran) = 0;
		
		int getX();
		
		int getY();
		
		int get_x_size();
		
		int get_y_size();
		
		virtual TypeSurface getType() = 0;	
};

class Eau: public Surface
{
	public:
		Eau();
		
		Eau(int, int, int, int);
		
		Eau(Eau const&);
		
		~Eau();
		
		void afficher(SDL_Surface* ecran);
		
		TypeSurface getType();	
};

class Sable: public Surface
{
	public:
		Sable();
		
		Sable(int, int, int, int);
		
		Sable(Sable const&);
		
		~Sable();
		
		void afficher(SDL_Surface* ecran);
		
		TypeSurface getType();	
};

class Boue: public Surface
{
	public:
		Boue();
		
		Boue(int, int, int, int);
		
		Boue(Boue const&);
		
		~Boue();
		
		void afficher(SDL_Surface* ecran);
		
		TypeSurface getType();	
};
#endif
