#include "Game.h"

Game::Game(Vector2i resolucion, string titulo) {

	//sonido disparo
	_sonidoDisparo.loadFromFile("../Sounds/disparoCa�on.wav");
	_disparo.setBuffer(_sonidoDisparo);
	  


	fps = 60;
	tiempoFrame = 1 / 60.f;
	tiempo2 = 0;

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	set_camera();
	iniciar_fisica();
	iniciar_img();

	evento1 = new Event;

	reloj1 = new Clock;
	tiempo1 = new Time;

	

	act_suelo = new Actor(bdy_suelo, fig_suelo);
	act_techo = new Actor(bdy_techo, fig_techo);
	act_paredI = new Actor(bdy_paredI, fig_paredI);
	act_paredD = new Actor(bdy_paredD, fig_paredD);

	act_obstaculoF = new Actor(bdy_obstaculoF, fig_obstaculoF);
	act_obstaculoF2 = new Actor(bdy_obstaculoF2, fig_obstaculoF2);
	act_obstaculoI = new Actor(bdy_obstaculoI, fig_obstaculoI);
	act_obstaculoI2 = new Actor(bdy_obstaculoI2, fig_obstaculoI2);
	act_obstaculoM = new Actor(bdy_obstaculoM, fig_obstaculoM);
	act_canion = new Actor(bdy_canion, fig_canion);


	gameLoop();
}

void Game::set_camera() {

	camara1 = new View({ 5.f,5.f }, { 30.f,30.f }); //el centro, el tama�o
	camara1->move(53.5f, 83.5f);

	ventana1->setView(*camara1);
}

