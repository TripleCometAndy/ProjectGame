#include "Box.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Box::Box(double x, double y, unsigned int width, unsigned int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    //Initialize VAO
    glGenVertexArrays(1, &VAO);

    //Initialize VBO
    glGenBuffers(1, &VBO);

    //Initialize EBO
    glGenBuffers(1, &EBO);

    //Get the vertices for our rect
}

void Box::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {

}

void Box::enactStateChanges() {

}

void Box::show(int shaderProgram){
}