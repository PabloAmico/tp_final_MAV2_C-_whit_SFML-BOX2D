#include "juego.h"

juego::juego(Vector2i resolucion, std::string titulo)
{
	fps = 60;
	tiempoFrame = 1 / 60.f;
	tiempo2 = 0;

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);
	
	set_camera();
	ini_fisica();
	ini_grafic();

	evento_1 = new Event;

	reloj_1 = new Clock;
	time_1 = new Time;

	rag_1 = new ragdoll({ 50,90 }, *mundo);
	

	
	Act_Floor = new actor(body_floor, fig_floor);
	Act_canion = new actor(bdy_canion, fig_canion);



	//colisiones

	mundo->SetContactListener(&Colisiones);

}

void juego::set_camera()
{
	camara = new View({ 5.f,5.f }, { 10.f,10.f });
	camara->move(45.f, 90.f);

	ventana1->setView(*camara);
}

void juego::ini_fisica()
{
	mundo = new b2World(b2Vec2(0.f, 9.81f));

	//suelo

	bodydef_floor.type = b2_staticBody;
	bodydef_floor.position = b2Vec2(50.f, 100.f);

	body_floor = mundo->CreateBody(&bodydef_floor);

	b2PolygonShape shp_suelo;
	shp_suelo.SetAsBox(50.f, 2.5f);

	fixdef_floor.shape = &shp_suelo;
	fixdef_floor.restitution = 0.f;
	fixdef_floor.friction = 0.25;
	fixdef_floor.density = 1.f;

	fix_floor = body_floor->CreateFixture(&fixdef_floor);

	//canion

	bdydef_canion.type = b2_staticBody;
	bdydef_canion.position = b2Vec2(46.f, 97.f);

	bdy_canion = mundo->CreateBody(&bdydef_canion);

	b2PolygonShape shp_canion;
	shp_canion.SetAsBox(0.9f, 0.32f);

	fixdef_canion.shape = &shp_canion;
	fixdef_canion.density = 1.f;
	fixdef_canion.restitution = 0.1f;
	fixdef_canion.friction = 0.3f;

	fix_canion = bdy_canion->CreateFixture(&fixdef_canion);
	

}

void juego::ini_grafic()
{
	fig_floor = new RectangleShape;
	fig_floor->setFillColor(Color::Red);
	fig_canion = new RectangleShape;
	fig_canion->setFillColor(Color::White);
}

void juego::update_fisica()
{
	mundo->Step(tiempoFrame, 8, 8);
	mundo->ClearForces();
}

void juego::process_events()
{
	while (ventana1->pollEvent(*evento_1))
	{
		switch (evento_1->type)
		{
		case Event::Closed:
			exit(1);
			break;

		case Event::KeyPressed:

			if (Keyboard::isKeyPressed(Keyboard::Down)) 
			{
				bdy_canion->SetTransform(bdy_canion->GetPosition(), bdy_canion->GetAngle() + deg2rad(3));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up)) 
			{
					bdy_canion->SetTransform(bdy_canion->GetPosition(), bdy_canion->GetAngle() + deg2rad(-3));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space)) 
			{
				rag_prueba = new ragdoll({ bdy_canion->GetPosition().x + 1.f,bdy_canion->GetPosition().y }, *mundo);
				//rag_prueba->set_id(jugador);
				rag_prueba->applyForce(2, bdy_canion->GetAngle());
			}
			break;
		}
	}
}

void juego::gameLoop()
{
	while (ventana1->isOpen())
	{
		*time_1 = reloj_1->getElapsedTime();
		if (tiempo2 + tiempoFrame < time_1->asSeconds()) {
			tiempo2 = time_1->asSeconds();
			ventana1->clear();
			process_events();
			update_fisica();
			draw();
			ventana1->display();
		}
	}
}

void juego::draw()
{
	Act_Floor->draw(*ventana1);
	Act_canion->draw(*ventana1);

	rag_1->Dibujar(*ventana1);

	if (rag_prueba) {
		rag_prueba->Dibujar(*ventana1);
	}
	
}

float juego::deg2rad(float grados) {

	return grados * 3.14 / 180;
}