void Game::iniciar_fisica() {

	mundo1 = new b2World(b2Vec2(0.f, 9.8f));

	//Se crea el contact listener y se lo asigna al mundo
	MCL = new MyContactListener;
	mundo1->SetContactListener(MCL);

	//suelo
	bdydef_suelo.type = b2_staticBody;
	bdydef_suelo.position = b2Vec2(50.f, 103.f);
	bdy_suelo = mundo1->CreateBody(&bdydef_suelo);

	b2PolygonShape shp_suelo;
	shp_suelo.SetAsBox(50.f, 0.5f);

	fixdef_suelo.shape = &shp_suelo;
	fixdef_suelo.restitution = 0.f;
	fixdef_suelo.friction = 0.3f;
	fixdef_suelo.density = 1.f;
	fixdef_suelo.userData.pointer = 3;

	fix_suelo = bdy_suelo->CreateFixture(&fixdef_suelo);

	//techo
	bdydef_techo.type = b2_staticBody;
	bdydef_techo.position = b2Vec2(50.f, 73.5f);
	bdy_techo = mundo1->CreateBody(&bdydef_techo);

	b2PolygonShape shp_techo;
	shp_techo.SetAsBox(50.f, 0.5f);

	fixdef_techo.shape = &shp_techo;
	fixdef_techo.restitution = 0.f;
	fixdef_techo.friction = 0.3f;
	fixdef_techo.density = 1.f;
	fixdef_techo.userData.pointer = 3;

	fix_techo = bdy_techo->CreateFixture(&fixdef_techo);

	//paredI
	bdydef_paredI.type = b2_staticBody;
	bdydef_paredI.position = b2Vec2(43.5f, 83.5f);
	bdy_paredI = mundo1->CreateBody(&bdydef_paredI);

	b2PolygonShape shp_paredI;
	shp_paredI.SetAsBox(0.5f, 50.f);

	fixdef_paredI.shape = &shp_paredI;
	fixdef_paredI.restitution = 0.f;
	fixdef_paredI.friction = 0.3f;
	fixdef_paredI.density = 1.f;
	fixdef_paredI.userData.pointer = 3;

	fix_paredI = bdy_paredI->CreateFixture(&fixdef_paredI);


	//paredD
	bdydef_paredD.type = b2_staticBody;
	bdydef_paredD.position = b2Vec2(73.5f, 83.5f);
	bdy_paredD = mundo1->CreateBody(&bdydef_paredD);

	b2PolygonShape shp_paredD;
	shp_paredD.SetAsBox(0.5f, 50.f);

	fixdef_paredD.shape = &shp_paredD;
	fixdef_paredD.restitution = 0.f;
	fixdef_paredD.friction = 0.3f;
	fixdef_paredD.density = 1.f;
	fixdef_paredD.userData.pointer = 3;

	fix_paredD = bdy_paredD->CreateFixture(&fixdef_paredD);

	//obst�culo Fijo

	bdydef_obstaculoF.type = b2_kinematicBody;
	bdydef_obstaculoF.position = b2Vec2(50.f, 85.f);
	bdy_obstaculoF = mundo1->CreateBody(&bdydef_obstaculoF);

	b2PolygonShape shp_obstaculoF;
	shp_obstaculoF.SetAsBox(1.5f, 1.f);

	fixdef_obstaculoF.shape = &shp_obstaculoF;
	fixdef_obstaculoF.restitution = 0.f;
	fixdef_obstaculoF.friction = 0.3f;
	fixdef_obstaculoF.density = 1.f;
	fixdef_obstaculoF.userData.pointer = 2;

	fix_obstaculoF = bdy_obstaculoF->CreateFixture(&fixdef_obstaculoF);

	//obst�culo Fijo 2

	bdydef_obstaculoF2.type = b2_kinematicBody;
	bdydef_obstaculoF2.position = b2Vec2(60.f, 85.f);
	bdy_obstaculoF2 = mundo1->CreateBody(&bdydef_obstaculoF2);

	b2PolygonShape shp_obstaculoF2;
	shp_obstaculoF2.SetAsBox(1.5f, 1.f);

	fixdef_obstaculoF2.shape = &shp_obstaculoF2;
	fixdef_obstaculoF2.restitution = 0.f;
	fixdef_obstaculoF2.friction = 0.3f;
	fixdef_obstaculoF2.density = 1.f;
	fixdef_obstaculoF2.userData.pointer = 2;

	fix_obstaculoF2 = bdy_obstaculoF2->CreateFixture(&fixdef_obstaculoF2);

	//obst�culo Inm�vil

	bdydef_obstaculoI.type = b2_staticBody;
	bdydef_obstaculoI.position = b2Vec2(60.f, 82.f);
	bdy_obstaculoI = mundo1->CreateBody(&bdydef_obstaculoI);

	b2PolygonShape shp_obstaculoI;
	shp_obstaculoI.SetAsBox(1.5f, 1.f);

	fixdef_obstaculoI.shape = &shp_obstaculoI;
	fixdef_obstaculoI.restitution = 0.f;
	fixdef_obstaculoI.friction = 0.3f;
	fixdef_obstaculoI.density = 1.f;
	fixdef_obstaculoI.userData.pointer = 3;

	fix_obstaculoI = bdy_obstaculoI->CreateFixture(&fixdef_obstaculoI);

	//obst�culo Inm�vil 2

	bdydef_obstaculoI2.type = b2_staticBody;
	bdydef_obstaculoI2.position = b2Vec2(60.f, 100.f);
	bdy_obstaculoI2 = mundo1->CreateBody(&bdydef_obstaculoI2);

	b2PolygonShape shp_obstaculoI2;
	shp_obstaculoI2.SetAsBox(1.5f, 1.f);

	fixdef_obstaculoI2.shape = &shp_obstaculoI2;
	fixdef_obstaculoI2.restitution = 0.f;
	fixdef_obstaculoI2.friction = 0.3f;
	fixdef_obstaculoI2.density = 1.f;
	fixdef_obstaculoI2.userData.pointer = 3;

	fix_obstaculoI2 = bdy_obstaculoI2->CreateFixture(&fixdef_obstaculoI2);

	//obst�culo M�vil	

	bdydef_obstaculoM.type = b2_kinematicBody;
	bdydef_obstaculoM.position = b2Vec2(55.f, 92.f);
	bdy_obstaculoM = mundo1->CreateBody(&bdydef_obstaculoM);

	b2PolygonShape shp_obstaculoM;
	shp_obstaculoM.SetAsBox(3.f, 0.4f);


	fixdef_obstaculoM.shape = &shp_obstaculoM;
	fixdef_obstaculoM.restitution = 0.f;
	fixdef_obstaculoM.friction = 1.f;
	fixdef_obstaculoM.density = 1.f;
	fixdef_obstaculoM.userData.pointer = 3;

	fix_obstaculoM = bdy_obstaculoM->CreateFixture(&fixdef_obstaculoM);


	//Ca��n   b2Vec2(47.5f, 98.5f);
	bdydef_canion.type = b2_staticBody;
	bdydef_canion.position = b2Vec2(45.5f, 100.5f);
	bdy_canion = mundo1->CreateBody(&bdydef_canion);

	b2PolygonShape shape_canion;
	shape_canion.SetAsBox(1.2f, 0.9f);


	fixdef_canion.shape = &shape_canion;
	fixdef_canion.density = 1.0f;
	fixdef_canion.restitution = 0.3f;
	fixdef_canion.friction = 0.3f;
	
	fix_canion = bdy_canion->CreateFixture(&fixdef_canion);

}

