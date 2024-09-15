#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <chrono>
#include <unordered_map>
#include <vector>

#include <__MiniNebula/__Math.h>
#include <__MiniNebula/Sprite.h>
#include <__MiniNebula/ResourceManager.h>
#include <__MiniNebula/SceneManager.h>
#include <__MiniNebula/CollisionManager.h>

class App {
public:
    App() = default;
    ~App() {quit();}

    bool init(int argc, char *argv[]);
    bool run();
    bool quit();
private:
    SDL_Texture* _load_texture(const char* path);

    void _render();
    void _update();
    void _event();

    void FrameDurationCalc();

    SDL_bool _running = SDL_FALSE;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SceneManager* mp_i = SceneManager::getInstance();
    ResourceManager* rm_i = ResourceManager::getInstance();
    CollisionManager* cm_i = CollisionManager::getInstance();

    Vec2<float> _window_scale = { 3.0f, 3.0f };


    std::string title = "MiniNebula";
    Vec2<int> _window_size = {1280, 800};

    std::chrono::system_clock::time_point TimeStampB;
//    Uint32 TimeStampB;
    float MaxFPS = 30.0f;
    double FrameDuration = 1000.0 / MaxFPS;
    double dt = FrameDuration;
};

