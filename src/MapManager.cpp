#include <__MiniNebula/MapManager.h>
#include <stdexcept>

MapManager* MapManager::_instance = nullptr;
ResourceManager* MapManager::_rm_instance = ResourceManager::getInstance();

MapManager* MapManager::getInstance() {
    if (_instance == nullptr) _instance = new MapManager;
    return _instance;
}

Map* MapManager::getMap(std::string name) {
    for (auto &map : _map_list) {
        if (map.Name == name) return &map;
    }
    throw std::runtime_error("Map not found");
}

Map* MapManager::getMap(int id) {
    if (id < 0 || id >= _map_list.size()) throw std::runtime_error("Map not found");
    return &_map_list[id];
}

// TODO: Remove this method, use load_from_json() instead
std::vector<Map>* MapManager::getML_instance() {
    return &_map_list;
}

void MapManager::load() {
    _map_list.push_back(Map{
        "Default",
        {},
        {},
        {},
        {},
        {MapTile({0, 0}, _rm_instance->getSingleTexture("gfx.bg.test"), {Sprite::Type::Single})}
    });
}