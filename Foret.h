#ifndef Foret_h
#define Foret_h
#include <list> 
#include <iterator> 
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Surface.h"
#include "Relief.h"
#include "Obstacle.h"
#include "Personnage.h"
#include <cmath> 
#include <iostream>
using namespace std;

struct Case
{
	int hauteur;
	// entier indiquant si la case est libre ou non
	bool libre;
	// pointeur vers une hypothetique surface
	Surface* CaseSurface;
	// pointeur vers un hyphothetique relief
	Relief* CaseRelief;
	// pointeur vers un hypothetique obstacle
	Obstacle* CaseObstacle;
	// pointeur vers un hypothetique personnage
	Personnage* CasePersonnage;
};

class Foret
{
	protected:
		int x_size, y_size;
		std::list<Surface*> Surfaces;
		std::list<Relief*> Reliefs;
		std::list<Obstacle*> Obstacles;
		Personnage* Personnages[2];
		SDL_Rect ForetPosition;
		SDL_Surface* ForetSurface;
		
	public:
		//constructeur
		Foret();
		
		Foret(int, int);
		
		Foret(string);
		
		Foret(Foret const& autre);
		
		//destructeur
		~Foret();
		
		//accesseur
		void afficher(SDL_Surface* ecran);
		
		bool isIn(int, int);
		
		int get_x_size();
		
		int get_y_size();
		
		void afficherHitBox(Case*** map, SDL_Surface* ecran);
		
		void showAccess(Case*** map, int i ,SDL_Surface* ecran);
		
		bool isAccess(Case*** map, int i, int x, int y);
		
		void showShootable(Case*** map, int i, SDL_Surface* ecran);
		
		bool isShootable(Case*** map, int i, int x, int y);
		
		Personnage** get_personnages();
			
		//modificateur
		void addSurface(int, int, int, int, TypeSurface);
		
		void addRelief(int, int, int, int, TypeRelief);
		
		void addObstacle(int, int, TypeObstacle, Dir = HORIZONTAL);
		
		void addPersonnage(int);
		
		void movePersonnage(int, int, int);
		
		/* tirer avec personnage */
		
		void delSurface(int, int);

		void delRelief(int, int);

		void delObstacle(int, int);

		void delPersonnage(int);
		
		//ecriture d'un fichier dans le dossier map
		void save_to(string url);
		
		//creation de la map
		Case*** CreateMap();
		
		void DeleteMap(Case***);
};

#endif
