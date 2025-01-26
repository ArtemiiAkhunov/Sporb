#include "bn_bg_palettes.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_astronaut.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_items_sky.h"
#include "bn_regular_bg_items_testmap2.h"

#include "bn_camera_ptr.h"
#include "bn_music_items.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bntmx_maps_testmap2.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_sprite_text_generator.h"

#include "Player.cpp"

void animation() {
  bn::sprite_ptr astronaut_sprite = bn::sprite_items::astronaut.create_sprite(0, 0);

  bn::sprite_animate_action<4> action = bn::create_sprite_animate_action_forever(astronaut_sprite, 16, bn::sprite_items::astronaut.tiles_item(), 1, 0, 1, 2);

  // while (!bn::keypad::start_pressed()) {
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
    // bn::core::update();
  // }
}

int main() {

  bn::core::init();
  bn::bg_palettes::set_transparent_color(bn::color(2, 2, 5));

  bn::music_items::mainmelody.play();
  bntmx::map* map = new bntmx::maps::testmap2();
  auto tiles= map->tiles(0);
  // int y;
  // int x;
  int cols = map->dimensions_in_tiles().width();
  int rows = map->dimensions_in_tiles().height();

  // for (y = 0; y < cols; y++) {

  // }
  // auto thing = bn::regular_bg_tiles_items::foreground.create_tiles();
  // bn::regular_bg_map_item map_item(
  //   tiles[0], // Map data
  //   bn::size(map->dimensions_in_tiles())
  // );

  // bn::regular_bg_ptr::create(0, 0, map_item, bn::regular_bg_tiles_items::foreground);
  // bn::music_items::maybe.play();

  bn::timer counter = bn::timer();
  const float ticks_per_second = (float) bn::timers::ticks_per_second();

  bn::sprite_ptr character_sprite = bn::sprite_items::astronaut.create_sprite(0, 0);
  character_sprite.set_bg_priority(0);

  bn::camera_ptr root_camera = bn::camera_ptr::create(0, 0);
  Player character = Player(character_sprite, &bn::sprite_items::astronaut, root_camera, &tiles, rows, cols);
  // character_sprite.remove_camera();
  character_sprite.set_camera(root_camera);

  bn::regular_bg_ptr sky = bn::regular_bg_items::sky.create_bg(-56, -56);
  bn::regular_bg_ptr level = bn::regular_bg_items::testmap2.create_bg(0,0);
  sky.set_priority(3);
  level.set_priority(2);
  sky.set_camera(root_camera);
  level.set_camera(root_camera);
  // level.set_blending_enabled(true);
  float speed = -0.025;
  // auto objects = map->objects(0);
  // for (int i = 0; i < objects.size(); i++) {
  //   objects[i].id
  // }

  while (true) {
    float deltaT = 1.0f;
    // BN_ASSERT(false, "thing", counter.elapsed_ticks_with_restart(), " ", (int) ticks_per_second);

    // DISPLAY_SKY
    if (bn::keypad::left_held()) {
      sky.set_x(sky.x() - speed);
    } else if (bn::keypad::right_held()) {
      sky.set_x(sky.x() + speed);
    } else if (bn::keypad::up_held()) {
      sky.set_y(sky.y() + speed);
    } else if (bn::keypad::down_held()) {
      sky.set_y(sky.y() - speed);
    }
    // END DISPLAY_SKY

    character.tick(deltaT);
    // animation();

    bn::core::update();
  }
}
