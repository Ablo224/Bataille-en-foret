#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Foret.h"
#include "Surface.h"
#include <cmath> 
#include <iostream>
using namespace std;

void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
} 

int main()
{
	//Ouverture d'une fenetre de taille 640*480 de 32 couleurs
	SDL_Surface *ecran = NULL;
	ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	
	// Changement du nom de la fenetre
	SDL_WM_SetCaption("Bataille en forêt", NULL);
	
	//Changement de la couleur de la surface
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
	
		
	Foret f(50,50);

	f.afficher(ecran);
	
	f.addSurface(18,18,7,7,EAU);
	
	f.addSurface(-25,-25,7,7,SABLE);
	
	f.addSurface(-25,18,7,7,BOUE);
	
	f.addRelief(0,0,5,5,COLINE);
	
	f.addRelief(10,10,6,6,CREUX);
	
	f.addObstacle(-8,-10,PETIT_ARBRE);
	
	f.addObstacle(-10,-10,ARBRE);
	
	f.addObstacle(10,-10,ROCHER);
	
	f.addObstacle(-10,10,PETIT_ROCHER);
	
	f.addObstacle(-12,12,MURET,HORIZONTAL);
	
	f.addObstacle(-12,13,MURET,VERTICAL);
	
	f.addObstacle(-12,14,MURET,VERTICAL);
	
	f.afficher(ecran);
	
	pause();
	
	f.afficher(ecran);
	
	pause();
}
