#ifndef Obstacle_h
#define Obstacle_h
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include <cmath> 
#include <iostream>
using namespace std;

enum TypeObstacle
{
	ARBRE,
	PETIT_ARBRE,
	ROCHER,
	PETIT_ROCHER,
	MURET
};

enum Dir
{
	HORIZONTAL,
	VERTICAL
};

class Obstacle
{
	protected:
		int x, y;
		int x_size, y_size;
		int hauteur;
		int vie;
		TypeObstacle type;
		Dir direction = HORIZONTAL;
		
	
	public:
		//destructeur
		virtual ~Obstacle() = 0;
		
		//accesseur
		virtual void afficher(SDL_Surface*) = 0;
		
		int getX();
		
		int getY();

		int get_x_size();
		
		int get_y_size();
		
		int get_hauteur();
		
		int get_vie();
					
		Dir getDir();
		
		virtual TypeObstacle getType() = 0;
		
		//modificateur
		void set_vie(int);
};

class Arbre: public Obstacle
{
	public:
		Arbre();
		
		Arbre(int, int);
		
		Arbre(Arbre const&);
		
		~Arbre();
		
		void afficher(SDL_Surface*);
		
		TypeObstacle getType();
};

class Petit_Arbre: public Obstacle
{
	public:
		Petit_Arbre();
		
		Petit_Arbre(int, int);
		
		Petit_Arbre(Petit_Arbre const&);
		
		~Petit_Arbre();
		
		void afficher(SDL_Surface*);
		
		TypeObstacle getType();
};

class Rocher: public Obstacle
{
	public:
		Rocher();
		
		Rocher(int, int);
		
		Rocher(Rocher const&);
		
		~Rocher();
		
		void afficher(SDL_Surface*);
		
		TypeObstacle getType();
};

class Petit_Rocher: public Obstacle
{
	public:
		Petit_Rocher();
		
		Petit_Rocher(int, int);
		
		Petit_Rocher(Petit_Rocher const&);
		
		~Petit_Rocher();
		
		void afficher(SDL_Surface*);
		
		TypeObstacle getType();
};

class Muret: public Obstacle
{
	public:
		Muret();
		
		Muret(int, int, Dir);
		
		Muret(Muret const&);
		
		~Muret();
		
		void afficher(SDL_Surface*);
		
		TypeObstacle getType();
};

#endif
