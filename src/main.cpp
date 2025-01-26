#include "bn_assert.h"
#include "bn_bg_palettes.h"
#include "bn_core.h"
#include "bn_fixed_point_fwd.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_astronaut.h"
#include "bn_sprite_items_ninja.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_items_sky.h"
#include "bn_regular_bg_items_testmap2.h"

#include "bn_camera_ptr.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bntmx_maps_testmap2.h"
#include "bn_regular_bg_tiles_items_foreground.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_tiles_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_map_cell_info.h"
#include "utils.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define TILE_SIZE (32)

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

bn::fixed_point attemptToEnter(bn::span<bool>* tiles, bn::fixed_point src, bn::fixed_point dst, int cols, int rows) {
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
        if (tile_x >= 0 && tile_y >= 0 && tile_x < rows && tile_y < cols && (*tiles)[tile_y * cols + tile_x]) {
            return current_pos;  // Return the furthest valid point
        }

        // Move to the next step
        current_pos.set_x(current_pos.x() + x_step);
        current_pos.set_y(current_pos.y() + y_step);
    }

    return dst;  // No collision, return the destination
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
  Player character = Player(character_sprite, &bn::sprite_items::astronaut);

  bn::regular_bg_ptr sky = bn::regular_bg_items::sky.create_bg(-56, -56);
  bn::regular_bg_ptr level = bn::regular_bg_items::testmap2.create_bg(0,0);
  sky.set_priority(3);
  level.set_priority(2); 
  sky.set_camera(root_camera);
  level.set_camera(root_camera);
  // level.set_blending_enabled(true);
  float speed = -0.025;

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
