#pragma once

#include <unordered_map>

#include <__MiniNebula/ResourceManager.h>
#include <__MiniNebula/Sprite.h>
#include <memory>

struct SceneTile : Sprite{
    SceneTile(Vec2<int> _pos, SDL_Texture* _tex, Sprite::Tex_Info _tex_info) : Sprite({(float)_pos.x, (float)_pos.y}, _tex, _tex_info) {}
};

class Scene {
public:
    std::string Name;
    std::vector<SceneTile> Layer0;
    std::vector<SceneTile> Layer1;
    std::vector<SceneTile> Layer2;
    std::vector<SceneTile> Layer3;
    std::vector<SceneTile> Layer4;
};

class SceneManager {
public:
    static SceneManager* getInstance();

    void load();

    Scene* getScene(std::string name);
    Scene* getScene(int id);
    std::vector<Scene>* getML_instance();
private:
    static SceneManager* _instance;
    static ResourceManager* _rm_instance;
    std::vector<Scene> _Scene_list;

    SceneManager() = default;
    ~SceneManager() = default;
};