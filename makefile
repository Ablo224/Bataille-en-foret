WorldGenerator: WorldGenerator.o Foret.o Surface.o Relief.o Obstacle.o main.o Personnage.o PlayGame.o
	g++ -o WorldGenerator Foret.o WorldGenerator.o Surface.o Relief.o Obstacle.o Personnage.o -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall
	g++ -o PlayGame Foret.o PlayGame.o Surface.o Relief.o Obstacle.o Personnage.o -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall

main: Foret.o main.o Surface.o Relief.o Obstacle.o Personnage.o
	g++ -o main Foret.o main.o Surface.o Relief.o Obstacle.o Personnage.o -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall
	
PlayGame: PlayGame.o Foret.o Surface.o Relief.o Obstacle.o main.o Personnage.o
	g++ -o PlayGame Foret.o PlayGame.o Surface.o Relief.o Obstacle.o Personnage.o -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall

PlayGame.o: PlayGame.cc Foret.h
	g++ -o PlayGame.o -c PlayGame.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall

WorldGenerator.o: WorldGenerator.cc Foret.h
	g++ -o WorldGenerator.o -c WorldGenerator.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall

main.o: main.cc Foret.h
	g++ -o main.o -c main.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall

Foret.o: Foret.cc Foret.h
	g++ -o Foret.o -c Foret.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall
	
Surface.o: Surface.cc Surface.h
		g++ -o Surface.o -c Surface.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall
		
Relief.o: Relief.cc Relief.h
		g++ -o Relief.o -c Relief.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall

Obstacle.o: Obstacle.cc Obstacle.h
		g++ -o Obstacle.o -c Obstacle.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall

Personnage.o: Personnage.cc Personnage.h
		g++ -o Personnage.o -c Personnage.cc -lSDLmain -lSDL -lSDL_image -lSDL_ttf -Wall
