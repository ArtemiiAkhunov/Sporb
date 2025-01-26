#include "bn_camera_ptr.h"
#include "bn_fixed_point_fwd.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "Entity.cpp"

class Player : private Entity {
public:
  Player(bn::sprite_ptr& sprite_ptr, const bn::sprite_item *sprite_item) : Entity(sprite_ptr, sprite_item), camera_(bn::camera_ptr::create(getPos())) {
    sprite_ptr.set_camera(camera_);
  }
  void tick(float deltaTime) override {
    // TODO: update is touching ground
    velocity_t current_velocity = getVel();

    if (!isDash) { 
      if(dashCoolDown > 0) {
        dashCoolDown --;
      }
      if(bn::keypad::left_held()) {
        current_velocity.xvel = -PLAYER_SPEED;
      } else if (bn::keypad::right_held()) {
        current_velocity.xvel = PLAYER_SPEED;
      } else if (bn::keypad::r_pressed() && dashCoolDown == 0 && touchedGround) {
        isDash = true;
        dashTime = DASH_LENGTH;
        setGravity(false);
        touchedGround = false;
        // TODO: Reduce air capacity
      } else { // TODO: Add descelate dive
        current_velocity.xvel = 0.0f;
      }
    }


    if (isDash) {
      if (dashTime > 0) {
        dashTime --;
        current_velocity.xvel = DASH_SPEED;
        current_velocity.yvel = 0.0f;
      } else {
        isDash = false;
        dashCoolDown = DASH_COOLDOWN;
        setGravity(true);
      }
    }


    setVel(current_velocity);
    this->tickPhysics(deltaTime);

    bn::fixed_point current_position = getPos();

    setPos(current_position);
    /*if (isDash) { // TODO: Animations
      
    } else {
      if () {

      }
    }*/
  }
  void setPos(bn::fixed_point pos) override {
    setWorkaroundPos(pos);
    // camera_.set_position(pos);
    
  }
private:
  bool isDash = true;
  bool touchedGround = false;
  int dashCoolDown = 0;
  int dashTime = 0;
  bn::camera_ptr camera_;
};
