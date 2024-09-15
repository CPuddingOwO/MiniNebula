#include <__MiniNebula/SceneManager.h>
#include <stdexcept>

SceneManager* SceneManager::_instance = nullptr;
ResourceManager* SceneManager::_rm_instance = ResourceManager::getInstance();

SceneManager* SceneManager::getInstance() {
    if (_instance == nullptr) _instance = new SceneManager;
    return _instance;
}

Scene* SceneManager::getScene(std::string name) {
    for (auto &Scene : _Scene_list) {
        if (Scene.Name == name) return &Scene;
    }
    throw std::runtime_error("Scene not found");
}

Scene* SceneManager::getScene(int id) {
    if (id < 0 || id >= _Scene_list.size()) throw std::runtime_error("Scene not found");
    return &_Scene_list[id];
}

// TODO: Remove this method, use load_from_json() instead
std::vector<Scene>* SceneManager::getML_instance() {
    return &_Scene_list;
}

void SceneManager::load() {
    _Scene_list.push_back(Scene{
        "Default",
        {},
        {},
        {},
        {},
        {SceneTile({0, 0}, _rm_instance->getSingleTexture("gfx.bg.test"), {Sprite::Type::Single})}
    });
}