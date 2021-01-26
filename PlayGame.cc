#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Foret.h"
#include "Surface.h"
#include <algorithm>
#include <string> 
#include <cmath> 
#include <iostream>
using namespace std;

const int SSize = 32;

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

int waitTB()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
		switch(event.type) 
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_t: /* appui sur t */
						return 0;
					break;
					
					case SDLK_b: /* appui sur b */
						return 1;
					break;
					
					case SDLK_ESCAPE: /* appui sur echap */
						return 2;
					break;
					
					default:
					break;
				}
			break;
		}
    }
    return -1;
}

int wait12()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
		switch(event.type) 
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_KP1: /* appui sur 1 */
						return 1;
					break;
					
					case SDLK_KP2: /* appui sur 2 */
						return 2;
					break;
					
					case 38:
						return 1;
					break;
					
					case 233:
						return 2;
					break;
					
					case SDLK_ESCAPE: /* appui sur escape */
						return 3;
					break;
					
					default:
						cout << event.key.keysym.sym << endl;
					break;
				}
			break;
		}
    }
    return -1;
}

bool waitClic(int& x, int& y)
{
	SDL_Event event;
	
	while(1)
	{
		SDL_WaitEvent(&event); 
		switch(event.type) 
		{
			case SDL_MOUSEBUTTONUP: /* Clic de la souris */
				x = event.button.x;
				y = event.button.y;
				return true;
			break;
			
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
						return false;
					break;
					
					default:
					break;
				}
			break;
		}
	}
}

int waitForce(int xa, int ya, SDL_Surface* ecran, Foret* f)
{
	int force = 1;
	SDL_Event event;
	SDL_Surface* SurfaceAccess = IMG_Load("Ressources/Access.png");
	SDL_Rect Position;
	
	f->afficher(ecran);
							
	for(int xb=0; xb < f->get_x_size(); xb++){
		for(int yb=0; yb < f->get_y_size(); yb++){
			if(sqrt(pow(xb-xa,2)+pow(yb-ya,2)) <= force){
				Position.x = xb*SSize;
				Position.y = yb*SSize;
				SDL_BlitSurface(SurfaceAccess, NULL, ecran, &Position);}}}
	SDL_Flip(ecran);
	
	while(1)
	{
		SDL_WaitEvent(&event); 
		switch(event.type) 
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
						return -1;
					break;
					
					case SDLK_PAGEUP:
						force = (force==5)?5:force+1;
						
						f->afficher(ecran);
							
						for(int xb=0; xb < f->get_x_size(); xb++){
							for(int yb=0; yb < f->get_y_size(); yb++){
								if(sqrt(pow(xb-xa,2)+pow(yb-ya,2)) <= force){
									Position.x = xb*SSize;
									Position.y = yb*SSize;
									SDL_BlitSurface(SurfaceAccess, NULL, ecran, &Position);
									SDL_Flip(ecran);}}}
						
					break;
					
					case SDLK_PAGEDOWN:
						force = (force==1)?1:force-1;
						
						f->afficher(ecran);
						
					for(int xb=0; xb < f->get_x_size(); xb++){
						for(int yb=0; yb < f->get_y_size(); yb++){
							if(sqrt(pow(xb-xa,2)+pow(yb-ya,2)) <= force){
								Position.x = xb*SSize;
								Position.y = yb*SSize;
								SDL_BlitSurface(SurfaceAccess, NULL, ecran, &Position);
								SDL_Flip(ecran);}}}
						
					break;
					
					case SDLK_RETURN: /* Appui sur la touche Echap, on arrête le programme */
						return force;
					break;					
					
					default:
					break;
				}
			break;
		}
	}
	
	SDL_FreeSurface(SurfaceAccess);
	return force;
}

int rand_a_b(int a, int b)
{
	int res = rand()%(b-a)+a;
	return res;
}

/*
 * Retourne 0 par default
 * 			-1 si il faut quitter
 * 			1 si le joueur 1 a gagner
 * 			2 si le joueur 2 a	gagner
 */ 
