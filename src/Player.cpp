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

  static inline float distance(bn::fixed_point src, bn::fixed_point dst) {
    return bn::sqrt((float) (((dst.x() - src.x()) * (dst.x() - src.x())) + (dst.y() - src.y()) * (dst.y() - src.y())));
  }

  static inline int pixel_to_tile(bn::fixed_point pos) {
    return  ((((pos.y()) + 80) / 32) * 16 + (((pos.x()) + 120) / 32)).integer();
  }

  bn::fixed_point attemptToEnter(bn::fixed_point src, bn::fixed_point dst) override {
    // determine tiles we start, end in, and pass through
    // check, from start to end, for the first tile that is collidable
    // return a position just outside that tile
    bn::vector<int, 256> tilesWeCross(0);
    float dist = distance(src, dst);
    // BN_LOG("DIST", (int) dist);
    if ((int) dist == 0) return dst;
    int steps = dist;
    bn::fixed_point pos = src;
    bn::fixed_point step_size = (dst - src).safe_division(dist);
    BN_LOG(pos.x(), " ", pos.y());
    int i;

    for (i = 0; i < steps; i++) {
      pos += step_size;
      if ((*tiles_)[pixel_to_tile(pos)]) {
        BN_LOG("COLLIDED!");
        return pos - step_size;
      }
    }
    return dst;
}
private:
  bool isDash = true;
  bool touchedGround = false;
  int dashCoolDown = 0;
  int dashTime = 0;
  bn::camera_ptr camera_;
  const bn::span<const bntmx::map_tile>* tiles_;
  const int rows;
  const int cols;
};
