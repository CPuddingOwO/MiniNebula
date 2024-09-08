#include <__MiniNebula/CollisionBox.h>


void CollisionBox::setActive(bool _active) { active = _active; }
void CollisionBox::setLayerSrc(CollisionLayer _layer) { layer_src = _layer; }
void CollisionBox::setLayerDst(CollisionLayer _layer) { layer_dst = _layer; }
void CollisionBox::setOnCollideCallback(std::function<void()> _callback) { onCollideCallback = _callback; }
void CollisionBox::setPos(Vec2<float>& _pos) { pos = _pos; }
void CollisionBox::setSize(Vec2<float>& _size) { size = _size; }
Vec2<float> CollisionBox::getSize() { return size; }

