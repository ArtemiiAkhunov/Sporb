#ifndef UTILS_H
#define UTILS_H

typedef struct {
  float xvel;
  float yvel;
} velocity_t;

#define GRAVITY (0.15f)
#define PLAYER_SPEED (5.0f)
#define DASH_COOLDOWN (100)
#define DASH_LENGTH (20)
#define DASH_SPEED (20)
#define MAX_SPEED (3.0f)
#define JUMP_SPEED (-6.0f)
#define ANIM_WALK 1,0,1,2
#define ANIM_DASH 6,7,8,6
#define ANIM_GROUNDPOUND 9,10,11,12
#define ANIM_JUMP 3,4,5,3
#endif
