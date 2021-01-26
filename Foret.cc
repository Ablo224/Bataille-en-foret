#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "math.h"
#include "Foret.h"
#include "Surface.h"
#include "Obstacle.h"
#include "Relief.h"
#include "stdio.h"
#include <sstream>
#include <string>
#include <cmath> 
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

const int SSize = 32;

//constructeur
Foret::Foret(): x_size(20), y_size(20)
{
	ForetPosition.x = ForetPosition.y = 0;
	ForetSurface = SDL_SetVideoMode(x_size*SSize, y_size*SSize, 32, SDL_HWSURFACE);
	SDL_FillRect(ForetSurface, NULL, SDL_MapRGB(ForetSurface->format, 0, 0, 0));
	Personnages[0] = NULL;
	Personnages[1] = NULL;
}
		
Foret::Foret(int new_x, int new_y)
{
	x_size = new_x;
	y_size = new_y;
	
	if(new_x<10)
		x_size = 10;
	if(new_x>30)
		x_size = 30;
	if(new_y<10)
		y_size = 10;
	if(new_y>30)
		y_size = 30;
	
	Personnages[0] = NULL;
	Personnages[1] = NULL;
	
	ForetPosition.x = ForetPosition.y = 0;
	ForetSurface = SDL_SetVideoMode(x_size*SSize, y_size*SSize, 32, SDL_HWSURFACE);
	SDL_FillRect(ForetSurface, NULL, SDL_MapRGB(ForetSurface->format, 0, 0, 0));
} 

// constructeur de recopie depuis un fichier
Foret::Foret(string url)
{
	 std::ifstream myfile (url, std::ifstream::in);
	 string line;
	 int X, Y, LO, LA;
	 
	 getline(myfile,line);
	 x_size = stoi(line);
	 
	 getline(myfile,line);
	 y_size = stoi(line);
	 
	 getline(myfile,line); 
	 
	 while(getline(myfile,line) && line != "SURFACE") // RELIEF
	 {
		istringstream iss(line);
		string t;
		Relief* to_add = NULL;
		
		if(!(iss >> X >> Y >> LO >> LA >> t)){
			cerr << "Probleme lecture ligne relief" << endl;
			break;}
		
		if(t == "COLINE")
				to_add = new Coline(X, Y, LO, LA);
			
		if(t == "CREUX")
				to_add = new Creux(X, Y, LO, LA);
					
		if(to_add != NULL){ 
			Reliefs.insert(Reliefs.end(),to_add);}}
	 
	 while(getline(myfile,line) && line != "OBSTACLE") // SURFACE
	 {
		istringstream iss(line);
		string t;
		Surface* to_add = NULL;
		
		if(!(iss >> X >> Y >> LO >> LA >> t)){
			cerr << "Probleme lecture ligne surface" << endl;
			break;}
			
			if(t == "EAU")
				to_add = new Eau(X, Y, LO, LA);
			
			if(t == "SABLE")
				to_add = new Sable(X, Y, LO, LA);

			if(t == "BOUE")
				to_add = new Boue(X, Y, LO, LA);

		if(to_add != NULL){ 
			Surfaces.insert(Surfaces.end(),to_add);}}
			
		while(getline(myfile,line) && line != "END") // OBSTACLE
		 {
			istringstream iss(line);
			string t, d;
			Obstacle* to_add = NULL;
			
			if(!(iss >> X >> Y >> t)){
				cerr << "Probleme lecture ligne obstacle" << endl;
				break;}

			if(t == "ARBRE")
					to_add = new Arbre(X, Y);
					
			if(t == "PETIT_ARBRE")
					to_add = new Petit_Arbre(X, Y);
			
			if(t == "ROCHER")
				to_add = new Rocher(X, Y);

			if(t == "PETIT_ROCHER")
				to_add = new Petit_Rocher(X, Y);

			if(t == "MURET"){
				if(!(iss >> d)){
					cerr << "Probleme lecture ligne obstacle" << endl;
					break;}
				if(d == "HORIZONTAL")
					to_add = new Muret(X, Y, HORIZONTAL);
				if(d == "VERTICAL")
					to_add = new Muret(X, Y, VERTICAL);}
				
			if(to_add != NULL){
				Obstacles.insert(Obstacles.end(),to_add);}}
	  
	Personnages[0] = NULL;
	Personnages[1] = NULL; 
	
	ForetPosition.x = ForetPosition.y = 0;
	ForetSurface = SDL_SetVideoMode(x_size*SSize, y_size*SSize, 32, SDL_HWSURFACE);
	SDL_FillRect(ForetSurface, NULL, SDL_MapRGB(ForetSurface->format, 0, 0, 0));
}
		
