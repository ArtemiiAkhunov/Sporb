#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_blue_bg.h"


void sprites_bg_move_scene() {
  bn::regular_bg_ptr blue_bg = bn::regular_bg_items::blue_bg.create_bg(-56, -56);
  blue_bg.set_priority(0);
  int speed = 1;

  while(! bn::keypad::start_pressed()) {
    if (bn::keypad::left_held()) {
      blue_bg.set_x(blue_bg.x() - speed);
    } else if (bn::keypad::right_held()) {
      blue_bg.set_x(blue_bg.x() + speed);
    } else if (bn::keypad::up_held()) {
      blue_bg.set_y(blue_bg.y() + speed);
    } else if (bn::keypad::down_held()) {
      blue_bg.set_y(blue_bg.y() - speed);
    }
    bn::core::update();
  }
}


int main() {

  bn::core::init();
  //bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

  // bn::sound_items::bubbletest2.play();
  // bn::music_items::bubble.play();

  while (true) {
    sprites_bg_move_scene();
    bn::core::update();
  }
}
