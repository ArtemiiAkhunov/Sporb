#include "bn_assert.h"
#include "bn_camera_ptr.h"
#include "bn_fixed_point_fwd.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "Entity.cpp"
#include "bn_vector.h"
#include "bntmx.h"
#include "bn_math.h"
#include "utils.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define TILE_SIZE (32)
#define DISTANCE(src,dst) ()

class Player : private Entity {
public:
  Player(bn::sprite_ptr& sprite_ptr, const bn::sprite_item *sprite_item, bn::camera_ptr camera, bn::span<const bntmx::map_tile>* tiles, int rows, int cols) : Entity(sprite_ptr, sprite_item), camera_(camera), tiles_(tiles), rows(rows), cols(cols) {
    setGravity(true);
  }

  bool grounded(bn::fixed_point pos) override {
    return ((*tiles_)[pixel_to_tile(pos + (bn::fixed_point) {0, 16})]);
  }

  void tick(float deltaTime) override {
    // TODO: update is touching ground
    velocity_t current_velocity = getVel();
    bn::fixed_point current_pos = getPos();

    if (grounded(current_pos)) {
      touchedGround = true;
    }

    if (!isDash) {
      if(dashCoolDown > 0) {
        dashCoolDown --;
      }


      if (bn::keypad::r_pressed() && dashCoolDown == 0 && touchedGround) {
        isDash = true;
        dashTime = DASH_LENGTH;
        setGravity(false);
        touchedGround = false;
        // TODO: Reduce air capacity
      }

      if(bn::keypad::left_held()) {
        current_velocity.xvel = -PLAYER_SPEED;
        facingLeft = true;
      } else if (bn::keypad::right_held()) {
        current_velocity.xvel = PLAYER_SPEED;
        facingLeft = false;
      } else { // TODO: Add descelate dive
        current_velocity.xvel = 0.0f;
      }

      if (bn::keypad::a_pressed() && grounded(current_pos) && (((int) current_pos.y()) % 32) >= JUMP_POSITION) {
        current_velocity.yvel = JUMP_SPEED;
        setGravity(true);
        // Do we need to do anything else here?
      } 
    }


    if (isDash) {
      if (dashTime > 0) {
        dashTime --;
        current_velocity.xvel = DASH_SPEED;
        if (facingLeft) {
          current_velocity.xvel = -DASH_SPEED;
        }
        current_velocity.yvel = 0.0f;
      } else {
        isDash = false;
        dashCoolDown = DASH_COOLDOWN;
        if (!grounded(current_pos)) {
          setGravity(true);
        }
      }
    }


    setVel(current_velocity);
    this->tickPhysics(deltaTime);

    current_pos = getPos();

    setPos(current_pos);  
  }

  void setPos(bn::fixed_point pos) override {
    setWorkaroundPos(pos);
    camera_.set_position(pos);
    //zeroSpritePointer();
    //BN_ASSERT(false, "BRUH:", camera_.x(), " ", camera_.y());
  }

  static inline float distance(bn::fixed_point src, bn::fixed_point dst) {
    return bn::sqrt((float) (((dst.x() - src.x()) * (dst.x() - src.x())) + (dst.y() - src.y()) * (dst.y() - src.y())));
  }

  static inline int pixel_to_tile(bn::fixed_point pos) {
    return (((pos.y().integer()) + 256 + 16) / 32) * 16 + (((pos.x().integer()) + 256) / 32);
  }

  bn::fixed_point attemptToEnter(bn::fixed_point src, bn::fixed_point dst) override {
    bn::fixed_point result = dst;
    // X
    bn::fixed distX = (dst.x() - src.x());
    if (distX.integer() != 0) {
      bn::fixed_point pos = src;
      if (distX > 0) {
        // positive
        bn::fixed_point step_size = {1, 0};
        for (int i = 0; i < distX; i++) {
          pos += step_size;
          if ((*tiles_)[pixel_to_tile(pos)]) {
            BN_LOG("COLLIDED!", (int)getVel().xvel, " ", (int) getVel().yvel, " ", pixel_to_tile(pos));
            // return pos - step_size;
            result.set_x(pos.x() - step_size.x());
            break;
          }
        }
      } else {
        bn::fixed_point step_size = {-1, 0};
        for (int i = 0; i > distX; i--) {
          pos += step_size;
          if ((*tiles_)[pixel_to_tile(pos)]) {
            BN_LOG("COLLIDED!", (int)getVel().xvel, " ", (int) getVel().yvel, " ", pixel_to_tile(pos));
            // return pos - step_size;
            result.set_x(pos.x() - step_size.x());
            break;
          }
        }
      }
    }
    // Y
    bn::fixed distY = (dst.y() - src.y());
    if (distY.integer() != 0) {
      bn::fixed_point pos = src;
      if (distY > 0) {
        // positive
        bn::fixed_point step_size = {0, 1};
        for (int i = 0; i < distY; i++) {
          pos += step_size;
          if ((*tiles_)[pixel_to_tile(pos)]) {
            BN_LOG("COLLIDED!", (int)getVel().xvel, " ", (int) getVel().yvel, " ", pixel_to_tile(pos));
            // return pos - step_size;
            result.set_y(pos.y() - step_size.y());
            break;
          }
        }
      } else {
        bn::fixed_point step_size = {0, -1};
        for (int i = 0; i > distY; i--) {
          pos += step_size;
          if ((*tiles_)[pixel_to_tile(pos)]) {
            BN_LOG("COLLIDED!", (int)getVel().xvel, " ", (int) getVel().yvel, " ", pixel_to_tile(pos));
            // return pos - step_size;
            result.set_y(pos.y() - step_size.y());
            break;
          }
        }
      }
    }
    return result;
  }

private:
  bool isDash = false;
  bool touchedGround = false;
  int dashCoolDown = 0;
  int dashTime = 0;
  bool facingLeft = false;
  bn::camera_ptr camera_;
  const bn::span<const bntmx::map_tile>* tiles_;
  const int rows;
  const int cols;
};
