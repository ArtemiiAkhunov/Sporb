#include "bn_bg_palettes.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_astronaut.h"
#include "bn_sprite_items_ninja.h"
#include "bn_sprite_ptr.h"

#include "bn_camera_ptr.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"

void sprites_visibility_scene() {

  bn::sprite_ptr red_sprite = bn::sprite_items::astronaut.create_sprite(0, 0);

  while (!bn::keypad::start_pressed()) {
    if (bn::keypad::a_pressed()) {
      red_sprite.set_visible(!red_sprite.visible());
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

/*int main() {

  bn::core::init();
  bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

  // bn::sound_items::bubbletest2.play();
  // bn::music_items::bubble.play();

  while (true) {
    animation();
    bn::core::update();
  }
}*/
