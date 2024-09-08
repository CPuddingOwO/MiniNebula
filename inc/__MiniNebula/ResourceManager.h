#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map>
#include <vector>
#include <string>

#include <__MiniNebula/__Math.h>
#include <__MiniNebula/Sprite.h>

class ResourceManager {
public:
    void init(SDL_Renderer* renderer);
    static ResourceManager* getInstance();
    void load();
    SDL_Texture* getSingleTexture(const std::string& id) const;
    SDL_Texture* getAtlasTexture(const std::string& id) const;
    Mix_Music* getMusic(const std::string& id) const;
    // TODO: Remove this method, Only load 2 Music, Destroy after use
    void freeAllMusic();


    SDL_Texture* _load_texture(const char* path);
private:
    SDL_Renderer* _renderer;
    static ResourceManager* _instance;
    std::vector<std::vector<Sprite>> _map_list;
    std::unordered_map<std::string, Mix_Music*> _music_hashmap;
    std::unordered_map<std::string, SDL_Texture*> _single_tex_hashmap;
    std::unordered_map<std::string, SDL_Texture*> _atlas_tex_hashmap;

    ResourceManager() = default;
    ~ResourceManager() = default;

    void mirror(SDL_Texture * tex);
    void rotate(SDL_Texture * tex, float cur);
};
