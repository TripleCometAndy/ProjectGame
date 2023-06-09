#include "Camera.h"

Camera::Camera() {
	x = 0;
	y = 0;
	width = 800;
	height = 600;
	zIndex = -1;

	name = "CAMERA";

	Hitbox* hitbox = new Hitbox();
	hitbox->x = 0;
	hitbox->y = 0;
	hitbox->width = 2000;
	hitbox->height = 2000;
	hitbox->parent = this;

	hitboxes.insert(hitbox);
}

void Camera::handleStateChanges(std::set<InputType>* currentInputs, std::set<JoystickInput *> * joystickInputs,  CollisionMap * collisionMap) {

}

void Camera::enactStateChanges() {

}

void Camera::show(int shaderProgram){
}