#pragma once
#include "Entity.h"

class Wyvern : public Entity {
public:
    uchar max_health = 1, health = 1, move_pattern = 0;
    char color = 'G';

    Wyvern(const Sprite::Info& s_i, const char i_color = 'G');

    void Update() override;
    void Draw() override;
    //void DrawGUI() override;

private:
    uchar mv_spd = 3;
    Sprite::Info proj_info = {};
    vector<pair<Vec2i, bool>> pattern_points;
    bool in_pattern = false, pattern_used = false;
    int move_pattern_act_y = 360;
    uchar /*pattern_repeats = 0, pattern_delay = 0, pattern_delay_max = 0, */fire_timer = 0, fire_timer_max = 0;


};