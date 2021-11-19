#pragma once
#include "Colisionables.h"

#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"


using namespace sf;

class actor : public Colisionables
{
public:
	actor(b2Body * cuerpo, RectangleShape * figura);
	void draw(RenderWindow &w);
	float rad2deg(float radianes);
	Colisionables col();
private:
	b2Body * bdy_actor;
	RectangleShape * fig_actor;

	b2AABB dimensiones;
	b2Vec2 posicion;
};

