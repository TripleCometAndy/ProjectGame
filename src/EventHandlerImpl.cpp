#include "../include/EventHandlerImpl.h"
#include "InputType.h"
#include "JoystickInput.h"

#include <set>
#include <iostream>
#include <cmath>

EventHandlerImpl::EventHandlerImpl() {
}

void EventHandlerImpl::handleEvents(bool* shouldQuit, EntityManager* entityManager, GLFWwindow * window) {
    std::set<InputType> * events = new std::set<InputType>();
    std::set<JoystickInput *> * joystickInputs = new std::set<JoystickInput *>();

    if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        //std::cout << "JOYSTICK PRESENT!" << std::endl;

        int count;
        const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

        
        for (int i = 0; i < count; i++) {
            float axis = axes[i];
            std::cout << "AXIS " << i << " " << axis << std::endl;
        }


        JoystickInput * joystickInput = new JoystickInput();
        joystickInput->x = axes[0];
        joystickInput->y = axes[1];

        double xSquared = axes[0] * axes[0];
        double ySquared = axes[1] * axes[1];
        double length = std::sqrt(xSquared + ySquared);

        joystickInput->length = length;
        joystickInput->controllerNumber = 1;
        joystickInput->isLeftStick = true;

        joystickInputs->insert(joystickInput);

    }
    else {
        //std::cout << "JOYSTICK NOT PRESENT!" << std::endl;
    }

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
        entityManager->setInputs(events, joystickInputs);
    }
 }