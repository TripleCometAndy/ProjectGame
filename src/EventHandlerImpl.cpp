#include "../include/EventHandlerImpl.h"
#include "InputType.h"

#include <set>
#include <iostream>

EventHandlerImpl::EventHandlerImpl() {
}

void EventHandlerImpl::handleEvents(bool* shouldQuit, EntityManager* entityManager, GLFWwindow * window) {
    std::set<InputType> * events = new std::set<InputType>();

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        std::cout << "UP" << std::endl;
        events->insert(InputType::UP_ARROW);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        std::cout << "LEFT" << std::endl;
        events->insert(InputType::LEFT_ARROW);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        std::cout << "RIGHT" << std::endl;
        events->insert(InputType::RIGHT_ARROW);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        std::cout << "DOWN" << std::endl;
        events->insert(InputType::DOWN_ARROW);
    }

    if (!(*shouldQuit)) {
        entityManager->setInputs(events);
    }
 }