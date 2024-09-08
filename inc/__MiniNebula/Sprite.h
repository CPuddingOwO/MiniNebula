#pragma once

#include <__MiniNebula/Renderable.h>
#include <__MiniNebula/__Math.h>

class Sprite : public Renderable {
public:
    enum class Type { Single, Atlas };
    enum class Anchor { Centered, BottomCentered};

    struct Tex_Info {
        Sprite::Type type = Sprite::Type::Single;
        int total = 1;
        Vec2<int> spacing = {0, 0};
        float scale = 1.0f;
        bool loop = true;
        Uint32 duration = 0;
        Uint32 cur_duration = 0;
    };
private:
    Vec2<float> pos;
    Vec2<float> size{};
    SDL_Texture* tex;
    Tex_Info tex_info;
    mutable Uint32 last_frame_time = 0;
    mutable int cur_frame = 0;
public:
    Sprite(const Vec2<float>& _pos, SDL_Texture* _tex, const Tex_Info& _tex_info);
    void render(SDL_Renderer* renderer) const override ;
};
