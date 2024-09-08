#pragma once

#include <SDL3/SDL_render.h>

class Renderable {
private:
    float _scale = 1.0f;
public:
    virtual ~Renderable() = default;

    virtual void render(SDL_Renderer* renderer) const = 0;
};