Foret::Foret(Foret const& autre)
{
	x_size = autre.x_size;
	y_size = autre.y_size;
	
	Personnages[0] = NULL;
	Personnages[1] = NULL;
	
	ForetPosition.x = ForetPosition.y = 0;
	ForetSurface = SDL_SetVideoMode(x_size*SSize, y_size*SSize, 32, SDL_HWSURFACE);
	SDL_FillRect(ForetSurface, NULL, SDL_MapRGB(ForetSurface->format, 0, 0, 0));
}

//destructeur
Foret::~Foret()
{

	list<Relief*> :: iterator iit; 
    for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
		delete *iit;}

	list<Surface*> :: iterator it;
    for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
		delete *it;}
	
	list<Obstacle*> :: iterator iiit; 
    for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
		delete *iiit;}
	
	if(Personnages[0] != NULL)
		delete Personnages[0];
	if(Personnages[1] != NULL)
		delete Personnages[1];
	
	SDL_FreeSurface(ForetSurface);
}

//accesseur
void Foret::afficher(SDL_Surface* ecran)
{
	SDL_Surface* SurfaceHerbe = IMG_Load("Ressources/Grass1.png");
	SDL_Rect HerbePosition;
	
	for(int i=0; i<x_size; i++){
		for(int j=0; j<y_size; j++){
			HerbePosition.x = i*SSize;
			HerbePosition.y = j*SSize;
			SDL_BlitSurface(SurfaceHerbe, NULL, ForetSurface, &HerbePosition);}}

	for(int i=0; i<x_size; i++){
		for(int j=0; j<y_size; j++){
			list<Surface*> :: iterator it; 
			for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
				if((*it)->getX() == i-(x_size/2) && (*it)->getY() == j-(y_size/2)) (*it)->afficher(ecran);}
				
			list<Relief*> :: iterator iit; 
			for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
				if((*iit)->getX() == i-(x_size/2) && (*iit)->getY() == j-(y_size/2)) (*iit)->afficher(ecran);}}}
	
	if(Personnages[0] != NULL)
		Personnages[0]->afficher(ecran);
	if(Personnages[1] != NULL)
		Personnages[1]->afficher(ecran);
	
	for(int i=0; i<x_size; i++){
		for(int j=0; j<y_size; j++){	
			list<Obstacle*> :: iterator iiit; 
			for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
				if((*iiit)->getX() == i-(x_size/2) && (*iiit)->getY() == j-(y_size/2)) (*iiit)->afficher(ecran);}}}
		
	SDL_BlitSurface(ForetSurface, NULL, ecran, &ForetPosition);
	SDL_Flip(ecran);
	SDL_FreeSurface(SurfaceHerbe);
}

bool Foret::isIn(int x, int y)
{
	return -(x_size/2) <= x && x <= (x_size/2) && -(y_size/2) <= y && y <= (y_size/2);
}	

int Foret::get_x_size()
{
	return x_size;
}
		
int Foret::get_y_size()
{
	return y_size;
}

void Foret::afficherHitBox(Case*** map, SDL_Surface* ecran)
{
	SDL_Surface* SurfaceBug = IMG_Load("Ressources/Bug.png");
	SDL_Rect Position;
	
	for(int i=0; i< x_size; i++){
		for(int n=0; n< y_size; n++){
			Position.x = i*SSize;
			Position.y = n*SSize;
			if(map[i][n]->libre == false)
				SDL_BlitSurface(SurfaceBug, NULL, ecran, &Position);}}
				
	SDL_Flip(ecran);
	SDL_FreeSurface(SurfaceBug);
}

void Foret::showAccess(Case*** map, int i ,SDL_Surface* ecran)
{
	SDL_Surface* SurfaceAccess = IMG_Load("Ressources/Access.png");
	SDL_Rect Position;
	
	for(int xb=0; xb < x_size; xb++){
		for(int yb=0; yb < y_size; yb++){
			if(isAccess(map, i, xb, yb)){
				Position.x = xb*SSize;
				Position.y = yb*SSize;
				SDL_BlitSurface(SurfaceAccess, NULL, ecran, &Position);}}}
	
	SDL_Flip(ecran);
	SDL_FreeSurface(SurfaceAccess);
}

