#pragma once
#include "Colisionables.h"
#include "actor.h"

class ragdoll 
{
public:
	ragdoll(Vector2f posicion, b2World & mundo);
	void Dibujar(RenderWindow &ventana);
	void applyForce(float force, float rad_angle);
	
	Colisionables col();
private:
	RectangleShape * fig_RecShape[6];
	actor * Act_Ragdoll[6];

	//resortes

	b2DistanceJoint * jnt_Ragdoll[5];
	b2DistanceJointDef jntdef_ragdoll[5];

	//ragdoll

	b2Body * bdy_ragdoll[6];
	b2BodyDef bdydef_ragdoll[6];
	b2Fixture * fix_ragdoll[6];
	b2FixtureDef fixdef_ragdoll[6];
};

