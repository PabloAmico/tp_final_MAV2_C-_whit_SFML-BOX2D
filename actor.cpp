#include "actor.h"

actor::actor(b2Body * cuerpo, RectangleShape * figura)
{

	bdy_actor = cuerpo; 
	fig_actor = figura;
	posicion = bdy_actor->GetPosition();
	

	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	bdy_actor->SetUserData((void*)this);
	
	

	for (b2Fixture * i = bdy_actor->GetFixtureList(); i; i = i->GetNext())
	{
		dimensiones = i->GetAABB(0);
	}
	

	fig_actor->setSize({ dimensiones.GetExtents().x * 2, dimensiones.GetExtents().y * 2 });
	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->getSize().y / 2.f);

	fig_actor->setPosition(posicion.x, posicion.y);
}

void actor::draw(RenderWindow & w)
{
	posicion = bdy_actor->GetPosition();

	fig_actor->setPosition(posicion.x, posicion.y);

	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));

	w.draw(*fig_actor);
}

float actor::rad2deg(float radianes)
{

	return radianes * 180 / 3.14;
}