bool Foret::isAccess(Case*** map, int i, int xb, int yb)
{
	//recupérer la position du perso i
	int xa = Personnages[i]->get_x()+(x_size/2);
	int ya = Personnages[i]->get_y()+(y_size/2);
	
	//verifier que la distance entre les deux points est <= 5
	if(map[xa][ya]->CaseSurface != NULL){
		if(!(sqrt(pow(xb-xa,2)+pow(yb-ya,2)) <= 2)) 
			return false;}
	else{
		if(!(sqrt(pow(xb-xa,2)+pow(yb-ya,2)) <= 3)) 
			return false;}
	
	float xdiff = xb - xa;
	float ydiff = yb - ya;
	float coef = max(abs(xdiff),abs(ydiff));
	xdiff = xdiff/coef;
	ydiff = ydiff/coef;
	
	float x, y;
	
	for(x=xa, y=ya; x != xb && y != yb; x+=xdiff, y+=ydiff){
		if((!map[(int)ceil(x)][(int)ceil(y)]->libre) && x != xa && y != ya)
			return false;}
	
	if(!map[xb][yb]->libre)
		return false;
	
	return true;
}

void Foret::showShootable(Case*** map, int i, SDL_Surface* ecran)
{
	SDL_Surface* SurfaceAccess = IMG_Load("Ressources/Access.png");
	SDL_Rect Position;
	
	for(int xb=0; xb < x_size; xb++){
		for(int yb=0; yb < y_size; yb++){
			if(isShootable(map, i, xb, yb)){
				Position.x = xb*SSize;
				Position.y = yb*SSize;
				SDL_BlitSurface(SurfaceAccess, NULL, ecran, &Position);}}}
	
	SDL_Flip(ecran);
	SDL_FreeSurface(SurfaceAccess);
}
		
bool Foret::isShootable(Case*** map, int i, int xb, int yb)
{
	//recupérer la position du perso i
	int xa = Personnages[i]->get_x()+(x_size/2);
	int ya = Personnages[i]->get_y()+(y_size/2);
	int h = (map[xa][ya]->CaseRelief != NULL)? 1 + map[xa][ya]->CaseRelief->get_hauteur() : 1;
	
	//verifier que la distance entre les deux points est <= 5
	if(!(sqrt(pow(xb-xa,2)+pow(yb-ya,2)) <= 5)) 
		return false;
		
	float xdiff = xb - xa;
	float ydiff = yb - ya;
	float coef = max(abs(xdiff),abs(ydiff));
	xdiff = xdiff/coef;
	ydiff = ydiff/coef;
	
	float x, y;
	
	for(x=xa, y=ya; x != xb && y != yb; x+=xdiff, y+=ydiff){
		if(!(h > map[(int)ceil(x)][(int)ceil(y)]->hauteur))
			return false;}
	
	if(!(h > map[xb][yb]->hauteur))
		return false;
	
	return true;
}

Personnage** Foret::get_personnages()
{
	return Personnages;
}

//modificateur

/* A rajouter pour ajouter une surface:
 * 	- ajouter une surface sur un relief
 *  - ne pas pouvoir superposer les surfaces 
 */

void Foret::addSurface(int set_x, int set_y, int set_x_size, int set_y_size, TypeSurface type)
{
	Surface* to_add = NULL;
	
	if(!isIn(set_x, set_y)){
		cerr << "Coordonnées Surface hors limites !!" << endl;
		return;}
	
	list<Surface*> :: iterator it; 
    for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
		int ax1 = (*it)->getX();
		int ax2 = (*it)->getX() + (*it)->get_x_size();
		int ay1 = (*it)->getY();
		int ay2 = (*it)->getY() + (*it)->get_y_size();
		int bx1 = set_x;
		int bx2 = set_x + set_x_size;
		int by1 = set_y;
		int by2 = set_y + set_y_size;
		if(ax1<=bx2 && ax2>=bx1 && ay1<=by2 && ay2>=by1){
			cerr << "Superposition de surfaces" << endl;
			return;}}
	
	switch(type)
	{
		case EAU:
			to_add = new Eau(set_x, set_y, set_x_size, set_y_size);
		break;
		
		case SABLE:
			to_add = new Sable(set_x, set_y, set_x_size, set_y_size);
		break;
		
		case BOUE:
			to_add = new Boue(set_x, set_y, set_x_size, set_y_size);
		break;
	}
	
	if(to_add != NULL){ 
		Surfaces.insert(Surfaces.end(),to_add);}
}

