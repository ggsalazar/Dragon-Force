#pragma once
#include "Entity.h"

class Dragon : public Entity {
public:
    uchar health = 10;
    string color = "Red";
    uchar fire_timer_max = 30;
    int fire_timer = 30;

    Dragon(const Sprite::Info& s_i);

    void GetInput() override;
    //void DrawGUI() override;

private:
    uchar mv_spd = 4;
    Sprite::Info proj_info = {};
};