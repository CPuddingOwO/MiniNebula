#include <__MiniNebula/ResourceManager.h>

ResourceManager* ResourceManager::_instance = nullptr;

struct SingleTexInfo {
    std::string id;
    std::string path;
};

struct AtlasTexInfo {
    std::string id;
    std::string path;
};

struct MusicInfo {
    std::string id;
    std::string path;
};

static const std::vector<SingleTexInfo> single_tex_info_list = {
        {"gfx.bg.test", "res/gfx/background.png"},
};

static const std::vector<AtlasTexInfo> atlas_tex_info_list = {
        {"gfx.alligator.forklift.empty", "res/gfx/Player_Forklift_Empty.png"},
        {"gfx.alligator.forklift.full", "res/gfx/Player_Forklift_Full.png"},
};

static const std::vector<MusicInfo> music_info_list = {
        {"mfx.theme", "res/mfx/theme.mp3"},
};

void ResourceManager::init(SDL_Renderer *renderer) {
    if (renderer != nullptr) {
        _renderer = renderer;
    }
}

ResourceManager* ResourceManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new ResourceManager();
    }
    return _instance;
}

SDL_Texture* ResourceManager::getSingleTexture(const std::string& id) const {
    const auto& it = _single_tex_hashmap.find(id);
    if (it != _single_tex_hashmap.end()) {
        return it->second;
    }
    return nullptr;
}

SDL_Texture* ResourceManager::getAtlasTexture(const std::string& id) const {
    const auto& it = _atlas_tex_hashmap.find(id);
    if (it != _atlas_tex_hashmap.end()) {
        return it->second;
    }
    return nullptr;
}

Mix_Music* ResourceManager::getMusic(const std::string& id) const {
    const auto& it = _music_hashmap.find(id);
    if (it != _music_hashmap.end()) {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::freeAllMusic() {
    for (auto &music : _music_hashmap) {
        Mix_FreeMusic(music.second);
    }
    _music_hashmap.clear();
}


void ResourceManager::load() {
    for (auto &info : single_tex_info_list) {
        _single_tex_hashmap[info.id] = _load_texture(info.path.c_str());
    }
    for (auto &info : atlas_tex_info_list) {
        _atlas_tex_hashmap[info.id] = _load_texture(info.path.c_str());
    }
    for (auto &info : music_info_list) {
        _music_hashmap[info.id] = Mix_LoadMUS(info.path.c_str());
    }
}

SDL_Texture* ResourceManager::_load_texture(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Failed to load texture -> %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create texture -> %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return nullptr;
    }
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(surface);
    return texture;
}

void ResourceManager::mirror(SDL_Texture * tex) { }
void ResourceManager::rotate(SDL_Texture * tex, float cur) { }

