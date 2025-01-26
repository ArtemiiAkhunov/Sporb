#ifndef UTILS_H
#define UTILS_H

typedef struct {
  float xvel;
  float yvel;
} velocity_t;

#define GRAVITY (0.15f)
#define PLAYER_SPEED (1.0f)
#define DASH_COOLDOWN (100)
#define DASH_LENGTH (10)
#define DASH_SPEED (5)
#define MAX_SPEED (3.0f)
#define JUMP_POSITION (15)
#define JUMP_SPEED (-6.0f)
#define IDLE 0,0,0,0
#define ANIM_WALK 1,0,1,2
#define ANIM_DASH 6,7,8,6
#define ANIM_GROUNDPOUND 9,10,11,12
#define ANIM_JUMP 3,4,5,3
#define X_BORDER (255.0f)
#endif
