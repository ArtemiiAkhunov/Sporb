#include "bn_fixed_point_fwd.h"
#include "bn_sprite_item.h"
#include "bn_sprite_items_astronaut.h"
#include "bn_sprite_ptr.h"
#include "PhysicsObject.cpp"

class Entity : public PhysicsObject {
public:
    const int start_x; // X-coordinate
    const int start_y; // Y-coordinate
    // Constructor
    Entity(const bn::sprite_item sprite, int x, int y)
        : sprite_(sprite), sprite_ptr_(bn::sprite_items::astronaut.create_sprite(x, y)), start_x(x), start_y(y) {
        }

    // Accessors
    const bn::sprite_item getSpriteItem() const { return sprite_; }
    bn::fixed_point getPos() const override { return sprite_ptr_.position(); }

    // Mutators
    void setPos(bn::fixed_point pos) override {
      sprite_ptr_.set_position(pos);
    }

    virtual void tick(float deltaTime) {};
    virtual bool canInteract(PhysicsObject obj) { return false; }

private:
    const bn::sprite_item sprite_; // Reference to const sprite_item
    bn::sprite_ptr sprite_ptr_;
};
