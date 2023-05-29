#include "OrionLoop.h"
#include "Background.h"
#include "Orb.h"
#include "CollisionMap.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Wall.h"
#include "Timer.h"

#include <iostream>

OrionLoop::OrionLoop(Options* options, EventHandler* eventHandler) {
	this->FPS = options->FPS;
	this->eventHandler = eventHandler;
}

void OrionLoop::initialize() {

}

void OrionLoop::execute() {
    std::cout << "ENTERED LOOP" << std::endl;

	int TICKS_PER_FRAME = 1000 / FPS;

	bool hasController = false;

	std::vector<std::string> backgroundPaths;
	backgroundPaths.push_back("C:/Users/might/Downloads/background.jpg");

	OrionEntity* b = new Background(&backgroundPaths);
	
	std::vector<std::string> orbPaths;
	orbPaths.push_back("C:/Users/might/Downloads/orb.png");

	OrionEntity* o = new Orb(700, 700, &orbPaths);

	std::vector<std::string> wallPaths;
	wallPaths.push_back("C:/Users/might/Downloads/wall.png");

	OrionEntity* w = new Wall(400, 400, 40, 900, &wallPaths);
	OrionEntity* w2 = new Wall(400, 400, 800, 40, &wallPaths);
	OrionEntity* w3 = new Wall(1075, 400, 40, 900, &wallPaths);
	OrionEntity* w4 = new Wall(400, 1075, 800, 40, &wallPaths);

	Camera* c = new Camera();

	CollisionMap* collisionMap = new CollisionMap(2000, 2000, 107);

	//Instantiate EntityManager
	this->entityManager = new EntityManager(collisionMap);

	//Add entities to entity manager
	entityManager->addEntity(b);
	entityManager->addEntity(o);
	entityManager->addEntity(w);
	entityManager->addEntity(w2);
	entityManager->addEntity(w3);
	entityManager->addEntity(w4);
	entityManager->addEntity(c);

	bool quit = false;
	int simulationTime = 0;
    Timer timer;

	while (!quit) {
        timer.start();
        int realTime = timer.getTime();

        while (simulationTime < realTime) {
            simulationTime += 16;
        }

        int frameTicks = timer.getTicks();

        std::cout << "IN LOOP" << std::endl;
	}

	int orbX = getEntityX("ORB");
	int orbY = getEntityY("ORB");

	std::cout << "ORBB: " << orbX << ", " << orbY << std::endl;
}

int OrionLoop::getEntityX(std::string entityName) {
	return entityManager->getEntityX(entityName);
}

int OrionLoop::getEntityY(std::string entityName) {
	return entityManager->getEntityY(entityName);
}