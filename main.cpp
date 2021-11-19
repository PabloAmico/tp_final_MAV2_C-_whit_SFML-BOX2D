#include "juego.h"


int main(int argc, char * args[])
{
	juego partida1({ 800,600 }, "Ragdoll  simple con resorte");
	partida1.gameLoop();

	return 0;
}