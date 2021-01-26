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
					case SDLK_q: /* Appui sur la touche Echap, on arrête le programme */
						return false;
					break;
					
					default:
					break;
				}
			break;
		}
	}
}

int main()
{
	string reponse;
	SDL_Surface *ecran = NULL;
	Foret* f;
	int xa, ya, xb, yb, l, L;
	
	// clean de l'affichage
	system("clear");
	
		do{
		cout << "Comment souhaiter vous créer votre Foret: la charger (L), la créer (C) ou QUITTER (Q) ?" << endl;
		cin >> reponse;
		transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
		
		if(reponse == "l"){
			// demander l'url
			reponse = "";
			cout << "Entrer le nom de la map" << endl;
			cin >> reponse;
			transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
			reponse = "map/" + reponse + ".txt";
			// appeller le constructeur avec l'url
			f = new Foret(reponse);
			// ouvrir une fenetre en fonction des dimensions de la foret
			ecran = SDL_SetVideoMode(f->get_x_size()*SSize, f->get_y_size()*SSize, 32, SDL_HWSURFACE);
			break;}
			
		else if(reponse == "c"){
			int largeur, longueur;
			// demander la largeur et la longueur
			cout << "! ATTENTION les valeurs suivantes doivent etre comprises entre 10 et 30 !" << endl;
			cout << "Taper la largeur (y) de la foret: " << endl;
			cin >> largeur;
			cout << "Taper la longueur (x) de la foret: " << endl;
			cin >> longueur;
			// appeller le constructeur avec largeur et longueur
			f = new Foret(longueur, largeur);
			// ouvrir une fenetre en fonction des dimensions de la foret
			ecran = SDL_SetVideoMode(f->get_x_size()*SSize, f->get_y_size()*SSize, 32, SDL_HWSURFACE);
			break;
			}
		else if(reponse == "q"){
			exit(0);
			}
		else
			cout << "Cette réponse n'est pas accépté !!";
		reponse = "";
	}while(1);
	f->afficher(ecran);
	
	while(1){
		// choisir entre relief, surface et obstacle
		system("clear");
		do{
			reponse = "";
			cout << "Que voulez vous faire ?\n- Ajouter un relief(R)\n- Ajouter une surface(S)\n- Supprimer un obstacle(O)\n- Quitter(Q)" << endl;
			cin >> reponse;
			transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
		}while(reponse != "r" && reponse != "s" && reponse != "o"  && reponse != "q");
		
		// si quitter
		if(reponse == "q"){
			break;}
		
		//si mode relief
		else if(reponse == "r"){
			// Mode de creation des reliefs
			cout << "Ajout des reliefs" <<endl;
			// entrer dans une bouble
			while(1){
				// !tant que! taper sur le terminal le relief escape pour quitter
				do{
					reponse = "";
					cout << "\nQue voulez vous faire ?\n- Ajouter un mont (M)\n- Ajouter une vallée(V)\n- Supprimer un relief(D)\n- Quitter le mode relief (Q)" << endl;
					cin >> reponse;
					transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
				}while(reponse != "m" && reponse != "v" && reponse != "d"  && reponse != "q") ;
				// si la reponse est de quitter
				if(reponse == "q"){
					break;}
				// agir selon la reponse
				else if(reponse == "m"){
					cout << "Cliquer deux fois pour definir les coordonnées du mont ou appuyer sur q pour quitter" << endl;
					while(waitClic(xa,ya) && waitClic(xb,yb)){
						xa = xa/SSize-(f->get_x_size()/2);
						xb = xb/SSize-(f->get_x_size()/2);
						ya = ya/SSize-(f->get_y_size()/2);
						yb = yb/SSize-(f->get_y_size()/2);
						l = sqrt(pow(xa-xb,2));
						L = sqrt(pow(ya-yb,2));
						f->addRelief(min(xa,xb),min(ya,yb),l,L,COLINE);
						f->afficher(ecran);}}
				
				else if(reponse == "v"){
					cout << "Cliquer deux fois pour definir les coordonnées de la vallée ou appuyer sur q pour quitter" << endl;
					while(waitClic(xa,ya) && waitClic(xb,yb)){
						xa = xa/SSize-(f->get_x_size()/2);
						xb = xb/SSize-(f->get_x_size()/2);
						ya = ya/SSize-(f->get_y_size()/2);
						yb = yb/SSize-(f->get_y_size()/2);
						l = sqrt(pow(xa-xb,2));
						L = sqrt(pow(ya-yb,2));
						f->addRelief(min(xa,xb),min(ya,yb),l,L,CREUX);
						f->afficher(ecran);}}
				
				else if(reponse == "d"){
					cout << "Cliquer en haut a gauche du relief" << endl;
					while(waitClic(xa,ya)){
						xa = xa/SSize-(f->get_x_size()/2);
						ya = ya/SSize-(f->get_y_size()/2);
						f->delRelief(xa,ya);
						f->afficher(ecran);}}}}
			
			else if(reponse == "s"){
				cout << "Mode ajout de surface" << endl;
				// entrer dans une boucle
				while(1){
					// !tant que! taper sur le terminal la surface souhaiter escape pour quitter (grass pour effacer)
					do{
						reponse = "";
						cout << "\nQue voulez vous faire ?\n- Ajouter de la boue(B)\n- Ajouter du sable(S)\n- Ajouter de l'eau(E)\n- Supprimer une surface(D)\n- Quitter le mode surface (Q)" << endl;
						cin >> reponse;
						transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
					}while(reponse != "b" && reponse != "s" && reponse != "e" && reponse !="d"  && reponse != "q") ;
					// si la reponse est de quitter
					if(reponse == "q"){
						break;}
					// agir selon la reponse
					else if(reponse == "b"){
					cout << "Cliquer deux fois pour definir les coordonnées de la boue ou appuyer sur q pour quitter" << endl;
						while(waitClic(xa,ya) && waitClic(xb,yb)){
							xa = xa/SSize-(f->get_x_size()/2);
							xb = xb/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							yb = yb/SSize-(f->get_y_size()/2);
							l = sqrt(pow(xa-xb,2));
							L = sqrt(pow(ya-yb,2));
							f->addSurface(min(xa,xb),min(ya,yb),l,L,BOUE);
							f->afficher(ecran);}}
					
					else if(reponse == "e"){
					cout << "Cliquer deux fois pour definir les coordonnées de l'eau ou appuyer sur q pour quitter" << endl;
						while(waitClic(xa,ya) && waitClic(xb,yb)){
							xa = xa/SSize-(f->get_x_size()/2);
							xb = xb/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							yb = yb/SSize-(f->get_y_size()/2);
							l = sqrt(pow(xa-xb,2));
							L = sqrt(pow(ya-yb,2));
							f->addSurface(min(xa,xb),min(ya,yb),l,L,EAU);
							f->afficher(ecran);}}
					
					else if(reponse == "s"){
					cout << "Cliquer deux fois pour definir les coordonnées du sable ou appuyer sur q pour quitter" << endl;
						while(waitClic(xa,ya) && waitClic(xb,yb)){
							xa = xa/SSize-(f->get_x_size()/2);
							xb = xb/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							yb = yb/SSize-(f->get_y_size()/2);
							l = sqrt(pow(xa-xb,2));
							L = sqrt(pow(ya-yb,2));
							f->addSurface(min(xa,xb),min(ya,yb),l,L,SABLE);
							f->afficher(ecran);}}
							
					else if(reponse == "d"){
						cout << "Cliquer en haut a gauche de la surface" << endl;
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->delSurface(xa,ya);
							f->afficher(ecran);}}}}
							
			else if(reponse == "o"){
				// Mode creation d'obstacle
				cout << "Mode ajout d'Obstacle" << endl;
				// entrer dans la boucle
				while(1){	
					// demander quelle obstacle il souhaite ajouter
					do{
						reponse = "";
						cout << "\nQue voulez vous faire ?\n- Ajouter un Arbre(A)\n- Ajouter un petit Arbre(PA)\n- Ajouter un Rocher(R)\n- Ajouter un petit Rocher(PR)\n- Ajouter un muret horizontale(MH)\n- Ajouter un muret verticale(MV)\n- Supprimer un obstacle(D)\n- Quitter le mode obstacle(Q)" << endl;
						cin >> reponse;
						transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
					}while(reponse != "a" && reponse != "pa" && reponse != "r" && reponse != "pr" && reponse != "mh" && reponse != "mv" && reponse != "d" && reponse != "q");
					
					// agir selon la selection
					if(reponse == "q"){
						break;}
					if(reponse == "a"){
						// decire les commandes possibles
						cout << "Cliquer pour placer l'arbre ou appuyer sur q pour quitter" << endl;
						// effectuer les ajouts
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->addObstacle(xa,ya,ARBRE);
							f->afficher(ecran);}}
					if(reponse == "pa"){
						// decire les commandes possibles
						cout << "Cliquer pour placer le petit arbre ou appuyer sur q pour quitter" << endl;
						// effectuer les ajouts
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->addObstacle(xa,ya,PETIT_ARBRE);
							f->afficher(ecran);}}	
					else if(reponse == "r"){
						// decire les commandes possibles
						cout << "Cliquer pour placer le rocher ou appuyer sur q pour quitter" << endl;
						// effectuer les ajouts
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->addObstacle(xa,ya,ROCHER);
							f->afficher(ecran);}}	
					else if(reponse == "pr"){
						// decire les commandes possibles
						cout << "Cliquer pour placer le petit_rocher ou appuyer sur q pour quitter" << endl;
						// effectuer les ajouts
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->addObstacle(xa,ya,PETIT_ROCHER);
							f->afficher(ecran);}}
					else if(reponse == "mh"){
						// decire les commandes possibles
						cout << "Cliquer pour placer le muret horizontal ou appuyer sur q pour quitter" << endl;
						// effectuer les ajouts
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->addObstacle(xa,ya,MURET,HORIZONTAL);
							f->afficher(ecran);}}
					else if(reponse == "mv"){
						// decire les commandes possibles
						cout << "Cliquer pour placer le muret horizontal ou appuyer sur q pour quitter" << endl;
						// effectuer les ajouts
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->addObstacle(xa,ya,MURET,VERTICAL);
							f->afficher(ecran);}}
					else if(reponse == "d"){
						// decire les commandes possibles
						cout << "Cliquer en haut a gauche de l'obstacle pour le supprimer ou appuyer sur q pour quitter" << endl;
						// effectuer les ajouts
						while(waitClic(xa,ya)){
							xa = xa/SSize-(f->get_x_size()/2);
							ya = ya/SSize-(f->get_y_size()/2);
							f->delObstacle(xa,ya);
							f->afficher(ecran);}}}}}
	// Demander si on veut sauvegarder
	reponse = "";
	cout << "Voulez vous sauvegarder la map ?(y/n)" << endl;
	cin >> reponse;
	transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
	if(reponse == "y"){
		reponse = "";
		cout << "Entrer le nom de la map" << endl;
		cin >> reponse;
		transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
		reponse = "map/" + reponse + ".txt";
		f->save_to(reponse);}
	
	
	delete f;
	system("clear");
}
