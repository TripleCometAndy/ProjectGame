#pragma once

class OrionEntity;
struct Hitbox {
	double x;
	double y;
	int width;
	int height;
	OrionEntity* parent;

	bool operator<(const Hitbox& rhs) const noexcept
	{
		return this->x < rhs.x;
	}

    bool isColliding(Hitbox * hitbox)
    {
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        //Calculate the sides of our rect (A)
        leftA = x;
        rightA = x + width;
        topA = y;
        bottomA = y + height;

        //Calculate the sides of the other rect (B)
        leftB = hitbox->x;
        rightB = hitbox->x + hitbox->width;
        topB = hitbox->y;
        bottomB = hitbox->y + hitbox->height;

        //If any of the sides from A are outside of B
        if (bottomA <= topB){
            return false;
        }

        if (topA >= bottomB){
            return false;
        }

        if (rightA <= leftB){
            return false;
        }

        if (leftA >= rightB){
            return false;
        }

        //If none of the sides from A are outside B
        return true;
    }
};