void Game::iniciar_img() {

	fig_suelo = new RectangleShape;
	fig_suelo->setFillColor(Color::Green);

	fig_techo = new RectangleShape;
	fig_techo->setFillColor(Color::Green);

	fig_paredI = new RectangleShape;
	fig_paredI->setFillColor(Color::Green);

	fig_paredD = new RectangleShape;
	fig_paredD->setFillColor(Color::Green);


	fig_canion = new RectangleShape;
	fig_canion->setFillColor(Color::Red);

	fig_obstaculoF = new RectangleShape;
	fig_obstaculoF->setFillColor(Color::Yellow);

	fig_obstaculoF2 = new RectangleShape;
	fig_obstaculoF2->setFillColor(Color::Yellow);

	fig_obstaculoI = new RectangleShape;
	fig_obstaculoI->setFillColor(Color::Blue);

	fig_obstaculoI2 = new RectangleShape;
	fig_obstaculoI2->setFillColor(Color::Blue);

	fig_obstaculoM = new RectangleShape;
	fig_obstaculoM->setFillColor(Color::Yellow);
	
}

void Game::actualizar_fisica() {

	mundo1->Step(tiempoFrame, 8, 8);
	mundo1->ClearForces();

	

	Vector2i posicion_m = Mouse::getPosition(*ventana1);
	Vector2f coordenadas_m = ventana1->mapPixelToCoords(posicion_m);

	// Calculamos el �ngulo hacia el mouse
	float angulo_objetivo = atan2f(coordenadas_m.y - bdy_canion->GetPosition().y, coordenadas_m.x - bdy_canion->GetPosition().x);

	// Limitamos el �ngulo (en radianes)
	float limite_min = deg2rad(-90); // -90�
	float limite_max = deg2rad(0);   // 0� (asumiendo que el ca��n apunta a la derecha y sube cuando gira negativo)

	if (angulo_objetivo < limite_min) angulo_objetivo = limite_min;
	if (angulo_objetivo > limite_max) angulo_objetivo = limite_max;

	bdy_canion->SetTransform(bdy_canion->GetPosition(), angulo_objetivo);

	
	if (MCL->cuerpo_tocado) {
		if (MCL->cuerpo_tocado->GetType() == b2_kinematicBody) {
			MCL->cuerpo_tocado->SetType(b2_dynamicBody);

		}
		MCL->cuerpo_tocado = nullptr; // Limpiar para no hacer varias veces
		
	}
}

