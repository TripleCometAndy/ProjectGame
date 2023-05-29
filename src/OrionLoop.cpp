#include "OrionLoop.h"
#include "Background.h"
#include "Orb.h"
#include "CollisionMap.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Wall.h"
#include "Timer.h"
#include "Utils.h"
#include "IOException.h"

#include <iostream>

//We need to include glad before glfw
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(aPos, 1.0f);\n"
    "    TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

OrionLoop::OrionLoop(Options* options, EventHandler* eventHandler) {
	this->FPS = options->FPS;
	this->eventHandler = eventHandler;
}

void OrionLoop::initialize() {

}

void OrionLoop::execute() {
    std::cout << "ENTERED LOOP" << std::endl;

	gl::initializeGLFW();
	gl::setOpenGLVersion(3, 3);
	gl::setGLFWUseCoreProfile();

	GLFWwindow * window = gl::createWindow(800, 600, "OrionEngine 3.0 Tech Demo");

	if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        gl::terminate();
        return;
    }

	gl::updateCurrentContext(window);

	try {
        gl::initializeGLAD();
    }
    catch (IOException &ex) {
        gl::terminate();
        return;
    }

	gl::setViewport(0, 0, 800, 600);

	gl::setWindowResizeEvent(window);


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

	int simulationTime = 0;
    Timer timer;

	while (!gl::shouldWindowClose(window)) {
        timer.start();
        int realTime = timer.getTime();

        while (simulationTime < realTime) {
			gl::processInput(window);
            simulationTime += 16;
        }

        int frameTicks = timer.getTicks();

        std::cout << "IN LOOP" << std::endl;

		gl::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        gl::clearColorBuffer();

		gl::pollEvents();
		gl::swapBuffers(window);
	}

	gl::terminate();

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