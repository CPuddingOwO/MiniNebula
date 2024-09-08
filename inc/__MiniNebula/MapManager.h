#pragma once

#include <unordered_map>

#include <__MiniNebula/ResourceManager.h>
#include <__MiniNebula/Sprite.h>
#include <memory>

struct MapTile : Sprite{
    MapTile(Vec2<int> _pos, SDL_Texture* _tex, Sprite::Tex_Info _tex_info) : Sprite({(float)_pos.x, (float)_pos.y}, _tex, _tex_info) {}
};

class Map {
public:
    std::string Name;
    std::vector<MapTile> Layer0;
    std::vector<MapTile> Layer1;
    std::vector<MapTile> Layer2;
    std::vector<MapTile> Layer3;
    std::vector<MapTile> Layer4;
};

class MapManager {
public:
    static MapManager* getInstance();

    void load();

    Map* getMap(std::string name);
    Map* getMap(int id);
    std::vector<Map>* getML_instance();
private:
    static MapManager* _instance;
    static ResourceManager* _rm_instance;
    std::vector<Map> _map_list;

    MapManager() = default;
    ~MapManager() = default;
};