int jouerTour(Foret* f, Case*** map, int i, bool alea, SDL_Surface* ecran)
{
	int vainqueur = 0;
	
	if(i==0)
		cout << "TOUR DU JOUEUR BLANC (vie = " << f->get_personnages()[i]->get_vie() << ")"<<endl;
	else
		cout << "TOUR DU JOUEUR ROUGE (vie = " << f->get_personnages()[i]->get_vie() << ")" << endl;
	
	cout << "Tirer ou bouger ? (T ou B)" << endl;
	int TB = -1;
	
	if(alea)
		TB = rand()%2;
	else
		TB = waitTB();
		
	switch(TB){
		case 0:
			{
			int x,y = 0;
			if(f->get_personnages()[i]->get_vie() <= 0){
				cout << "vous etes trop fatique pour tirer" << endl;
				f->get_personnages()[i]->set_vie(f->get_personnages()[i]->get_vie()+2);
				return 0;}
					
			//afficher les cases disponible pour un tire
			f->showShootable(map, i, ecran);
			
			SDL_Delay(1000);
			
			//attendre un clic
			cout << "Cliquer pour définir un point de chute" << endl;
			if(alea){
				do{
					x = rand_a_b(0,f->get_x_size());
					y = rand_a_b(0,f->get_y_size());
				}while(!f->isShootable(map,i,x,y));
			}
			else{
				do{
					waitClic(x,y);
					x = x/SSize;
					y = y/SSize;
				}while(!f->isShootable(map,i,x,y));}
			
			//choisir la force du tir
			f->afficher(ecran);
			int force = 1;
			cout << "Page up et page down pour augmenter et reduire la force" << endl;
			
			if(alea){
				force = rand_a_b(1,5);
				SDL_Surface* SurfaceAccess = IMG_Load("Ressources/Access.png");
				SDL_Rect Position;
				
				for(int xb=0; xb < f->get_x_size(); xb++){
					for(int yb=0; yb < f->get_y_size(); yb++){
						if(sqrt(pow(xb-x,2)+pow(yb-y,2)) <= force){
							Position.x = xb*SSize;
							Position.y = yb*SSize;
							SDL_BlitSurface(SurfaceAccess, NULL, ecran, &Position);}}}
				SDL_Flip(ecran);
				
				SDL_FreeSurface(SurfaceAccess);
				SDL_Delay(1000);}
			else
				force = waitForce(x,y,ecran,f);
			
			if(force == -1)
				return -1;
				
			//retirer la vie au personnage
			f->get_personnages()[i]->set_vie(f->get_personnages()[i]->get_vie()-force);
					
			//afficher et faire les changements
			Obstacle* ObsAdress[25] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //tableau d'adresse des obstacles
			for(int xb = 0; xb < f->get_x_size(); xb++){
				for(int yb = 0; yb < f->get_y_size(); yb++){
					//si map de xb yb est un obstacle et qu'il n'est pas deja dans le tableau l'ajouter
					if(map[xb][yb]->CaseObstacle != NULL && sqrt(pow(xb-x,2)+pow(yb-y,2))<=force){
						bool flag = true;
						int n;
						for(n = 0; n < 25; n++){
							if(ObsAdress[n] == NULL)
								break;
							if(ObsAdress[n] == map[xb][yb]->CaseObstacle)
								flag = false;}
						if(flag)
							ObsAdress[n] = map[xb][yb]->CaseObstacle;}
					
					if(map[xb][yb]->CasePersonnage != NULL && sqrt(pow(xb-x,2)+pow(yb-y,2))<=force){
						if(i == 0 && map[xb][yb]->CasePersonnage == f->get_personnages()[1]){
							vainqueur = 1; //joueur 1 mais personnage 0
							cout << "LE JOUEUR BLANC GAGNE !!!" << endl;
						}
						if(i == 1 && map[xb][yb]->CasePersonnage == f->get_personnages()[0]){
							vainqueur = 2; //joueur 2 mais personnage 1
							cout << "LE JOUEUR ROUGE GAGNE !!!" << endl;
						}}
					
			}}
			
			//deteriorer tous les obstacles dans le tableau
			int n = 0;
			while(ObsAdress[n] != NULL){
				ObsAdress[n]->set_vie(ObsAdress[n]->get_vie()-force);
				n++;}
						
			//supprimer les obstacles sans vie de map et foret
			n = 0;
			
			//supprimer de la map
			while(ObsAdress[n] != NULL){
				if(ObsAdress[n]->get_vie()<= 0){
					for(int xb = 0; xb < f->get_x_size(); xb++){
						for(int yb = 0; yb < f->get_y_size(); yb++){
							if(map[xb][yb]->CaseObstacle == ObsAdress[n]){
								map[xb][yb]->hauteur -= ObsAdress[n]->get_hauteur();
								map[xb][yb]->libre = true;
								map[xb][yb]->CaseObstacle = NULL;}}}}
			n++;}
					
			//supprimer de la foret
			n = 0;
			while(ObsAdress[n] != NULL){
				if(ObsAdress[n]->get_vie()<= 0){
					f->delObstacle(ObsAdress[n]->getX(),ObsAdress[n]->getY());}
			n++;}	
			}
		break;
			
		case 1:
			{int x, y =0;
		
			// afficher les cases ou il peut de placer
			f->showAccess(map,i,ecran);
					
			// attendre un clic et voir si elle est accessible
			cout << "Cliquer sur une case grise pour vous y rendre" << endl;
			if(alea){
				do{
					x = rand_a_b(0,f->get_x_size());
					y = rand_a_b(0,f->get_y_size());
				}while(!f->isAccess(map,i,x,y));
			}
			else{
				do{
					waitClic(x,y);
					x = x/SSize;
					y = y/SSize;
				}while(!f->isAccess(map,i,x,y));}

						
			// déplacer le joueur
			map[f->get_personnages()[i]->get_x()+(f->get_x_size()/2)][f->get_personnages()[i]->get_y()+(f->get_y_size()/2)]->CasePersonnage = NULL;
			map[f->get_personnages()[i]->get_x()+(f->get_x_size()/2)][f->get_personnages()[i]->get_y()+(f->get_y_size()/2)]->libre = true;
			
			f->movePersonnage(i,x-(f->get_x_size()/2),y-(f->get_y_size()/2));
			f->get_personnages()[i]->set_vie(f->get_personnages()[i]->get_vie()+2);
			
			map[f->get_personnages()[i]->get_x()+(f->get_x_size()/2)][f->get_personnages()[i]->get_y()+(f->get_y_size()/2)]->CasePersonnage = f->get_personnages()[i];
			map[f->get_personnages()[i]->get_x()+(f->get_x_size()/2)][f->get_personnages()[i]->get_y()+(f->get_y_size()/2)]->libre = false;	}	
		break;
		
		case 2:
			return -1;
		break;
	}
	
	
	return vainqueur;
}