/* A rajouter pout ajouter un relief
 * 	- verifier qu'il y a pas de surface de type eau en dessous
 * 	- verffier qu'il n'y a pas d'obstacle
 * 	- verifier qu'il n'y a pas de superposition de relief
 */

void Foret::addRelief(int set_x, int set_y, int set_x_size, int set_y_size, TypeRelief type)
{
	Relief* to_add = NULL;
	
	if(!isIn(set_x, set_y)){
		cerr << "Coordonnées Relief hors limites !!" << endl;
		return;}
		
	list<Relief*> :: iterator iit; 
    for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
		int ax1 = (*iit)->getX();
		int ax2 = (*iit)->getX() + (*iit)->get_x_size();
		int ay1 = (*iit)->getY();
		int ay2 = (*iit)->getY() + (*iit)->get_y_size();
		int bx1 = set_x;
		int bx2 = set_x + set_x_size;
		int by1 = set_y;
		int by2 = set_y + set_y_size;
		if(ax1<=bx2 && ax2>=bx1 && ay1<=by2 && ay2>=by1){
			cerr << "Superposition de reliefs" << endl;
			return;}}
			
	list<Obstacle*> :: iterator iiit; 
    for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
		if(set_x <= (*iiit)->getX() && (*iiit)->getX() <= set_x+set_x_size  && set_y <= (*iiit)->getY() && (*iiit)->getY() <= set_y+set_y_size){
			cerr << "Il ya un obstacle au relief" << endl;
			return;}}
			
	list<Surface*> :: iterator it; 
    for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
		int ax1 = (*it)->getX();
		int ax2 = (*it)->getX() + (*it)->get_x_size();
		int ay1 = (*it)->getY();
		int ay2 = (*it)->getY() + (*it)->get_y_size();
		int bx1 = set_x;
		int bx2 = set_x + set_x_size;
		int by1 = set_y;
		int by2 = set_y + set_y_size;
		if(ax1<=bx2 && ax2>=bx1 && ay1<=by2 && ay2>=by1 && (*it)->getType() == EAU){
			cerr << "Relief impossible sur de l'eau" << endl;
			return;}}
	
	switch(type)
	{
		case COLINE:
			to_add = new Coline(set_x, set_y, set_x_size, set_y_size);
		break;
		
		case CREUX:
			to_add = new Creux(set_x, set_y, set_x_size, set_y_size);
		break;
	}
	
	if(to_add != NULL){ 
		Reliefs.insert(Reliefs.end(),to_add);}
}

/* A rajouter pour ajouter des obstacles
 * 	- Pas sur une surface de type eau
 * 	- Pas sur les bordures d'un relief
 * 	- Pas de superpositioon
 */

