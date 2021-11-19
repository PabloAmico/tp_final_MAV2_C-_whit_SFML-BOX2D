#pragma once
#include "actor.h"
#include "ragdoll.h"
#include "Procesar_Colisiones.h"


class juego
{
public:
	juego(Vector2i resolucion, std::string titulo);
	void set_camera();
	void ini_fisica();
	void ini_grafic();
	void update_fisica();
	void process_events();
	void gameLoop();
	void draw();
	float deg2rad(float grados);
private:
	RenderWindow * ventana1;
	View * camara;
	Event * evento_1;
	Time * time_1;
	Clock * reloj_1;

	float fps, tiempoFrame, tiempo2;

	b2World *mundo;


	//suelo

	b2Body * body_floor;
	b2BodyDef bodydef_floor;
	b2Fixture * fix_floor;
	b2FixtureDef fixdef_floor;

	//Canion

	b2Body * bdy_canion;
	b2BodyDef bdydef_canion;
	b2Fixture * fix_canion;
	b2FixtureDef fixdef_canion;

	RectangleShape * fig_canion;
	
	RectangleShape * fig_floor;
	actor * Act_Floor;

	actor * Act_canion;

	ragdoll *rag_1;

	ragdoll *rag_prueba;

	//colisiones

	Procesar_Colisiones Colisiones;
};

