#ifndef _BACKGROUND
#define _BACKGROUND
#include "../include/Background.h"
#endif

#include "../include/Hitbox.h"

Background::Background(std::vector<std::string>* spriteSheetPaths) {
	x = 400;
	y = 400;
	width = 710;
	height = 702;
	name = "BACKGROUND";
	zIndex = 0;

	for (std::string path : *spriteSheetPaths) {
		this->spriteSheetPaths.push_back(path);
	}

	Hitbox * hitbox = new Hitbox();
	hitbox->x = 0;
	hitbox->y = 0;
	hitbox->width = 710;
	hitbox->height = 702;
	hitbox->parent = this;

	hitboxes.insert(hitbox);
}

void Background::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {

}

void Background::enactStateChanges() {

}