#include "Box.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Box::Box(double x, double y, unsigned int width, unsigned int height, unsigned int virtualWidth, unsigned int virtualHeight) {
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
    float renderX = ((2 * x) / virtualWidth) - 1;
    float renderY = ((2 * y) / virtualHeight) - 1;
    float renderWidth = ((2 * width) / virtualWidth);
    float renderHeight = ((2 * height) / virtualHeight);

    float vertices[] = {
        renderX + renderWidth, renderY, 0.0f,
        renderX + renderWidth, renderY + renderHeight, 0.0f,
        renderX, renderY + renderHeight, 0.0f,
        renderX, renderY, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Box::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {

}

void Box::enactStateChanges() {

}

void Box::show(int shaderProgram){
}