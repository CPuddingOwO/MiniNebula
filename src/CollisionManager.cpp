#include <__MiniNebula/CollisionManager.h>


CollisionManager* CollisionManager::_instance = nullptr;


CollisionManager* CollisionManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new CollisionManager();
    }
    return _instance;
}

CollisionBox* CollisionManager::CreateCollisionBox() {
    auto* box = new CollisionBox();
    _collision_box_list.push_back(*box);
    return box;
}

void CollisionManager::DestroyCollisionBox(CollisionBox* _box) {
    for (auto it = _collision_box_list.begin(); it != _collision_box_list.end(); it++) {
        if (*it == *_box) {
            _collision_box_list.erase(it);
            break;
        }
    }
    delete _box;
}

void CollisionManager::debugRender(SDL_Renderer* renderer) {
    for (auto& box : _collision_box_list) {
        if (!box.active) {
            continue;
        }

        SDL_FRect r = {box.pos.x, box.pos.y, box.size.x, box.size.y};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &r);
    }
}

void CollisionManager::ProcessCollisions() {
    for (auto& src_box : _collision_box_list) {
        if (!src_box.active || src_box.layer_dst == CollisionLayer::None) {
            continue;
        }

        for (auto& dst_box : _collision_box_list) {
            if (!dst_box.active || src_box == dst_box || src_box.layer_dst != dst_box.layer_src) {continue;}
            bool isCollide_x = (std::max(src_box.pos.x + src_box.size.x / 2,
                                         dst_box.pos.x + dst_box.size.x / 2
                                         ) - std::min(src_box.pos.x - src_box.size.x / 2,
                                                        dst_box.pos.x - dst_box.size.x / 2
                                                        ) <= src_box.size.x + dst_box.size.x);
            bool isCollide_y = (std::max(src_box.pos.y + src_box.size.y / 2,
                                         dst_box.pos.y + dst_box.size.y / 2
                                         ) - std::min(src_box.pos.y - src_box.size.y / 2,
                                                        dst_box.pos.y - dst_box.size.y / 2
                                                        ) <= src_box.size.y + dst_box.size.y);

            if (isCollide_x && isCollide_y) {
                src_box.onCollideCallback();
                dst_box.onCollideCallback();
            }
        }
    }
}