#include "Procesar_Colisiones.h"

void Procesar_Colisiones::BeginContact(b2Contact * contact) {
	contact->GetFixtureA()->GetBody()->GetUserData();
}