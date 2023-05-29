#include "Camera.h"

Camera::Camera() {
	x = 400;
	y = 400;
	width = 710;
	height = 702;
	zIndex = -1;

	name = "CAMERA";

	Hitbox* hitbox = new Hitbox();
	hitbox->x = 400;
	hitbox->y = 400;
	hitbox->width = 710;
	hitbox->height = 702;
	hitbox->parent = this;

	hitboxes.insert(hitbox);
}

void Camera::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {

}

void Camera::enactStateChanges() {

}