void Game::procesar_eventos() {

	while (ventana1->pollEvent(*evento1)) {
		switch (evento1->type) {
		case Event::Closed:

			for (auto& rag : ragdolls) {
				delete rag;
			}
			ragdolls.clear();


			exit(1);
			break;
		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				bdy_canion->SetTransform(bdy_canion->GetPosition(), bdy_canion->GetAngle() - deg2rad(3));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				bdy_canion->SetTransform(bdy_canion->GetPosition(), bdy_canion->GetAngle() + deg2rad(3));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space)) {
				
			}
			break;

		case Event::MouseButtonPressed:

			Vector2i posicion_m;
			Vector2f coordenadas_m;
			float angle = bdy_canion->GetAngle(); // �ngulo de rotaci�n en radianes

			ReproducirDisparo();

			// Calcular vector de direcci�n hacia donde apunta el ca��n
			b2Vec2 direction(cos(angle), sin(angle));

			// Posici�n de disparo (punta del ca��n)
			b2Vec2 spawnPos = { bdy_canion->GetPosition().x + cos(angle), bdy_canion->GetPosition().y + sin(angle) };
			//b2Vec2 spawnPos = bdy_canion->GetPosition() + b2Mul(0.3f, direction);

			posicion_m = Mouse::getPosition(*ventana1);
			coordenadas_m = ventana1->mapPixelToCoords(posicion_m);  //tambi�n ventana1->mapPixelToCoords( Mouse::getPosition(*ventana1));
			
			// Crear y guardar nueva ragdoll

			if (ragdolls.size() >= 10) {
				delete ragdolls.front();         // Eliminar el primero
				ragdolls.erase(ragdolls.begin()); // Sacarlo del vector
			}

			Ragdoll* nueva_rag = new Ragdoll({ spawnPos.x, spawnPos.y }, mundo1);

			// Aplicar fuerza en direcci�n al mouse
			nueva_rag->aplicar_fuerza({ coordenadas_m.x - bdy_canion->GetPosition().x, coordenadas_m.y - bdy_canion->GetPosition().y });

			// Agregarla al vector
			ragdolls.push_back(nueva_rag);




			break;
		}
		

	}

	
	if (bdy_obstaculoM->GetPosition().x >= 65.f) {
		desplazamiento = -0.03f;
		rotacion = -0.015f;
	}
	if (bdy_obstaculoM->GetPosition().x <= 50.f) {
		desplazamiento = 0.03f;
		rotacion = 0.015f;
	}
	bdy_obstaculoM->SetTransform(b2Vec2(bdy_obstaculoM->GetPosition().x + desplazamiento, bdy_obstaculoM->GetPosition().y), bdy_obstaculoM->GetAngle() + rotacion);
	
}


void Game::gameLoop() {

	while (ventana1->isOpen()) {

		*tiempo1 = reloj1->getElapsedTime();
		if (tiempo2 + tiempoFrame < tiempo1->asSeconds()) {
			tiempo2 = tiempo1->asSeconds();

			ventana1->clear();
			procesar_eventos();
			actualizar_fisica();
			dibujar();
			ventana1->display();

		}
	}
}

void Game::dibujar() {

	act_suelo->dibujar(*ventana1);
	act_techo->dibujar(*ventana1);
	act_paredI->dibujar(*ventana1);
	act_paredD->dibujar(*ventana1);

	act_obstaculoF->dibujar(*ventana1);
	act_obstaculoF2->dibujar(*ventana1);
	act_obstaculoI->dibujar(*ventana1);
	act_obstaculoI2->dibujar(*ventana1);
	act_obstaculoM->dibujar(*ventana1);
	

	for (auto& rag : ragdolls) {
		rag->Dibujar(*ventana1);
	}
	act_canion->dibujar(*ventana1);
}

float Game::deg2rad(float grados) {
	return grados * 3.14 / 180;
}

void Game::ReproducirDisparo() {
	_disparo.setVolume(80);
	_disparo.play();
}

