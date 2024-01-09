#include "Box.h"
#include "Utils.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Box::Box(double x, double y, unsigned int width, unsigned int height, unsigned int virtualWidth, unsigned int virtualHeight, int r, int g, int b) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    futureX = x;
    futureY = y;

    realX = x;
    realY = y;
    settleX = x;
    settleY = y;

    futureRealX = x;
    futureRealY = y;
    futureSettleX = x;
    futureSettleY = y;

    this->r = (1.0f/255)*r;
    this->g = (1.0f/255)*g;
    this->b = (1.0f/255)*b;

    this->virtualWidth = virtualWidth;
    this->virtualHeight = virtualHeight;

    xDynamic = new SecondOrderDynamics(-0.3125, -0.3125, 1.875, x);
    yDynamic = new SecondOrderDynamics(-0.3125, -0.3125, 1.875, y);

    transform = gl::createTransformationMatrix();

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

    float topRightX = 0 + renderWidth;
    float topRightY = 0;

    float bottomRightX =  0 + renderWidth;
    float bottomRightY = 0 - renderHeight;

    float bottomLeftX = 0;
    float bottomLeftY = 0 - renderHeight;

    float topLeftX = 0;
    float topLeftY = 0;

    transform = gl::translate(transform, renderX, renderY, 0.0f);

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

void Box::handleStateChanges(std::set<InputType>* currentInputs, std::set<JoystickInput *> * joystickInputs, CollisionMap * collisionMap, int dt) {
    handleJoystickInput(joystickInputs, dt);

    handleArrowKeyInput(currentInputs, dt);

    futureX = xDynamic->update((double)dt/(double)1000, futureSettleX);
    futureY = yDynamic->update((double)dt/(double)1000, futureSettleY);
}

void Box::handleJoystickInput(std::set<JoystickInput *> * joystickInputs, int dt) {
    if (joystickInputs == NULL) {
        return;
    }

    double xJoy;
    double yJoy;
    double lengthJoy;

    //Find joystick 1 and then break
    for (JoystickInput * joystickInput : *joystickInputs) {
        if (joystickInput->controllerNumber == 1) {
            xJoy = joystickInput->x;
            yJoy = joystickInput->y;
            lengthJoy = joystickInput->length;

            if (lengthJoy >= 0.5) {
                double normalizedX = xJoy/lengthJoy;
                double normalizedY = yJoy/lengthJoy;

                double finalX = normalizedX * VELOCITY * dt;
                double finalY = normalizedY * VELOCITY * dt;

                futureSettleX += finalX;
                futureSettleY -= finalY;

                xDynamic->setFZR(1, 1, -200);
                yDynamic->setFZR(1, 1, -200);
            }

            break;
        }
    }
}

void Box::handleArrowKeyInput(std::set<InputType>* currentInputs, int dt) {
    if (currentInputs == NULL) {
        return;
    }

    if (currentInputs->find(InputType::UP_ARROW) != currentInputs->end()) {
		futureSettleY += (VELOCITY * dt);

        setDynamicForMovementWhileInput();
	}
	else if (currentInputs->find(InputType::LEFT_ARROW) != currentInputs->end()) {
		futureSettleX -= (VELOCITY * dt);

        setDynamicForMovementWhileInput();
	}
	else if (currentInputs->find(InputType::RIGHT_ARROW) != currentInputs->end()) {
		futureSettleX += (VELOCITY * dt);

        setDynamicForMovementWhileInput();
	}
	else if (currentInputs->find(InputType::DOWN_ARROW) != currentInputs->end()) {
		futureSettleY -= (VELOCITY * dt);

        setDynamicForMovementWhileInput();
	}
    else {
        xDynamic->setFZR(-0.3125, -0.3125, 1.875);
        yDynamic->setFZR(-0.3125, -0.3125, 1.875);
    }
}

void Box::setDynamicForMovementWhileInput() {
    xDynamic->setFZR(1, 1, 0);
    yDynamic->setFZR(1, 1, 0);
}

void Box::enactStateChanges() {
    double differenceX = futureX - x;
	double differenceY = futureY - y;

    float differenceRenderX = (differenceX * 2) / (double)virtualWidth;
    float differenceRenderY = (differenceY * 2) / (double)virtualHeight;

    transform = gl::translate(transform, differenceRenderX, differenceRenderY, 0.0f);

	x = futureX;
	y = futureY;

    settleX = futureSettleX;
    settleY = futureSettleY;

	for (Hitbox* hitbox : hitboxes) {
		hitbox->x += differenceX;
		hitbox->y += differenceY;
	}
}

void Box::show(int shaderProgram) {
    //Cache the uniform locations. Significant speed loss if we continuously grab them
    if (!doHaveUniformLocations) {
        transformLoc = getUniformLocation(shaderProgram, "transform");
        vertexColorLoc = getUniformLocation(shaderProgram, "ourColor");
        doHaveUniformLocations = true;
    }

    useProgram(shaderProgram);
    uniformMatrix4fv(transformLoc);
    uniform4f(vertexColorLoc);
    bindVertexArray();
    drawElements();
}

int Box::getUniformLocation(int shaderProgram, std::string uniform) {
    return glGetUniformLocation(shaderProgram, uniform.c_str());
}

void Box::useProgram(int program) {
    glUseProgram(program);
}

void Box::uniformMatrix4fv(int transformLoc) {
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void Box::uniform4f(int vertexColorLocation) {
    glUniform4f(vertexColorLocation, r, g, b, 1.0f);
}

void Box::bindVertexArray() {
    glBindVertexArray(VAO);
}

void Box::drawElements() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}