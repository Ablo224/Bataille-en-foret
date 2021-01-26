#ifndef Relief_h
#define Relief_h
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include <cmath> 
#include <iostream>
using namespace std;

enum TypeRelief
{
	COLINE,
	CREUX
};

class Relief
{
	protected:
		int x, y;
		int x_size, y_size;
		int hauteur;
		TypeRelief type;
	
	public:
		//destructeur
		virtual ~Relief() = 0;
		
		//accesseur
		virtual void afficher(SDL_Surface*) = 0;
		
		int getX();
		
		int getY();
		
		int get_x_size();
		
		int get_y_size();
		
		int get_hauteur();
		
		virtual TypeRelief getType() = 0;
};

class Coline : public Relief
{
	public:
		Coline();
		
		Coline(int, int, int, int);
		
		Coline(Coline const&);
		
		~Coline();
		
		void afficher(SDL_Surface*);
		
		TypeRelief getType();
};

class Creux : public Relief
{	
	public:
		Creux();
		
		Creux(int, int, int, int);
		
		Creux(Creux const&);
		
		~Creux();
		
		void afficher(SDL_Surface*);
		
		TypeRelief getType();
};

#endif
