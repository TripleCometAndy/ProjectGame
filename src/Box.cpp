#include "Box.h"

#include <iostream>

Box::Box() {
    std::cout << "GOT HERE!!!!" << std::endl;
}

void Box::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {

}

void Box::enactStateChanges() {

}

void Box::show(int shaderProgram){
}