void Foret::addObstacle(int set_x, int set_y, TypeObstacle type, Dir d)
{
	Obstacle* to_add = NULL;
	
	if(!isIn(set_x, set_y)){
		cerr << "Coordonnées Obstacle hors limites !!" << endl;
		return;}
		
	list<Surface*> :: iterator it; 
    for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
		if((*it)->getX() <= set_x && set_x <= (*it)->getX()+(*it)->get_x_size() && (*it)->getY() <= set_y && set_y <= (*it)->getY()+(*it)->get_y_size() && (*it)->getType() == EAU){
			cerr << "L'obstacle est sur l'eau !!" << endl;
			return;}}	
	
	list<Relief*> :: iterator iit; 
    for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
		if( (((*iit)->getX() <= set_x && set_x <= (*iit)->getX()+(*iit)->get_x_size()) && (set_y == (*iit)->getY() || set_y == (*iit)->getY()+(*iit)->get_y_size())) || (((*iit)->getY() <= set_y && set_y <= (*iit)->getY()+(*iit)->get_y_size()) && (set_x == (*iit)->getX() || set_x == (*iit)->getX()+(*iit)->get_x_size()))){
				cerr << "L'obstacle est en pente" << endl;
				return;}
		if(( (((*iit)->getX() <= set_x+1 && set_x+1 <= (*iit)->getX()+(*iit)->get_x_size()) && (set_y+1 == (*iit)->getY() || set_y+1 == (*iit)->getY()+(*iit)->get_y_size())) || (((*iit)->getY() <= set_y+1 && set_y+1 <= (*iit)->getY()+(*iit)->get_y_size()) && (set_x+1 == (*iit)->getX() || set_x+1 == (*iit)->getX()+(*iit)->get_x_size()))) && (type == ARBRE || type == ROCHER)){
				cerr << "L'obstacle est en pente" << endl;
				return;}}

	list<Obstacle*> :: iterator iiit; 
    for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
		if((*iiit)->getX() == set_x && (*iiit)->getY() == set_y){
			cerr << "Superposition d'Obstacle" << endl;
			return;}
		if( (((*iiit)->getX() <= set_x && set_x < (*iiit)->getX()+(*iiit)->get_x_size()) && (set_y == (*iiit)->getY() || set_y == (*iiit)->getY()+(*iiit)->get_y_size()-1)) || (((*iiit)->getY() <= set_y && set_y < (*iiit)->getY()+(*iiit)->get_y_size()) && (set_x == (*iiit)->getX() || set_x == (*iiit)->getX()+(*iiit)->get_x_size()-1))){
				cerr << "Superposition d'Obstacle" << endl;
				return;}}
	
	
	switch(type)
	{
		case ARBRE:
			to_add = new Arbre(set_x, set_y);
		break;
		
		case PETIT_ARBRE:
			to_add = new Petit_Arbre(set_x, set_y);
		break;
		
		case ROCHER:
			to_add = new Rocher(set_x, set_y);
		break;
		
		case PETIT_ROCHER:
			to_add = new Petit_Rocher(set_x, set_y);
		break;
		
		case MURET:
			to_add = new Muret(set_x, set_y, d);
		break;
		
		default:
		break;
	}
	
	if(to_add != NULL){ 
		Obstacles.insert(Obstacles.end(),to_add);}
}

void Foret::addPersonnage(int vie)
{
	int set_x, set_y;
	bool flag = false;
	srand((unsigned)time(NULL)); 
	
	if(Personnages[0] != NULL && Personnages[1] != NULL){
		cerr << "Tous les personnages ont déja été ajouter" << endl;
		return;}
	do{
		flag = false;
		
		set_x = (rand()%(x_size))-(x_size/2);
		set_y = (rand()%(y_size))-(y_size/2);
		
		if(!isIn(set_x, set_y)){
			flag = true;}
			
		list<Surface*> :: iterator it; 
		for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
			if((*it)->getX() <= set_x && set_x <= (*it)->getX()+(*it)->get_x_size() && (*it)->getY() <= set_y && set_y <= (*it)->getY()+(*it)->get_y_size() && (*it)->getType() == EAU){
				flag = true;}}	// personnage sur de l'eau
		
		list<Relief*> :: iterator iit; 
		for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
			if( (((*iit)->getX() <= set_x && set_x <= (*iit)->getX()+(*iit)->get_x_size()) && (set_y == (*iit)->getY() || set_y == (*iit)->getY()+(*iit)->get_y_size())) || (((*iit)->getY() <= set_y && set_y <= (*iit)->getY()+(*iit)->get_y_size()) && (set_x == (*iit)->getX() || set_x == (*iit)->getX()+(*iit)->get_x_size()))){
				flag = true;}} // personnage en pente

		list<Obstacle*> :: iterator iiit; 
		for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
			if((*iiit)->getX() == set_x && (*iiit)->getY() == set_y)
				flag = true;
			if( (((*iiit)->getX() <= set_x && set_x < (*iiit)->getX()+(*iiit)->get_x_size()) && (set_y == (*iiit)->getY() || set_y == (*iiit)->getY()+(*iiit)->get_y_size()-1)) || (((*iiit)->getY() <= set_y && set_y < (*iiit)->getY()+(*iiit)->get_y_size()) && (set_x == (*iiit)->getX() || set_x == (*iiit)->getX()+(*iiit)->get_x_size()-1))){
				flag = true;}} // personnage sur un Obstacle	
		
		if(Personnages[0] != NULL){
			if(set_x == Personnages[0]->get_x() && set_y == Personnages[0]->get_y())
				flag = true;}
			
		if(Personnages[1] != NULL){
			if(set_x == Personnages[1]->get_x() && set_y == Personnages[1]->get_y())
				flag = true;}
			
	
	}while(flag);
	
	if(Personnages[0] == NULL){
		Personnages[0] = new Personnage(set_x,set_y,BAS,vie,BLANC);
		return;}
	if(Personnages[1] == NULL){
		Personnages[1] = new Personnage(set_x,set_y,BAS,vie,ROUGE);
		return;}
	
}

