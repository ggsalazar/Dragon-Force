#include "Dragon.h"
#include "Projectile.h"
#include "../Core/Input.h"

Dragon::Dragon(const Sprite::Info& s_i) : Entity(s_i) {
	proj_info.sheet = "Dragon/Projectiles";
	proj_info.origin = { .5 }; proj_info.frame_size = { 8 };
}

void Dragon::GetInput() {
	//Movement
	Vec2f offset;
	//Up
	if (Input::KeyDown(SCW))
		offset.y = -mv_spd;
	//Down
	else if (Input::KeyDown(SCS))
		offset.y = mv_spd;
	//Left
	if (Input::KeyDown(SCA))
		offset.x = -mv_spd;
	//Right
	else if (Input::KeyDown(SCD))
		offset.x = mv_spd;

	MoveBy(offset);
	//Can't move offscreen
	if (pos.x < sprite.GetScaledSize().x * .5f) MoveTo(Vec2f{ sprite.GetScaledSize().x * .5f, (float)pos.y });
	else if (game->min_res.x - sprite.GetScaledSize().x*.5f < pos.x) MoveTo(Vec2f{ game->min_res.x - sprite.GetScaledSize().x * .5f, (float)pos.y });
	if (pos.y < sprite.GetScaledSize().y*.5f) MoveTo(Vec2f{ (float)pos.x, sprite.GetScaledSize().y * .5f });
	if (game->min_res.y - sprite.GetScaledSize().y*.5f < pos.y) MoveTo(Vec2f{ (float)pos.x, game->min_res.y - sprite.GetScaledSize().y * .5f });


	//Fire projectiles
	if (Input::KeyPressed(SPACE)) {
		if (color == "Red") proj_info.curr_frame = 0;

		proj_info.pos = pos;
		game->projs.push_back(new Projectile(proj_info));
	}
}
