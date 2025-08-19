#pragma once
#include "Entity.h"

class Wyvern : public Entity {
public:
    uchar health = 1;
    string color = "Green";

    Wyvern(const Sprite::Info& s_i) : Entity(s_i) {}

    void Update() override;
    //void DrawGUI() override;

private:
    uchar mv_spd = 3;
    Sprite::Info proj_info = {};
};