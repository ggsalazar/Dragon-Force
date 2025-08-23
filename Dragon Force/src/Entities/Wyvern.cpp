#include "Wyvern.h"
#include "Projectile.h"

Wyvern::Wyvern(const Sprite::Info& s_i, const char i_color) :
	Entity(s_i), color(i_color) {

	proj_info.sheet = "Wyverns/Projectiles";

	string sheet_color(1, color);

	switch (color) {
		case 'B':
			max_health = 1;
		break;

		case 'G':
			max_health = 2;
		break;

		case 'P':
			max_health = 3;
		break;
	}
	proj_info.curr_frame = max_health - 1;
	proj_info.frame_size = { 8 };
	health = max_health;
	sprite.SetSheet("Wyverns/" +sheet_color + " Wyvern");

	//Randomly determine AI
	//Movement pattern
	
	//Other movement patterns - TO-DO
	//move_pattern = rand() % 3;
	move_pattern = 0;
	move_pattern_act_y = 32 + rand() % 180;
	//Firing timer
	fire_timer_max = 30 + (rand() % 60);
	fire_timer = fire_timer_max;
}

void Wyvern::Update() {
	Entity::Update();
	//Behavioral AI
	//Fire
	if (--fire_timer == 0) {
		fire_timer = fire_timer_max;
		fire_timer += rand() % 20;
		proj_info.pos = { pos.x-6, pos.y + 16 };
		game->projs.push_back(new Projectile(proj_info, false));
	}

	//Move down
	Vec2f offset = {};
	if (!in_pattern or pattern_used)
		offset.y = mv_spd;

	//Activate movement pattern
	if (!in_pattern and pos.y >= move_pattern_act_y and !pattern_used) {
		//Set pattern_points
		switch (move_pattern) {
			//Triangle
			case 0:
				pattern_points.push_back({ {pos.x, pos.y - 60}, false });
				pattern_points.push_back({ {pos.x + 70, pos.y + 60 }, false });
				pattern_points.push_back({ {pos.x - 70, pos.y + 60 }, false });
			break;

			//Square
			case 1:

			break;

			//S2S:
			case 2:

			break;
		}

		in_pattern = true;
	}
	
	//Flying in movement pattern
	else if (in_pattern) {
		switch (move_pattern) {
			case 0:
				//Move to first point
				if (!pattern_points[0].second) {
					pattern_points[0].second = Distance(pattern_points[0].first, pos) <= 15;
					offset.y = -mv_spd;
					if (pos.x != pattern_points[0].first.x) offset.x = mv_spd*.5f;
					if (pattern_points[0].second and pattern_points[2].second) pattern_used = true;
				}
				//Move to second point
				else if (!pattern_points[1].second) {
					pattern_points[1].second = Distance(pattern_points[1].first, pos) <= 15;
					offset.x = mv_spd * .5f;
					offset.y = mv_spd;
				}
				//Move to third point
				else if (!pattern_points[2].second) {
					pattern_points[2].second = Distance(pattern_points[2].first, pos) <= 15;
					offset.x = -mv_spd;
					if (pattern_points[2].second) pattern_points[0].second = false;
				}
			break;
		}
	}
	
	MoveBy(offset);

	if (pos.y >= 400) health = 0;
}

void Wyvern::Draw() {
	Entity::Draw();

	//for (const auto& p : pattern_points) {
	//	game->renderer.DrawCircle(Circle(p.first, 2), Color(1, 0, 0));
	//}
}
