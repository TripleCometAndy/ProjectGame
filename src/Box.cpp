#include "Box.h"

#include "Utils.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Box::Box(double x, double y, unsigned int width, unsigned int height, unsigned int virtualWidth, unsigned int virtualHeight) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    Hitbox * hitbox = new Hitbox();
	hitbox->x = x;
	hitbox->y = y;
	hitbox->width = width;
	hitbox->height = height;
	hitbox->parent = this;

	hitboxes.insert(hitbox);

    //Initialize VAO
    glGenVertexArrays(1, &VAO);

    //Initialize VBO
    glGenBuffers(1, &VBO);

    //Initialize EBO
    glGenBuffers(1, &EBO);

    //Get the vertices for our rect
    float renderX = ((2 * x) / virtualWidth) - 1;
    float renderY = (((2 * y) / virtualHeight) - 1) * -1;
    float renderWidth = ((double)(2 * width) / (double)virtualWidth);
    float renderHeight = ((double)(2 * height) / (double)virtualHeight);

    std::cout << "RENDER WIDTH: " << renderWidth << std::endl;
    std::cout << "RENDER HEIGHT: " << renderHeight << std::endl;

    float topRightX = renderX + renderWidth;
    float topRightY = renderY;

    float bottomRightX =  renderX + renderWidth;
    float bottomRightY = renderY - renderHeight;

    float bottomLeftX = renderX;
    float bottomLeftY = renderY - renderHeight;

    float topLeftX = renderX;
    float topLeftY = renderY;

    std::cout << "TOP LEFT: " << topLeftX << ", " << topLeftY << std::endl;
    std::cout << "TOP RIGHT: " << topRightX << ", " << topRightY << std::endl;
    std::cout << "BOTTOM LEFT: " << bottomLeftX << ", " << bottomLeftY << std::endl;
    std::cout << "BOTTOM RIGHT: " << bottomRightX << ", " << bottomRightY << std::endl;

    float vertices[] = {
        topRightX, topRightY, 0.0f,
        bottomRightX, bottomRightY, 0.0f,
        bottomLeftX, bottomLeftY, 0.0f,
        topLeftX, topLeftY, 0.0f
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

        // note that this is allowed, the call to glVertexAttribPointer registered
    // VBO as the vertex attribute's bound vertex buffer object so afterwards we
    // can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally
    // modify this VAO, but this rarely happens. Modifying other VAOs requires a
    // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
    // VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}

void Box::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {

}

void Box::enactStateChanges() {

}

void Box::show(int shaderProgram) {
    std::cout << "RENDER BOX" << std::endl;

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}