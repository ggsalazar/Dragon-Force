#pragma once
#include <chrono>
#include <unordered_map>
#include "../Core/Camera.h"
#include "../Core/Enums.h"
#include "../Graphics/Window.h"
#include "../Graphics/Renderer.h" //SDL_render, Sprite (SDL_image)

using namespace std;
using namespace chrono;
using hr_clock = high_resolution_clock;
using durationf = duration<float>;

class Dragon;
class Projectile;
class Wyvern;

class Game {
private:
    //Variables
    uchar fps = 0, game_frames = 0;
    float target_frame_time;
    hr_clock::time_point last_time;
    durationf delta;
    float accumulated_time = 0.f,
        music_volume = 100,
        sfx_volume = 100;


    uint wyvern_timer_max = 180,
        wyvern_timer = 180;

public:
    //Game UTH details
    const Vec2u min_res = { 640, 360 };
    Vec2u resolution;
    Window window;
    Renderer renderer;
    bool running = true;
    float delta_time = 0.f;
    bool paused = false;
    uchar curr_ui_layer = 0;

    //Game details
    Dragon* dragon = nullptr;
    vector<Projectile*> projs;
    Sprite::Info wyvern_info = {};
    vector<Wyvern*> wyverns;

    //Camera
    Camera camera;

    //Music & SFX - waiting for SDL_mixer 3.0
    //DJ dj;
    //Soundboard sb;

    //Miscellaneous
    unordered_map<int, Font> default_fonts;
    Text debug_txt;
    Sprite cursor;

    Game(const char* title, const uchar init_fps);
    ~Game() {
        delete dragon;
        for (auto& p : projs) delete p;
        projs.clear();

        TTF_Quit();
        //Mix_CloseAudio();
        //Mix_Quit();
        SDL_Quit(); //Pretty sure this has to be called last
    }

    //Engine
    void Run();
    void ProcessInput();
    void Update();
    void Render();

    //Frame stuff
    inline uchar GetFPS() const { return fps; }
    inline int GetGameFrames() const { return game_frames; }

    //Settings
    void SetMusicVolume(float n_v);
    inline float GetMusicVolume() const { return music_volume; }
    void SetSFXVolume(float n_v);
    inline float GetSFXVolume() const { return sfx_volume; }

    void SetResolution(uchar res_scalar);
    void SetResolution(Vec2u n_r);
    void SetRes();
};