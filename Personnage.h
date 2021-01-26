#ifndef Personnage_h
#define Personnage_h
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include <cmath> 
#include <iostream>
using namespace std;

enum Direction
{
	HAUT, // 0°
	HAUT_DROITE, //45 °
	DROITE, // 90°
	BAS_DROITE, // 135°
	BAS, // 180°
	BAS_GAUCHE, // 225°
	GAUCHE, // 270°
	HAUT_GAUCHE // 315°
};

enum Color
{
	BLANC,
	ROUGE
};

struct Tire
{
	unsigned int angle;
	unsigned int portee;
	unsigned int force;
};

class Personnage
{
	private:
		int x,y;
		Direction dir;
		int vie;
		Color c;
		
	public:
		Personnage();
		
		Personnage(int, int, Direction, int, Color);
		
		Personnage(Personnage const &);
		
		~Personnage();
		
		int get_x();
		
		int get_y();
		
		int get_dir();
		
		int get_vie();
		
		void set_x(int);
		
		void set_y(int);
		
		void set_dir(Direction);
		
		void set_vie(int);
		
		void deplacer(int, int, Direction);
		
		void afficher(SDL_Surface*);
		
};

#endif
