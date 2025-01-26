#include "bn_assert.h"
#include "bn_fixed_fwd.h"
#include "bn_fixed_point_fwd.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "utils.h"

class Entity {
public:
    const int start_x; // X-coordinate
    const int start_y; // Y-coordinate
    // Constructor
    Entity(bn::sprite_ptr& sprite_ptr, const bn::sprite_item *sprite_item)
        : sprite_ptr_(sprite_ptr), start_x(sprite_ptr.x()), start_y(sprite_ptr.y()) ,animation_(bn::create_sprite_animate_action_forever(sprite_ptr, 1, sprite_item->tiles_item(), 0, 0, 0, 0)), gravity_(true) {
        }

    // Accessors
    bn::fixed_point getPos() const {
        return pos_;
    };
    virtual bool canInteract(Entity entity) const {
        return true;
    };
    velocity_t getVel() const { return vel_; };
    bool isGravity() { return gravity_; };

    // Mutators
    virtual void setPos(bn::fixed_point pos) {
      sprite_ptr_.set_position(pos);
      pos_ = pos;
    }
    virtual void tick(float deltaTime) {};
    void setVel(velocity_t vel) { vel_ = vel; };
    void setGravity(bool gravity) { gravity_ = gravity;};
    void tickPhysics(float deltaT) {
        bn::fixed y = pos_.y().to_float() + (vel_.yvel * deltaT);
        bn::fixed x = pos_.x().to_float() + (vel_.xvel * deltaT);
        if (gravity_) {
            y += (0.5f * (deltaT * deltaT) * GRAVITY);
            // BN_ASSERT(false, "YOU STUPIOD", y);
            setVel({vel_.xvel, vel_.yvel + (deltaT * GRAVITY)});
        }
        setPos({x, y});
    };
    void setWorkaroundPos(bn::fixed_point pos) { pos_ = pos; sprite_ptr_.set_position(pos); };

private:
    bn::sprite_ptr sprite_ptr_;
    bn::fixed_point pos_;
    bn::sprite_animate_action<4> animation_;
    velocity_t vel_;
    bool gravity_;
};
