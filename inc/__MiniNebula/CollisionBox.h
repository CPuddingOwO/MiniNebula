#pragma once

#include <vector>
#include <functional>

#include <__MiniNebula/CollisionLayer.h>
#include <__MiniNebula/__Math.h>

class CollisionBox {
    friend class CollisionManager;

private:
    Vec2<float> size;
    Vec2<float> pos;
    bool active = true;
    std::function<void()> onCollideCallback;
    CollisionLayer layer_src = CollisionLayer::None;
    CollisionLayer layer_dst = CollisionLayer::None;
public:
    CollisionBox() = default;
    ~CollisionBox() = default;
public:
    void setActive(bool _active);
    void setLayerSrc(CollisionLayer _layer);
    void setLayerDst(CollisionLayer _layer);
    void setOnCollideCallback(std::function<void()> _callback);
    void setPos(Vec2<float>& _pos);
    void setSize(Vec2<float>& _size);

    Vec2<float> getSize();

    bool operator==(const CollisionBox& other) const {
        return pos == other.pos && size == other.size;
    }
};