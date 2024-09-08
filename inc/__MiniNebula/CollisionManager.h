#pragma once
#include <vector>

#include <__MiniNebula/CollisionBox.h>
#include <SDL3/SDL_render.h>

class CollisionManager {
public:
    static CollisionManager* getInstance();

    CollisionBox* CreateCollisionBox();
    void DestroyCollisionBox(CollisionBox* _box);

    void ProcessCollisions();
    void debugRender(SDL_Renderer* renderer);
private:
    static CollisionManager* _instance;
    std::vector<CollisionBox> _collision_box_list;

    CollisionManager() = default;
    ~CollisionManager() = default;
};
