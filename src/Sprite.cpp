#include <__MiniNebula/Sprite.h>
#include <__MiniNebula/Renderable.h>
#include <__MiniNebula/__Math.h>
#include <SDL3/SDL_timer.h>


Sprite::Sprite(const Vec2<float> &_pos, SDL_Texture *_tex, const Sprite::Tex_Info &_tex_info) :
pos(_pos), tex(_tex), tex_info(_tex_info) {
    SDL_GetTextureSize( tex, &size.x, &size.y);
}

void Sprite::render(SDL_Renderer* renderer) const  {
    if (tex_info.type == Sprite::Type::Single) {
        SDL_FRect dstRect = { pos.x, pos.y, size.x * tex_info.scale , size.y * tex_info.scale };
        SDL_RenderTexture(renderer, tex, nullptr, &dstRect);
    } else if (tex_info.type == Sprite::Type::Atlas) {
        Uint32 now = SDL_GetTicks();

        if (now - last_frame_time > tex_info.duration) {
            cur_frame = ( cur_frame + 1 ) % tex_info.total;
            last_frame_time = now;
        }

        float frame_width = (tex_info.spacing.x == 0)
                            ? size.x / static_cast<float>(tex_info.total)
                            : (size.x + static_cast<float>(tex_info.spacing.x) * (tex_info.total - 1)) / static_cast<float>(tex_info.total);

        int _frame_width_ = static_cast<int>(frame_width);

        SDL_FRect srcRect = {static_cast<float>(_frame_width_ * cur_frame), 0, static_cast<float>(_frame_width_), size.y};

        SDL_FRect dstRect = { pos.x, pos.y, (float)_frame_width_ * tex_info.scale , size.y * tex_info.scale };
        SDL_RenderTexture(renderer, tex, &srcRect, &dstRect);
    }

}
