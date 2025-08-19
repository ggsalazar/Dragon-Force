#pragma once

#include "Entity.h"

class Projectile : public Entity {
public:

	Projectile(const Sprite::Info& s_i, bool up = true)
		: Entity(s_i) {	vel = up ? -7 : 7; }

	void Update() override {
		//Move
		MoveBy(Vec2f(0, vel));
	}

private:
	char vel = 7;
};