void Foret::movePersonnage(int i, int new_x, int new_y)
{
	int x = Personnages[i]->get_x();
	int y = Personnages[i]->get_y();
	
	if(new_x == x && new_y > y)
		Personnages[i]->set_dir(BAS);
	else if(new_x == x && new_y < y)
		Personnages[i]->set_dir(HAUT);
	else if(new_x > x && new_y == y)
		Personnages[i]->set_dir(DROITE);
	else if(new_x < x && new_y == y)
		Personnages[i]->set_dir(GAUCHE);
	else if(new_x > x && new_y < y)
		Personnages[i]->set_dir(HAUT_DROITE);
	else if(new_x < x && new_y > y)
		Personnages[i]->set_dir(BAS_GAUCHE);
	else if(new_x > x && new_y > y)
		Personnages[i]->set_dir(BAS_DROITE);
	else if(new_x < x && new_y < y)
		Personnages[i]->set_dir(HAUT_GAUCHE);
	
	Personnages[i]->set_x(new_x);
	Personnages[i]->set_y(new_y);
}

void Foret::delSurface(int x, int y)
{
	list<Surface*> :: iterator it; 
    for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
		if((*it)->getX() == x && (*it)->getY() == y){
			delete (*it);
			Surfaces.erase(it);
			return;}}
	
	cerr << "Ce décor n'existe pas!!" << endl;
}

void Foret::delRelief(int x, int y)
{
	list<Relief*> :: iterator iit; 
    for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
		if((*iit)->getX() == x && (*iit)->getY() == y){
			delete (*iit);
			Reliefs.erase(iit);
			return;}}
			
	cerr << "Ce décor n'existe pas!!" << endl;
}

void Foret::delObstacle(int x, int y)
{
	list<Obstacle*> :: iterator iiit; 
    for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
		if((*iiit)->getX() == x && (*iiit)->getY() == y){
			delete (*iiit);
			Obstacles.erase(iiit);
			return;}}
			
	cerr << "Ce décor n'existe pas!!" << endl;
}

void Foret::delPersonnage(int index)
{
	delete Personnages[index];
}


//ecriture d'un fichier dans le dossier map
void Foret::save_to(string url)
{
	ofstream myfile;
	myfile.open(url);
	myfile << x_size <<"\n";
	myfile << y_size <<"\n";
	
	myfile << "RELIEF\n";
	
	list<Relief*> :: iterator iit; 
    for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
		switch((*iit)->getType())
		{
			case COLINE:
				myfile << (*iit)->getX() << " " << (*iit)->getY() << " " << (*iit)->get_x_size() << " " << (*iit)->get_y_size() << " COLINE\n";
			break;
			
			case CREUX:
				myfile << (*iit)->getX() << " " << (*iit)->getY() << " " << (*iit)->get_x_size() << " " << (*iit)->get_y_size() << " CREUX\n";
			break;
		}}
	
	myfile << "SURFACE\n";
	
	list<Surface*> :: iterator it; 
    for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
		switch((*it)->getType())
		{
			case EAU:
				myfile << (*it)->getX() << " " <<  (*it)->getY() << " " << (*it)->get_x_size() << " " << (*it)->get_y_size() <<  " EAU\n";
			break;
			
			case SABLE:
				myfile << (*it)->getX() << " " <<  (*it)->getY() << " " <<  (*it)->get_x_size() << " " << (*it)->get_y_size() << " SABLE\n";
			break;
			
			case BOUE:
				myfile << (*it)->getX() << " " <<  (*it)->getY() << " " <<  (*it)->get_x_size() << " " << (*it)->get_y_size() << " BOUE\n";
			break;
		}}
		
	myfile << "OBSTACLE\n";	
		
	list<Obstacle*> :: iterator iiit; 
    for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
		switch((*iiit)->getType())
	{
		case ARBRE:
			myfile << (*iiit)->getX() << " " <<  (*iiit)->getY() << " " <<  "ARBRE\n";
		break;
		
		case PETIT_ARBRE:
			myfile << (*iiit)->getX() << " " <<  (*iiit)->getY() << " " <<  "PETIT_ARBRE\n";
		break;
		
		case ROCHER:
			myfile << (*iiit)->getX() << " " <<  (*iiit)->getY() << " " <<  "ROCHER\n";
		break;
		
		case PETIT_ROCHER:
			myfile << (*iiit)->getX() << " " <<  (*iiit)->getY() << " " <<  "PETIT_ROCHER\n";
		break;
		
		case MURET:
			if((*iiit)->getDir() == HORIZONTAL)
				myfile << (*iiit)->getX() << " " <<  (*iiit)->getY() << " " <<  "MURET" << " " <<  "HORIZONTAL\n";
			else
				myfile << (*iiit)->getX() << " " <<  (*iiit)->getY() << " " <<  "MURET" << " " <<  "VERTICAL\n";
		break;
		
		default:
		break;
	}}
	
	 myfile << "END\n";	
	
	myfile.close();
}

