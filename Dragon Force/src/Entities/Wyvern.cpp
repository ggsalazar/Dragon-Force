#include "Wyvern.h"

void Wyvern::Update() {
	Entity::Update();



	//Behavioral AI - TO-DO



	//Just move down for now
	Vec2f offset = {};
	offset.y = mv_spd;

	MoveBy(offset);
}
