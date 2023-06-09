#pragma once

#include "OrionEntity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Box : public OrionEntity {
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    float r;
    float g;
    float b;

    unsigned int virtualWidth;
    unsigned int virtualHeight;

    glm::mat4 transform;


public:
    Box(double x, double y, unsigned int width, unsigned int height, unsigned int virtualWidth, unsigned int virtualHeight, int r, int g, int b);

	void handleStateChanges(std::set<InputType>* currentInputs, std::set<JoystickInput *> * joystickInputs, CollisionMap * collisionMap);
	void enactStateChanges();
	void show(int shaderProgram);
};