Case*** Foret::CreateMap()
{
	Case*** to_return = new Case**[x_size];
	for(int i = 0; i < x_size; i++)
		to_return[i] = new Case*[y_size];
	
	for(int i=0; i< x_size; i++){
		for(int n=0; n< y_size; n++){
			to_return[i][n] = new Case;
			
			to_return[i][n]->libre = true;
			to_return[i][n]->CaseObstacle = NULL;
			to_return[i][n]->hauteur = 0;
			// on regarde si il y a un obstacle
			list<Obstacle*> :: iterator iiit; 
			for(iiit = Obstacles.begin(); iiit != Obstacles.end(); ++iiit){
				if((((*iiit)->getX() <= i-(x_size/2) && i-(x_size/2) < (*iiit)->getX()+(*iiit)->get_x_size()) && (n-(y_size/2) == (*iiit)->getY() || n-(y_size/2) == (*iiit)->getY()+(*iiit)->get_y_size()-1)) || (((*iiit)->getY() <= n-(y_size/2) && n-(y_size/2) < (*iiit)->getY()+(*iiit)->get_y_size()) && (i-(x_size/2) == (*iiit)->getX() || i-(x_size/2) == (*iiit)->getX()+(*iiit)->get_x_size()-1))){
						to_return[i][n]->libre = false;
						to_return[i][n]->CaseObstacle = *iiit;
						to_return[i][n]->hauteur += (*iiit)->get_hauteur();}}
	
			to_return[i][n]->CaseSurface = NULL;
			// on regarde si il y a une surface
			list<Surface*> :: iterator it; 
			for(it = Surfaces.begin(); it != Surfaces.end(); ++it){
				if((*it)->getX() <= i-(x_size/2) && i-(x_size/2) <= (*it)->getX()+(*it)->get_x_size() && (*it)->getY() <= n-(y_size/2) && n-(y_size/2) <= (*it)->getY()+(*it)->get_y_size()){
				to_return[i][n]->CaseSurface = *it;}}
			
			to_return[i][n]->CaseRelief = NULL;
			// on regade si il y a un relief
			list<Relief*> :: iterator iit; 
			for(iit = Reliefs.begin(); iit != Reliefs.end(); ++iit){
				if((*iit)->getX() <= i-(x_size/2) && i-(x_size/2) <= (*iit)->getX()+(*iit)->get_x_size() && (*iit)->getY() <= n-(y_size/2) && n-(y_size/2) <= (*iit)->getY()+(*iit)->get_y_size()){
				to_return[i][n]->CaseRelief = *iit;
				to_return[i][n]->hauteur += (*iit)->get_hauteur();}}
			
			to_return[i][n]->CasePersonnage = NULL;
			if(Personnages[0] != NULL){
				if(i == Personnages[0]->get_x()+(x_size/2) && n == Personnages[0]->get_y()+(y_size/2)){
					to_return[i][n]->libre = false;
					to_return[i][n]->CasePersonnage = Personnages[0];}}
			
			if(Personnages[1] != NULL){
				if(i == Personnages[1]->get_x()+(x_size/2) && n == Personnages[1]->get_y()+(y_size/2)){
					to_return[i][n]->libre = false;
					to_return[i][n]->CasePersonnage = Personnages[1];}}
	}}
	
	return to_return;
}

void Foret::DeleteMap(Case*** c)
{
	// on supprime toutes les cases
	for(int i=0; i< x_size; i++){
		for(int n=0; n< y_size; n++){
			delete[] c[i][n];}}
		
	// on supprime toutes les colonnees
	for(int i = 0; i < x_size; i++)
		delete[] c[i];
	
	// on supprime le tableau de colonnes
	delete[] c;
}
