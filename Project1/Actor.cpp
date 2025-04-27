#include "Actor.h"

Actor::Actor(b2Body* cuerpo, RectangleShape* figura) : bdy_actor(cuerpo), fig_actor(figura) 
{
	posicion = bdy_actor->GetPosition();

	

	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	for (b2Fixture* i = bdy_actor->GetFixtureList(); i; i = i->GetNext()) {
		dimensiones = i->GetAABB(0);
	}

	
	fig_actor->setSize({ dimensiones.GetExtents().x * 2,dimensiones.GetExtents().y * 2 });
	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->getSize().y / 2.f);
	fig_actor->setPosition(posicion.x, posicion.y);
}

void Actor::dibujar(RenderWindow& ventana) {
	posicion = bdy_actor->GetPosition();

	fig_actor->setPosition(posicion.x, posicion.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));

	ventana.draw(*fig_actor);
}

float Actor::rad2deg(float radianes) {

	//3.14____________180
	//radian__________x


	return radianes * 180 / 3.14;
}