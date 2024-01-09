#include "OrionLoop.h"
#include "CollisionMap.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Box.h"
#include "Timer.h"
#include "Utils.h"
#include "IOException.h"
#include "SecondOrderDynamics.h"

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
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

OrionLoop::OrionLoop(Options* options, EventHandler* eventHandler) {
	this->FPS = options->FPS;
	this->eventHandler = eventHandler;
}

void OrionLoop::initialize() {

}

void OrionLoop::execute() {
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

	gl::setViewport(0, 0, 800, 800);
	gl::setWindowResizeEvent(window);

	int TICKS_PER_FRAME = 1000 / FPS;
	bool hasController = false;
	Camera* c = new Camera();
	Box * b = new Box(0, 0, 135, 195, 2000, 2000, 222, 72, 31);
	CollisionMap* collisionMap = new CollisionMap(2000, 2000, 107);

	//Instantiate EntityManager
	this->entityManager = new EntityManager(collisionMap);

	//Add entities to entity manager
	entityManager->addEntity(c);
	entityManager->addEntity(b);

	double simulationTime = 0;
	double physTime = 0;
    Timer timer;

	bool quit = false;
	unsigned int shaderProgram = gl::getShaderProgram(vertexShaderSource, fragmentShaderSource);

	glEnable(GL_LINE_SMOOTH);
	glfwSwapInterval(1);

	std::cout << "DEBUG" << std::endl;

	while (!gl::shouldWindowClose(window)) {
		gl::pollEvents();
		gl::processInput(window);
		gl::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		gl::clearColorBuffer();

        timer.start();
        int realTime = timer.getTime();

		int tripsAroundTheSun = 0;

        while (simulationTime < realTime) {
			int eventBefore = timer.getTime();
			eventHandler->handleEvents(&quit, entityManager, window);

			int eventAfter = timer.getTime() - eventBefore;

			int handleBefore = timer.getTime();
			entityManager->handleStateChanges(6.06);

			int handleAfter = timer.getTime() - handleBefore;

			int enactBefore = timer.getTime();
			entityManager->enactStateChanges();
			
			int enactAfter = timer.getTime() - enactBefore;

            simulationTime += 6.06;
			tripsAroundTheSun++;

			// if (simulationTime < realTime) {
			// 	std::cout << "FRAME DROP " << eventAfter << ", " << handleAfter << ", " << enactAfter << ", " << simulationTime -16.67 << ", " << realTime << std::endl;
			// }
        }

		int showBefore = timer.getTime();
		entityManager->showAll(shaderProgram);
		int showAfter = timer.getTime() - showBefore;

		int swapBefore = timer.getTime();
		gl::swapBuffers(window);
		int swapAfter = timer.getTime() - swapBefore;

		//std::cout << "DEBUG: " << showAfter << ", " << swapAfter << std::endl;
		
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