int main()
{
	string reponse;
	SDL_Surface *ecran = NULL;
	int nbPlayer;
	Foret* f;
	srand(time(NULL));
	
	cout << "Sur quelle map voulez vous jouer ?" << endl;
	cin >> reponse;
	transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
	reponse = "map/" + reponse + ".txt";
	
	//appeller le constructeur avec l'url
	f = new Foret(reponse);

	f->addPersonnage(20);
	
	f->addPersonnage(20);
	
	// creer une map a partir des obstacles
	Case*** map = f->CreateMap();
	
	// ouvrir une fenetre en fonction des dimensions de la foret
	ecran = SDL_SetVideoMode(f->get_x_size()*SSize, f->get_y_size()*SSize, 32, SDL_HWSURFACE);	
	
	// afficher Foret
	f->afficher(ecran);

	//demander le nombre de joueurs
	cout << "Nombre de joueurs ? (1 ou 2)" << endl;
	nbPlayer = wait12();
	
	cout << "Appuyer sur echap pour quitter la partie" << endl;

	if(nbPlayer == 1){
		int i = rand()%2;
		
		while(jouerTour(f,map,i,i,ecran)==0){
			i = (i==0)?1:0;
			f->afficher(ecran);}
	}


	if(nbPlayer == 2){
		int i = rand()%2;
		
		while(jouerTour(f,map,i,false,ecran)==0){
			i = (i==0)?1:0;
			f->afficher(ecran);	
	}
	}
	

	f->DeleteMap(map);

	delete f;
}
