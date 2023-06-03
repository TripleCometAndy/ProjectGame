#pragma once

#include "EntityManager.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class EventHandler {
public:
	EventHandler();

	virtual void handleEvents(bool* shouldQuit, EntityManager * entityManager, GLFWwindow * window) = 0;
};