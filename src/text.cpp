
// #include "bn_core.h"

// void text_scene()
//     {
//         bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
//         text_generator.set_center_alignment();

//         bn::vector<bn::sprite_ptr, 32> text_sprites;
//         text_generator.generate(0, -text_y_limit, "Text", text_sprites);
//         text_generator.generate(0, text_y_limit, "START: go to next scene", text_sprites);

//         while(! bn::keypad::start_pressed())
//         {
//             bn::core::update();
//         }
//     }