#pragma once

#include "OrionEntity.h"

class Box : public OrionEntity {
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;



public:
    Box(double x, double y, unsigned int width, unsigned int height);

	void handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap);
	void enactStateChanges();
	void show(int shaderProgram);
};