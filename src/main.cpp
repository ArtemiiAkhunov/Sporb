#include "bn_bg_palettes.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_astronaut.h"
#include "bn_sprite_items_ninja.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_items_sky.h"

#include "bn_camera_ptr.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bntmx_maps_testmap2.h"

void sprites_bg_move_scene() {
  bn::regular_bg_ptr sky = bn::regular_bg_items::sky.create_bg(-56, -56);
  sky.set_priority(0);
  float speed = 0.05;

  while(! bn::keypad::start_pressed()) {
    if (bn::keypad::left_held()) {
      sky.set_x(sky.x() - speed);
    } else if (bn::keypad::right_held()) {
      sky.set_x(sky.x() + speed);
    } else if (bn::keypad::up_held()) {
      sky.set_y(sky.y() + speed);
    } else if (bn::keypad::down_held()) {
      sky.set_y(sky.y() - speed);
    }
    bn::core::update();
  }
}

void animation() {
  bn::sprite_ptr astronaut_sprite = bn::sprite_items::astronaut.create_sprite(0, 0);

  bn::sprite_animate_action<4> action = bn::create_sprite_animate_action_forever(astronaut_sprite, 16, bn::sprite_items::astronaut.tiles_item(), 1, 0, 1, 2);

  while (!bn::keypad::start_pressed()) {
    if (bn::keypad::left_pressed()) {
      action = bn::create_sprite_animate_action_forever(astronaut_sprite, 16, bn::sprite_items::astronaut.tiles_item(), 1, 0, 1, 2);
    } else if (bn::keypad::right_pressed()) {
      action = bn::create_sprite_animate_action_forever(astronaut_sprite, 16, bn::sprite_items::astronaut.tiles_item(), 1, 0, 1, 2);
    }

    if (bn::keypad::up_pressed()) {
      action = bn::create_sprite_animate_action_forever(astronaut_sprite, 16, bn::sprite_items::astronaut.tiles_item(), 2, 1, 0, 1);
    } else if (bn::keypad::down_pressed()) {
      action = bn::create_sprite_animate_action_forever(astronaut_sprite, 16, bn::sprite_items::astronaut.tiles_item(), 2, 1, 0, 1);
    }

    action.update();
    bn::core::update();
  }
}

int main() {

  bn::core::init();
  bn::bg_palettes::set_transparent_color(bn::color(2, 2, 5));

  bn::music_items::mainmelody.play();
  bntmx::map* map = new bntmx::maps::testmap2();
  map->tiles(0).front()
  // bn::music_items::maybe.play();

  bn::timer timer;
  const float ticks_per_second = (float) bn::timers::ticks_per_second();

  while (true) {
    float deltaT = timer.elapsed_ticks_with_restart() / ticks_per_second;

    // animation();

    sprites_bg_move_scene();
    bn::core::update();
  }
}
