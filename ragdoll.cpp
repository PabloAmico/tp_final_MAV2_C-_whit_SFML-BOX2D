#include "ragdoll.h"

ragdoll::ragdoll(Vector2f posicion, b2World & mundo) {
	

	//Ragdoll

	for (size_t i = 0; i < 6; i++)
	{
		bdydef_ragdoll[i].type = b2_dynamicBody;
	}

	//posicionamiento del ragdoll
	bdydef_ragdoll[0].position = b2Vec2(posicion.x, posicion.y + 0.1f); //Cabeza
	bdydef_ragdoll[1].position = b2Vec2(posicion.x, posicion.y +0.65f); //Torso
	bdydef_ragdoll[2].position = b2Vec2(posicion.x + 0.32f, posicion.y + 0.5f);	//brazo derecho
	bdydef_ragdoll[3].position = b2Vec2(posicion.x - 0.32f, posicion.y + 0.5f);	//Brazo izquiero
	bdydef_ragdoll[4].position = b2Vec2(posicion.x + 0.9f, posicion.y + 1.5f);	//pierna derecha
	bdydef_ragdoll[5].position = b2Vec2(posicion.x - 0.9f, posicion.y + 1.5f);	//pierna izquierda

	for (size_t i = 0; i < 6; i++)
	{
		bdy_ragdoll[i] = mundo.CreateBody(&bdydef_ragdoll[i]);
	}

	//dimensiones del cuerpo
	b2PolygonShape shp_rag[6];

	shp_rag[0].SetAsBox(0.1, 0.1);
	shp_rag[1].SetAsBox(0.2, 0.4);
	shp_rag[2].SetAsBox(0.07, 0.3);
	shp_rag[3].SetAsBox(0.07, 0.3);
	shp_rag[4].SetAsBox(0.07, 0.4);
	shp_rag[5].SetAsBox(0.07, 0.4);

	for (size_t i = 0; i < 6; i++)
	{
		fixdef_ragdoll[i].shape = &shp_rag[i];
		fixdef_ragdoll[i].density = 1.f;
		fixdef_ragdoll[i].friction = 0.3f;
		fixdef_ragdoll[i].restitution = 0.3f;
		fix_ragdoll[i] = bdy_ragdoll[i]->CreateFixture(&fixdef_ragdoll[i]);
	}

	//Resortes

	jntdef_ragdoll[0].Initialize(bdy_ragdoll[0], bdy_ragdoll[1], b2Vec2(bdy_ragdoll[0]->GetPosition().x, bdy_ragdoll[0]->GetPosition().y + 0.08), b2Vec2(bdy_ragdoll[1]->GetPosition().x, bdy_ragdoll[1]->GetPosition().y - 0.38));
	jntdef_ragdoll[1].Initialize(bdy_ragdoll[1], bdy_ragdoll[2], b2Vec2(bdy_ragdoll[1]->GetPosition().x + 0.17, bdy_ragdoll[1]->GetPosition().y - 0.37), b2Vec2(bdy_ragdoll[2]->GetPosition().x - 0.04, bdy_ragdoll[2]->GetPosition().y - 0.27));
	jntdef_ragdoll[2].Initialize(bdy_ragdoll[1], bdy_ragdoll[3], b2Vec2(bdy_ragdoll[1]->GetPosition().x - 0.15, bdy_ragdoll[3]->GetPosition().y - 0.37), b2Vec2(bdy_ragdoll[3]->GetPosition().x + 0.05, bdy_ragdoll[3]->GetPosition().y - 0.27));
	jntdef_ragdoll[3].Initialize(bdy_ragdoll[1], bdy_ragdoll[4], b2Vec2(bdy_ragdoll[1]->GetPosition().x - 0.09, bdy_ragdoll[1]->GetPosition().y + 0.38), b2Vec2(bdy_ragdoll[4]->GetPosition().x, bdy_ragdoll[4]->GetPosition().y - 0.38));
	jntdef_ragdoll[4].Initialize(bdy_ragdoll[1], bdy_ragdoll[5], b2Vec2(bdy_ragdoll[1]->GetPosition().x - 0.09, bdy_ragdoll[1]->GetPosition().y + 0.38), b2Vec2(bdy_ragdoll[5]->GetPosition().x, bdy_ragdoll[5]->GetPosition().y - 0.38));

	for (size_t i = 0; i < 5; i++)
	{
		jntdef_ragdoll[i].dampingRatio = 0.35f;
		jntdef_ragdoll[i].frequencyHz = 2.5f;
		jntdef_ragdoll[i].collideConnected = true;
		jntdef_ragdoll[i].length = 0.030f;
		jnt_Ragdoll[i] = (b2DistanceJoint*)mundo.CreateJoint(&jntdef_ragdoll[i]);
	}


	for (size_t i = 0; i < 6; i++)
	{
		fig_RecShape[i] = new RectangleShape;

	}

	fig_RecShape[0]->setFillColor(Color::Red);
	fig_RecShape[1]->setFillColor(Color::Green);
	fig_RecShape[2]->setFillColor(Color::Magenta);
	fig_RecShape[3]->setFillColor(Color::Magenta);
	fig_RecShape[4]->setFillColor(Color::Yellow);
	fig_RecShape[5]->setFillColor(Color::Yellow);

	for (size_t i = 0; i < 6; i++)
	{
		Act_Ragdoll[i] = new actor(bdy_ragdoll[i], fig_RecShape[i]);
	}

	bdy_ragdoll[1]->SetUserData((void*)this);
	fix_ragdoll[1]->SetUserData((void*)this);
}

void ragdoll::Dibujar(RenderWindow & ventana) {
	for (size_t i = 0; i < 6; i++)
	{
		Act_Ragdoll[i]->draw(ventana);
	}
}


void ragdoll::applyForce(float force, float rad_angle) {

	
	for (int i = 0; i < 6; i++) {
		bdy_ragdoll[i]->ApplyForceToCenter(b2Vec2(bdy_ragdoll[i]->GetPosition().x * force * cos(rad_angle), bdy_ragdoll[i]->GetPosition().y * force * sin(rad_angle)), false);
	}
}


