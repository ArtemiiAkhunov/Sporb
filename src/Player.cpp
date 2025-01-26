#include "bn_assert.h"
#include "bn_camera_ptr.h"
#include "bn_fixed_point_fwd.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "Entity.cpp"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define TILE_SIZE (32)

class Player : private Entity {
public:
  Player(bn::sprite_ptr& sprite_ptr, const bn::sprite_item *sprite_item, bn::camera_ptr camera, bn::span<bool>* tiles, int rows, int cols) : Entity(sprite_ptr, sprite_item), camera_(camera), tiles_(tiles), rows(rows), cols(cols) {
    setGravity(true);
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
    camera_.set_position(pos);
    //zeroSpritePointer();
    //BN_ASSERT(false, "BRUH:", camera_.x(), " ", camera_.y());
  }
private:
  bool isDash = true;
  bool touchedGround = false;
  int dashCoolDown = 0;
  int dashTime = 0;
  bn::camera_ptr camera_;
  const bn::span<bool>* tiles_;
  const int rows;
  const int cols;
  bn::fixed_point attemptToEnter(bn::fixed_point src, bn::fixed_point dst) {
    // Calculate the direction of movement
    bn::fixed dx = dst.x() - src.x();
    bn::fixed dy = dst.y() - src.y();

    // Calculate the number of steps along the x and y axis
    int steps = bn::max(ABS(dx.integer()), ABS(dx.integer()));  // Max steps in x or y direction

    // Calculate the step size in each direction
    bn::fixed x_step = dx / steps;
    bn::fixed y_step = dy / steps;

    // Start from the src position
    bn::fixed_point current_pos = src;

    // Iterate over each step and check for collisions
    for (int i = 0; i <= steps; ++i) {
        int tile_x = current_pos.x().integer() / TILE_SIZE;
        int tile_y = current_pos.y().integer() / TILE_SIZE;

        // Check if the current tile is collidable
        if (tile_x >= 0 && tile_y >= 0 && tile_x < rows && tile_y < cols && (*tiles_)[tile_y * cols + tile_x]) {
            return current_pos;  // Return the furthest valid point
        }

        // Move to the next step
        current_pos.set_x(current_pos.x() + x_step);
        current_pos.set_y(current_pos.y() + y_step);
    }

    return dst;  // No collision, return the destination
}
};
